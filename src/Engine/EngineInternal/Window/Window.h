#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <functional>
#include <glm/glm/glm.hpp>
#include <glad.h>


#include <Rose/Observer.h>


#include "../EngineException.h"

class Window {

    public:

        GLFWwindow * window { nullptr };

        int width = 0;
        int height = 0;

        bool vSyncEnabled = true;

        Window(const int & resX, const int & resY);

        void setKeyCallback(GLFWkeyfun callback);

        void setMouseButtonCallback(GLFWmousebuttonfun callback);

        void setScrollCallback(GLFWscrollfun callback);

        void setCursorPositionCallback(GLFWcursorposfun callback);

        bool shouldBeOpened();

        void glfwSetWindowCenter();

        ~Window();
};