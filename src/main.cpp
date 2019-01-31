#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Shader.h"
#include "Engine/Primitives/RenderObject.h"
#include "Engine/TextureLoader.h"
#include "Engine/Primitives/Quad.h"
#include "Engine/Window.h"
#include "Engine/Renderers/OrthographicProjectionRenderer.h"
#include "Engine/Renderers/PerspectiveProjectionRenderer.h"

#include <iostream>
#include <memory>
#include <functional>

int iterations = 10;

glm::vec3 position = glm::vec3(0.0);
glm::vec3 scale = glm::vec3(0.8);

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {

    int state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
    if (state == GLFW_PRESS) {
        scale = glm::vec3(scale.x + (float) yoffset / 100.0f, scale.y + (float) yoffset / 100.0f, 1.0f);
        return;
    }

    if (iterations + yoffset >= 1) {
        iterations += yoffset;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    switch (key) {
        case GLFW_KEY_LEFT:
            position = glm::vec3(position.x - 0.02f, position.y, 0.0f);
            break;
        case GLFW_KEY_RIGHT:
            position = glm::vec3(position.x + 0.02f, position.y, 0.0f);
            break;
        case GLFW_KEY_UP:
            position = glm::vec3(position.x, position.y + 0.02f, 0.0f);
            break;
        case GLFW_KEY_DOWN:
            position = glm::vec3(position.x, position.y - 0.02f, 0.0f);
            break;
        default:break;
    }
}

Window * window;

int Init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = new Window(600, 600);

    window->setScrollCallback(scroll_callback);
    window->setKeyCallback(key_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    return 0;
}

float lastTime = 0.0f;
float totalTime = 0.0f;

int main() {
    int initResult = Init();

    if (initResult != 0) {
        return initResult;
    }

    OrtographicProjectionRenderer orthoRenderer(window);
    PerspectiveProjectionRenderer perspectiveProjectionRenderer(window);

    TextureLoader::load("resources/textures/texture_white.bmp");

    Shader * mandelbrotShader = new Shader("resources/shaders/Mandelbrot.vert", "resources/shaders/Mandelbrot.frag");

    Quad quad(mandelbrotShader);

    //quad.position = glm::vec3(2.0f, 1.0f, 0.0f);
    //quad.scale = glm::vec3(0.5f, 0.5f, 0.5f);
    quad.rotation = glm::vec3(20.0f, 0.0f, 0.0f);

    while (window->shouldBeOpened()) {

        float currentTime = static_cast<float>(glfwGetTime());
        float timeDiff = currentTime - lastTime;
        totalTime += timeDiff;
        lastTime = currentTime;

        quad.position = position;
        quad.scale = scale;

        window->Update();

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //orthoRenderer.Render(quad, [](const Shader * shader) {
        //shader->setVec2("resolution", window->getResolution());
        //    shader->setInt("iterations", iterations);
        //    shader->setFloat("time", totalTime);
        //});

        perspectiveProjectionRenderer.Render(quad, [](const Shader * shader) {
            shader->setVec2("resolution", window->getResolution());
            shader->setInt("iterations", iterations);
            shader->setFloat("time", totalTime);
        });

        window->swapBuffers();
        window->pollEvents();
    }

    delete mandelbrotShader;
    delete window;

    glfwTerminate();

    return 0;
}