#pragma once

#include <ObservableBase.h>

#include <glad.h>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glm/glm/glm.hpp>

#include "EditorStyle.h"

#include "../Window/Window.h"

class Editor {

    private:
        ImGuiIO * io_ptr;

    public:
        std::shared_ptr<ObservableBase<glm::vec2>> sceneWindowSizeProperty;

        Editor(const std::shared_ptr<Window> & window);

        static void DockSpaceBegin();

        static ImGuiID createView(ImGuiID & node_id, ImGuiDir split_dir, float ratio);

        static void DockSpaceEnd();

        static void renderConsoleWindow();
        static void renderSettingsWindow();
        static void renderInfoWindow();
        static void renderHierarchyWindow();

        static void on_scene_window_resize(ImGuiSizeCallbackData * data);

        void OnSceneWindowResize(ImVec2 size);

        void renderSceneWindow(float texWidth, float texHeight, GLuint texture);

        void renderFrame(std::shared_ptr<Window> & window, float width, float height, GLuint texture);

        static void terminate();
};