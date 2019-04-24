#include "Engine.h"

Engine::Engine() {
    window = std::make_shared<Window>(1500, 1000);

    renderer = std::make_shared<Renderer>(window);

    InputDispatcher::init(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glPointSize(1.0f);

    editor = std::make_shared<Editor>(window);

    onWindowSizeChanged = createObserver<glm::vec2>([&](glm::vec2 v) { renderer->updateSize(v); });

    subscription = editor->sceneWindowSizeProperty->Subscribe(onWindowSizeChanged);
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
        editor->renderFrame(window, renderer->width, renderer->height, renderer->texture);
        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    editor->terminate();

    glfwTerminate();

    subscription->Unsubscribe();
}