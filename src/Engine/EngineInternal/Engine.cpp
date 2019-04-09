#include "Engine.h"

Engine::Engine() {
    window = std::make_shared<Window>(1500, 1000);

    renderer = std::make_shared<TextureRenderer>(window);

    InputDispatcher::init(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    editor = std::make_shared<Editor>(window);

    observer = createObserver<glm::vec2>([&](glm::vec2 v) {
        renderer->updateSize(v);
        renderer->perspectiveCamera->aspectRatio = v.x / v.y;
    });

    subscription = editor->sceneWindowSizeProperty->Subscribe(observer);
}

void Engine::addScene(const std::shared_ptr<UserScene> & scene) {
    renderer->addScene(SceneMapper::mapToEngine(scene));
}

void Engine::prepareScenes() {
    renderer->prepare();
}

void Engine::start() {
    prepareScenes();

    while (window->shouldBeOpened()) {
        renderGraphics();
        editor->renderFrame(window, renderer->width, renderer->height, renderer->texture);
        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    editor->terminate();

    glfwTerminate();

    subscription->Unsubscribe();
}

void Engine::renderGraphics() {
    renderer->renderToTexture();
}