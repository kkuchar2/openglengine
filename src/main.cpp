#include "Engine/Engine.h"

int main() {

    std::shared_ptr<Engine> engine;

    try {
        engine = std::make_shared<Engine>();
    }
    catch (EngineException & e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    auto mandelbrotShader = std::make_shared<Shader>("resources/shaders/Mandelbrot.vert", "resources/shaders/Mandelbrot.frag");
    auto gridShader = std::make_shared<Shader>("resources/shaders/Grid.vert", "resources/shaders/Grid.frag");

    std::shared_ptr<RenderObject> quad = std::make_shared<Quad>();
    std::shared_ptr<RenderObject> gridQuad = std::make_shared<Quad>();

    quad->useRendering(RenderFlag::PERSPECTIVE);
    quad->useShader(mandelbrotShader);
    quad->loadTexture("resources/textures/texture2.bmp");
    quad->transform.scale = glm::vec3(3.0f);

    gridQuad->useRendering(RenderFlag::PERSPECTIVE);
    gridQuad->useShader(mandelbrotShader);
    gridQuad->loadTexture("resources/textures/texture_white.bmp");
    gridQuad->transform.scale = glm::vec3(20.0f, 20.0f, 20.0f);
    gridQuad->transform.rotation = glm::vec3(glm::radians(90.0), 0.0f, 0.0f);

    engine->addObject(quad);
    engine->addObject(gridQuad);
    engine->renderingLoop();

    glfwTerminate();

    return 0;
}