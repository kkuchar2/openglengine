#include "Engine/Engine.h"
#include "Engine/Scene/Scenes.h"

int main() {
    std::shared_ptr<Engine> engine;

    try {
        engine = std::make_shared<Engine>();
    }
    catch (EngineException & e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    //engine->addScene(baseScene());
    engine->addScene(shaderTestScene());
    //engine->addScene(orthographicScene());

    engine->perspectiveCamera->SetPosition(glm::vec3(0.0f, 0.0, 3.0));
    engine->renderingLoop();

    glfwTerminate();

    return 0;
}