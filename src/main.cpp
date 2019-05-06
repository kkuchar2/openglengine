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

    engine->engineRenderer->perspectiveCamera->setPosition(glm::vec3(0.0, 2.0, 5.0));

    engine->addScene(testSphereScene());
    engine->addScene(instancedScene());
    engine->addScene(mainScene());

    engine->start();

    glfwTerminate();

    return 0;
}