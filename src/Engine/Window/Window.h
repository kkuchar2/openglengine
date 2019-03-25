#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <functional>
#include "../Exceptions/EngineException.h"

class Window {

    public:
        GLFWwindow * window { nullptr };
        int width = 600;
        int height = 600;

        float lastTime = 0.0f;
        float totalTime = 0.0f;

        bool vSyncEnabled = true;

        Window(const int resX, const int resY) {

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

            window = glfwCreateWindow(resX, resY, "Engine", nullptr, nullptr);

            if (!window) {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }

            width = resX;
            height = resY;

            glfwMakeContextCurrent(window);

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                throw EngineException("Failed to initialize GLAD");
            }

            if (vSyncEnabled) {
                glfwSwapInterval(1);
            }
        }

        void setKeyCallback(GLFWkeyfun callback) {
            glfwSetKeyCallback(window, callback);
        }

        void setMouseButtonCallback(GLFWmousebuttonfun callback) {
            glfwSetMouseButtonCallback(window, callback);
        }

        void setScrollCallback(GLFWscrollfun callback) {
            glfwSetScrollCallback(window, callback);
        }

        void setCursorPositionCallback(GLFWcursorposfun callback) {
            glfwSetCursorPosCallback(window, callback);
        }

        glm::vec2 getResolution() {
            return glm::vec2(width, height);
        }

        void Update() {
            UpdateTime();
            glfwGetFramebufferSize(window, &width, &height);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        bool shouldBeOpened() {
            return !glfwWindowShouldClose(window);
        }

        void UpdateTime() {
            auto currentTime = static_cast<float>(glfwGetTime());
            float timeDiff = currentTime - lastTime;
            totalTime += timeDiff;
            lastTime = currentTime;
        }

        ~Window() {
            glfwDestroyWindow(window);
            glfwTerminate();
            exit(EXIT_SUCCESS);
        }
};