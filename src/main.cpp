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
        std::cerr << e.what() << std::endl;
        return -1;
    }

    engine->addScene(baseScene());
    //engine->addScene(shaderTestScene());
    engine->addScene(instancedScene());

    engine->start();

    glfwTerminate();

    return 0;
}