#include "Engine.h"

Engine::Engine() {
    window = std::make_shared<Window>(1500, 1000);

    renderer = std::make_shared<TextureRenderer>(window);

    InputDispatcher::init(window);

    ortographicCamera = std::make_shared<OrtographicCamera>(window);
    perspectiveCamera = std::make_shared<PerspectiveCamera>(window, glm::vec3(0.0, 5.0, 10.0));

    renderer->addCamera(ortographicCamera);
    renderer->addCamera(perspectiveCamera);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    editor = std::make_shared<Editor>(window);

    observer = createObserver<glm::vec2>([&](glm::vec2 v) {
        renderer->updateSize(v);
        perspectiveCamera->aspectRatio = v.x / v.y;
    });

    subscription = editor->sceneWindowSizeProperty->Subscribe(observer);
}

void Engine::addScene(const std::shared_ptr<UserScene> & scene) {
    renderer->addScene(SceneMapper::mapToEngine(scene));
}

void Engine::prepareScenes() {
    renderer->prepareScenes();
}

void Engine::renderingLoop() {
    std::cout << "Preparing scenes start" << std::endl;
    prepareScenes();
    std::cout << "Preparing scenes end" << std::endl;

    while (window->shouldBeOpened()) {
        renderer->renderToTexture();
        editor->renderFrame(window, renderer->width, renderer->height, renderer->texture);
        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    editor->terminate();

    glfwTerminate();

    subscription->Unsubscribe();
}