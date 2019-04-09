#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <functional>
#include <glm/glm/glm.hpp>
#include <glad.h>

#include "../EngineException.h"

class Window {

    public:
        GLFWwindow * window { nullptr };

        int width = -1;
        int height = -1;

        bool vSyncEnabled = false;

        Window(const int resX, const int resY);

        void setKeyCallback(GLFWkeyfun callback);

        void setMouseButtonCallback(GLFWmousebuttonfun callback);

        void setScrollCallback(GLFWscrollfun callback);

        void setCursorPositionCallback(GLFWcursorposfun callback);

        glm::vec2 getResolution();

        bool shouldBeOpened();

        void glfwSetWindowCenter();

        ~Window();
};