#ifndef OPENGL_WINDOWMANAGER_H
#define OPENGL_WINDOWMANAGER_H

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
        float aspectRatio{};

        float lastTime = 0.0f;
        float totalTime = 0.0f;

        bool vSyncEnabled = false;

        Window(const int resX, const int resY) {

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            if (vSyncEnabled) {
                glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE );
            }

            createWindow(resX, resY);
            width = resX;
            height = resY;
            aspectRatio = (float) width / (float) height;
            glfwMakeContextCurrent(window);

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                throw EngineException("Failed to initialize GLAD");
            }
        }

        void createWindow(const int resX, const int resY) {
            window = glfwCreateWindow(resX, resY, "Demo", nullptr, nullptr);
            if (!window) {
                glfwTerminate();
                exit(EXIT_FAILURE);
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

        void setFramebufferSizeCallback(GLFWframebuffersizefun callback) {
            glfwSetFramebufferSizeCallback(window, callback);
        }

        void framebuffer_size_callback(GLFWwindow * window, int width, int height) {
            this->width = width;
            this->height = height;
        }

        glm::vec2 getResolution() {
            return glm::vec2(width, height);
        }

        void Update() {
            glfwGetFramebufferSize(window, &width, &height);
            aspectRatio = (float) width / (float) height;
            UpdateTime();
            if (vSyncEnabled) {

                glFinish();
            }
            else {
                glfwSwapBuffers(window);
            }

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

#endif //OPENGL_WINDOWMANAGER_H
