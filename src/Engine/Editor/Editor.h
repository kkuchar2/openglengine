#pragma once

#include <Rose/Observable.h>

#include <glad.h>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glm/glm/glm.hpp>
#include <RoseCpp/src/Rose/Property/BooleanProperty.h>

#include "EditorStyle.h"

#include "../Window/Window.h"

class Editor {

    private:
        
        ImGuiIO * io_ptr;

    public:
        
        std::shared_ptr<Observable<glm::vec2>> sceneLeftSizeProperty;
        std::shared_ptr<Observable<glm::vec2>> sceneRightSizeProperty;

        std::shared_ptr<BooleanProperty> enableBoundingBoxesProperty;
        std::shared_ptr<BooleanProperty> enableVsyncProperty;
        std::shared_ptr<BooleanProperty> showNormalsProperty;

        Editor(const std::shared_ptr<Window> & window);

        static void DockSpaceBegin();

        static ImGuiID createView(ImGuiID & node_id, ImGuiDir split_dir, float ratio);

        void DockSpaceEnd();

        void renderConsoleWindow();
        
        void renderSettingsWindow();
        
        void renderInfoWindow();

        void renderSceneWindow(const std::string & name, float texWidth, float texHeight, GLuint texture, ImGuiSizeCallback custom_callback = NULL);

        void ToggleButton(const char * str_id, const std::shared_ptr<Observable<bool>> & property);

        static void on_scene_left_resize(ImGuiSizeCallbackData * data);

        static void on_scene_right_resize(ImGuiSizeCallbackData * data);

        void OnSceneLeftResize(const ImVec2 & size);

        void OnSceneRightResize(const ImVec2 & size);

        void renderFrame(std::shared_ptr<Window> & window, double widths[], double heights[], GLuint textures[]);

        void terminate();
};