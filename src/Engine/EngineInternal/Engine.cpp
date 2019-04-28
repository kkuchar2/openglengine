#include "Engine.h"

Engine::Engine() {
    window = std::make_shared<Window>(1500, 1000);

    renderer = std::make_shared<Renderer>(window);

    InputDispatcher::init(window);

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    editor = std::make_shared<Editor>(window);


    onWindowSizeChanged = createObserver<glm::vec2>([&](glm::vec2 v) { renderer->updateSize(v); });
    onBoundingBoxesEnablementChanged = createObserver<bool>([&](bool v) { renderer->enableBoundingBoxes = v; });
    onVSyncValueChange = createObserver<bool>([&](bool v) { window->setVSyncEnabled(v); });

    windowSizeSubscription = editor->sceneWindowSizeProperty->Subscribe(onWindowSizeChanged);
    boundingBoxSubscription = editor->enableBoundingBoxesProperty->Subscribe(onBoundingBoxesEnablementChanged);
    vSyncSubscription = editor->enableVsyncProperty->Subscribe(onVSyncValueChange);
}

void Engine::addScene(const std::shared_ptr<Scene> & scene) {
    renderer->addScene(scene);
}

void Engine::prepareScenes() {
    renderer->preprocessScenes();
    renderer->prepare();
}

void Engine::start() {
    prepareScenes();

    while (window->shouldBeOpened()) {
        renderer->renderFrame();
        editor->renderFrame(window, renderer->width, renderer->height, renderer->mainTexture);
        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    editor->terminate();

    glfwTerminate();

    windowSizeSubscription->Unsubscribe();
    boundingBoxSubscription->Unsubscribe();
    vSyncSubscription->Unsubscribe();
}