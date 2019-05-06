#include "Editor.h"

Editor::Editor(const std::shared_ptr<Window> & window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io_ptr = &ImGui::GetIO();

    (*io_ptr).ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    (*io_ptr).ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    (*io_ptr).ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    ImGuiStyle & style = ImGui::GetStyle();

    if ((*io_ptr).ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window->window, true);
    ImGui_ImplOpenGL3_Init("#version 420");

    EditorStyle::Apply();

    sceneWindowSizeProperty = std::make_shared<Observable<glm::vec2>>(glm::vec2(0.0, 0.0));
    enableBoundingBoxesProperty = std::make_shared<BooleanProperty>(true);
    enableVsyncProperty = std::make_shared<BooleanProperty>(window->vSyncEnabled);
    showNormalsProperty = std::make_shared<BooleanProperty>(false);
}

void Editor::DockSpaceBegin() {
    auto open = true;

    const auto window_flags =
            ImGuiWindowFlags_MenuBar |
            ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus;

    const auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y));
    ImGui::SetNextWindowViewport(viewport->ID);

    std::string dockspace_name = "MainDockspace";

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin(dockspace_name.c_str(), &open, window_flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    const auto dockspace_id = ImGui::GetID(dockspace_name.c_str());

    if (!ImGui::DockBuilderGetNode(dockspace_id)) {
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_None);

        auto dock_main_id = dockspace_id;

        auto view_info = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.1f, nullptr, &dock_main_id);

        auto views_main = createView(dock_main_id, ImGuiDir_Down, 0.9f);

        auto view_console = createView(views_main, ImGuiDir_Down, 0.2f);
        auto views_hierarchy_scene_settings = createView(views_main, ImGuiDir_Up, 0.8f);

        auto views_hierarchy_scene = createView(views_hierarchy_scene_settings, ImGuiDir_Left, 0.75f);
        auto view_settings = createView(views_hierarchy_scene_settings, ImGuiDir_Right, 0.3f);

        auto view_hierarchy = createView(views_hierarchy_scene, ImGuiDir_Left, 0.2f);
        auto view_scene = createView(views_hierarchy_scene, ImGuiDir_Right, 0.7f);

        ImGui::DockBuilderDockWindow("Info", view_info);
        ImGui::DockBuilderDockWindow("Hierarchy", view_hierarchy);
        ImGui::DockBuilderDockWindow("Scenes", view_scene);
        ImGui::DockBuilderDockWindow("Settings", view_settings);
        ImGui::DockBuilderDockWindow("Console", view_console);

        ImGui::DockBuilderFinish(dock_main_id);
    }
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
}

ImGuiID Editor::createView(ImGuiID & node_id, ImGuiDir split_dir, float ratio) {
    return ImGui::DockBuilderSplitNode(node_id, split_dir, ratio, nullptr, &node_id);
}

void Editor::DockSpaceEnd() {
    ImGui::End();
}

void Editor::renderConsoleWindow() {
    ImGui::Begin("Console");
    ImGui::End();
}

void Editor::renderSettingsWindow() {
    ImGui::Begin("Settings");

    ImGui::Dummy(ImVec2(0.0f, 20.0f));
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Dummy(ImVec2(0.0f, 20.0f));
    ImGui::Text("Enable bounding boxes:");
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ToggleButton("id", enableBoundingBoxesProperty);

    ImGui::Dummy(ImVec2(0.0f, 20.0f));
    ImGui::Text("Enable VSync:");
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ToggleButton("id2", enableVsyncProperty);

    ImGui::Dummy(ImVec2(0.0f, 20.0f));
    ImGui::Text("Show normals:");
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ToggleButton("id3", showNormalsProperty);
    ImGui::End();
}

void Editor::renderInfoWindow() {
    ImGui::Begin("Info");
    ImGui::End();
}

void Editor::renderHierarchyWindow() {
    ImGui::Begin("Hierarchy");
    ImGui::End();
}

void Editor::ToggleButton(const char * str_id, const std::shared_ptr<Observable<bool>> & property)
{
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight() * 1.1f;
    float width = height * 2.0f;
    float radius = height * 0.50f;

    ImGui::InvisibleButton(str_id, ImVec2(width, height));
    if (ImGui::IsItemClicked())
        property->setValue(!property->getValue());

    float t = property->getValue() ? 1.0f : 0.0f;

    ImGuiContext& g = *GImGui;
    float ANIM_SPEED = 0.08f;
    if (g.LastActiveId == g.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = property->getValue() ? (t_anim) : (1.0f - t_anim);
    }

    ImU32 col_bg = IM_COL32(70, 70, 70, 255);
    ImU32 col_circle = property->getValue() ? IM_COL32(10, 213, 96, 255) : IM_COL32(255, 255, 255, 255);

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, col_circle, 24);
}

void Editor::on_scene_window_resize(ImGuiSizeCallbackData * data) {
    static_cast<Editor *>(data->UserData)->OnSceneWindowResize(data->CurrentSize);
}

void Editor::OnSceneWindowResize(ImVec2 size) {
    sceneWindowSizeProperty->setValue(glm::vec2(size.x, size.y));
}

void Editor::renderSceneWindow(float texWidth, float texHeight, GLuint texture) {
    ImGui::SetNextWindowSizeConstraints({texWidth, texHeight}, {10000.0, 10000.0}, Editor::on_scene_window_resize, this);

    ImGui::Begin("Scenes");

    ImGui::GetWindowDrawList()->AddImage(
            reinterpret_cast<ImTextureID>(texture),
            ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + texWidth,
                   ImGui::GetCursorScreenPos().y + texHeight), ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

void Editor::renderFrame(std::shared_ptr<Window> & window, float width, float height, GLuint mainTexture) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, window->size.x, window->size.y);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    Editor::DockSpaceBegin();

    //Editor::renderInfoWindow();
    //Editor::renderHierarchyWindow();
    Editor::renderSceneWindow(width, height, mainTexture);
    Editor::renderSettingsWindow();
    //Editor::renderConsoleWindow();

    Editor::DockSpaceEnd();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if ((*io_ptr).ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow * backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void Editor::terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
