#include <Engine/EngineInternal/Settings.h>
#include "Engine.h"

#include "Scene/BaseEngineScene.h"

Engine::Engine() {
    window = std::make_shared<Window>(1500, 1000);

    physicsEngine = std::make_shared<PhysicsEngine>();

    engineRenderer = std::make_shared<EngineRenderer>(window, physicsEngine);

    InputDispatcher::init(window);

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    glEnable(GL_DEPTH_TEST);

    editor = std::make_unique<Editor>(window);

    onSceneLeftSizeChanged = createObserver<glm::vec2>([&](glm::vec2 v) { engineRenderer->setTargetSize(v, 0); });
    onSceneRightSizeChanged = createObserver<glm::vec2>([&](glm::vec2 v) { engineRenderer->setTargetSize(v, 1); });
    onBoundingBoxesEnablementChanged = createObserver<bool>([&](bool v) { engineRenderer->setBoundingBoxesEnabled(v); });
    onVSyncValueChange = createObserver<bool>([&](bool v) { window->setVSyncEnabled(v); });

    SC.add(editor->sceneLeftSizeProperty->Subscribe(onSceneLeftSizeChanged));
    SC.add(editor->sceneRightSizeProperty->Subscribe(onSceneRightSizeChanged));
    SC.add(editor->enableBoundingBoxesProperty->Subscribe(onBoundingBoxesEnablementChanged));
    SC.add(editor->enableVsyncProperty->Subscribe(onVSyncValueChange));

    addScene(baseEngineScene());
}

void Engine::addScene(const std::shared_ptr<Scene> & scene) {
    engineRenderer->addScene(scene);
}

void Engine::prepareScenes() {
    engineRenderer->prepare();
}

void Engine::start() {
    prepareScenes();

    while (window->shouldBeOpened()) {

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //physicsEngine->step(deltaTime);
        engineRenderer->renderFrame();

        editor->renderFrame(window, engineRenderer->widths, engineRenderer->heights, engineRenderer->textures);
        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    editor->terminate();

    glfwTerminate();

    SC.unsubscribeAll();
}