#pragma once

#include <ObservableBase.h>
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_internal.h"
#include "../../imgui/imgui_impl_glfw.h"
#include "../../imgui/imgui_impl_opengl3.h"
#include "../Utils/Logging/Logger.h"
#include "EditorStyle.h"

class Editor {
    public:

        ImGuiIO * io_ptr;

        std::shared_ptr<ObservableBase<glm::vec2>> sceneWindowSizeProperty;

        explicit Editor(std::shared_ptr<Window> & window) {
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

            sceneWindowSizeProperty = std::make_shared<ObservableBase<glm::vec2>>(glm::vec2(0.0, 0.0));
        }

        void DockSpaceBegin() {
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
                ImGui::DockBuilderDockWindow("Scene", view_scene);
                ImGui::DockBuilderDockWindow("Settings", view_settings);
                ImGui::DockBuilderDockWindow("Console", view_console);

                ImGui::DockBuilderFinish(dock_main_id);
            }
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
        }

        ImGuiID createView(ImGuiID & node_id, ImGuiDir split_dir, float ratio) {
            ImGui::DockBuilderSplitNode(node_id, split_dir, ratio, nullptr, &node_id);
        }

        void DockSpaceEnd() {
            ImGui::End();
        }

        void renderConsoleWindow() {
            ImGui::Begin("Console");

            for (auto & msg : Logger::buffer) {
                ImGui::Text("%s", msg.c_str());
            }

            ImGui::End();
        }

        void renderSettingsWindow() {
            ImGui::Begin("Settings");
            ImGui::End();
        }

        void renderInfoWindow() {
            ImGui::Begin("Info");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        void renderHierarchyWindow() {
            ImGui::Begin("Hierarchy");
            ImGui::End();
        }

        static void on_scene_window_resize(ImGuiSizeCallbackData * data) {
            static_cast<Editor *>(data->UserData)->OnSceneWindowResize(data->CurrentSize);
        }

        void OnSceneWindowResize(ImVec2 size) {
            sceneWindowSizeProperty->setValue(glm::vec2(size.x, size.y));
        }

        void renderSceneWindow(float texWidth, float texHeight, GLuint texture) {
            ImGui::SetNextWindowSizeConstraints({texWidth, texHeight}, {10000.0, 10000.0}, Editor::on_scene_window_resize, this);

            ImGui::Begin("Scene");

            ImGui::GetWindowDrawList()->AddImage(
                    reinterpret_cast<ImTextureID>(texture),
                    ImVec2(ImGui::GetCursorScreenPos()),
                    ImVec2(ImGui::GetCursorScreenPos().x + texWidth,
                           ImGui::GetCursorScreenPos().y + texHeight), ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();
        }

        void renderFrame(std::shared_ptr<Window> & window, float width, float height, GLuint texture) {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClearColor(1.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glViewport(0, 0, window->width, window->height);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            Editor::DockSpaceBegin();

            Editor::renderInfoWindow();
            Editor::renderHierarchyWindow();
            Editor::renderSceneWindow(width, height, texture);
            Editor::renderSettingsWindow();
            Editor::renderConsoleWindow();

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

        static void terminate() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
};