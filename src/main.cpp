#include <Scenes/InstanncingRenderingTestScene.h>
#include <Scenes/MainScene.h>
#include <Engine/EngineInternal/Scene/BaseScene.h>
#include <Engine.h>

int main() {
    std::shared_ptr<Engine> engine;

    try {
        engine = std::make_shared<Engine>();
    }
    catch (EngineException & e) {
        std::cout << e.what() << std::endl;
    }

    //engine->addScene(baseScene());
    engine->addScene(mainScene());

    engine->start();

    glfwTerminate();

    return 0;
}