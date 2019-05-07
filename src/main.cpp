#include <Scenes/InstanncingRenderingTestScene.h>
#include <Scenes/MainScene.h>
#include <Scenes/test/TestCubeScene.h>
#include <Scenes/test/TestSphereScene.h>
#include <Engine/Engine.h>
#include <Scenes/OrthoScene.h>

int main() {
    std::shared_ptr<Engine> engine;

    try {
        engine = std::make_shared<Engine>();
    }
    catch (EngineException & e) {
        std::cout << e.what() << std::endl;
    }

    engine->addScene(testSphereScene());
    //engine->addScene(instancedScene());
    engine->addScene(mainScene());

    engine->start();

    glfwTerminate();

    return 0;
}