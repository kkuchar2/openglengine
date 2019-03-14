#include "Engine/Engine.h"
#include "Engine/Scene/Scenes.h"

int main() {
    std::shared_ptr<Engine> engine;

    try {
        engine = std::make_shared<Engine>();
    }
    catch (EngineException & e) {
        return -1;
    }

    std::shared_ptr<RenderScene> bs = baseScene();
    std::shared_ptr<RenderScene> ms = mainScene();
    std::shared_ptr<RenderScene> os = orthographicScene();

    engine->addScene(bs);
    engine->addScene(ms);
    engine->addScene(os);

    engine->renderingLoop();

    glfwTerminate();

    return 0;
}