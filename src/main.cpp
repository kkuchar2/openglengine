#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Shader.h"
#include "Engine/Primitives/RenderObject.h"
#include "Engine/TextureLoader.h"
#include "Engine/Primitives/Quad.h"
#include "Engine/Window.h"
#include "Engine/Renderers/OrtographicCamera.h"
#include "Engine/Renderers/PerspectiveCamera.h"

#include <iostream>
#include <memory>
#include <functional>

int iterations = 10;

glm::vec3 rotation = glm::vec3(0.0);

glm::vec3 cameraPosition = glm::vec3(0.0f, 5.0f, 10.0f);

bool pressed = false;

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {

    int state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);

    if (state == GLFW_PRESS) {
        std::cout << "Rotation radians: " << rotation.x << std::endl;

        rotation = glm::vec3(rotation.x + glm::radians((float) yoffset), 0.0f, 0.0f);
        return;
    }

    if (iterations + yoffset >= 1) {
        iterations += yoffset;
    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (pressed) {
        std::cout << "Cursor position: (" << xpos << ", " << ypos << ")" << std::endl;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "Mouse button left pressed" << std::endl;
        pressed = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        std::cout << "Mouse button left released" << std::endl;
        pressed = false;
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    switch (key) {
        case GLFW_KEY_LEFT:
            break;
        case GLFW_KEY_RIGHT:
            break;
        case GLFW_KEY_UP:
            break;
        case GLFW_KEY_DOWN:
            break;
        case GLFW_KEY_W:
            cameraPosition = glm::vec3(cameraPosition.x, cameraPosition.y + 0.2, cameraPosition.z);
            break;
        case GLFW_KEY_A:
            cameraPosition = glm::vec3(cameraPosition.x - 0.2, cameraPosition.y, cameraPosition.z);
            break;
        case GLFW_KEY_S:
            cameraPosition = glm::vec3(cameraPosition.x, cameraPosition.y - 0.2, cameraPosition.z);
            break;
        case GLFW_KEY_D:
            cameraPosition = glm::vec3(cameraPosition.x + 0.2, cameraPosition.y, cameraPosition.z);
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
    window->setMouseButtonCallback(mouse_button_callback);
    window->setCursorPositionCallback(cursor_position_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}


int main() {
    int initResult = Init();

    if (initResult != 0) {
        return initResult;
    }

    OrtographicCamera orthographicCamera(window);
    PerspectiveCamera perspectiveCamera(window, cameraPosition);



    auto tex1 = TextureLoader::load("resources/textures/texture_white.bmp");
    auto tex2 = TextureLoader::load("resources/textures/texture_white.bmp");

    auto * mandelbrotShader = new Shader("resources/shaders/Mandelbrot.vert", "resources/shaders/Mandelbrot.frag");
    auto * gridShader = new Shader("resources/shaders/Grid.vert", "resources/shaders/Grid.frag");

    Quad quad(mandelbrotShader);
    Quad gridQuad(gridShader);

    //quad.position = glm::vec3(2.0f, 1.0f, 0.0f);
    quad.transform.scale = glm::vec3(3.0f);

    gridQuad.transform.rotation = glm::vec3(glm::radians(90.0), 0.0f, 0.0f);
    gridQuad.transform.scale = glm::vec3(20.0f, 20.0f, 20.0f);

    while (window->shouldBeOpened()) {

        perspectiveCamera.position = cameraPosition;

        window->UpdateTime();
        window->Update();

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //orthographicCamera.Render(quad, [](const Shader * shader) {
        //    shader->setInt("iterations", iterations);
        //});

        glBindTexture(GL_TEXTURE_2D, tex1);

        perspectiveCamera.Render(quad, [](const Shader * shader) {
            shader->setInt("iterations", iterations);
        });

        glBindTexture(GL_TEXTURE_2D, tex2);

        perspectiveCamera.Render(gridQuad, [](const Shader * shader) {});

        window->swapBuffers();
        window->pollEvents();
    }

    delete mandelbrotShader;
    delete gridShader;
    delete window;

    glfwTerminate();

    return 0;
}