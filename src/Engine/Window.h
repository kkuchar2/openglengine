#ifndef OPENGL_WINDOWMANAGER_H
#define OPENGL_WINDOWMANAGER_H

#include <include/GLFW/glfw3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>

class Window {

    public:
        GLFWwindow * window { nullptr };
        int width = 600;
        int height = 600;
        float aspectRatio{};

        float lastTime = 0.0f;
        float totalTime = 0.0f;

        Window(const int resX, const int resY, GLFWkeyfun keyCallback, GLFWmousebuttonfun mouse_button_callback, GLFWcursorposfun mouse_position_callback) {
            createWindow(resX, resY);
            glfwMakeContextCurrent(window);
            setKeyCallback(keyCallback);
            setMouseButtonCallback(mouse_button_callback);
        }

        Window(const int resX, const int resY) {
            createWindow(resX, resY);
            width = resX;
            height = resY;
            aspectRatio = (float) width / (float) height;
            glfwMakeContextCurrent(window);
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
            glViewport(0, 0, width, height);
        }

        glm::vec2 getResolution() {
            return glm::vec2(width, height);
        }

        void Update() {
            glfwGetFramebufferSize(window, &width, &height);
            aspectRatio = (float) width / (float) height;
            glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
        }

        void swapBuffers() {
            glfwSwapBuffers(window);
        }

        void pollEvents() {
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
