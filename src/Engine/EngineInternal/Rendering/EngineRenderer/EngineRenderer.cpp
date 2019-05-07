#include <Rendering/Mesh/MeshBuilder.h>
#include "EngineRenderer.h"
#include <ctime>
#include <thread>

EngineRenderer::EngineRenderer(const std::shared_ptr<Window> & window, const std::shared_ptr<PhysicsEngine> & physicsEngine) {
    createFramebuffer();
    ortographicCamera = std::make_shared<OrtographicCamera>(window->size);
    perspectiveCamera = std::make_shared<PerspectiveCamera>(glm::vec3(0.0, 5.0, 10.0));
    renderingManager = std::make_shared<RenderingManager>();
    renderingManager->physicsEngine = physicsEngine;
}

void EngineRenderer::addScene(const std::shared_ptr<Scene> & scene) {
    for (auto & child : scene->children) {
        renderingManager->addChild(child);
    }
}

void EngineRenderer::prepare() {
    renderingManager->preprocessScenes();

    for (auto & info : renderingManager->meshes) {
        info->renderer->prepare();
    }

    for (auto  & [id, info] : renderingManager->instancedMeshes) {
        info->renderer->prepare();
    }
}

void EngineRenderer::renderFrame() {
    perspectiveCamera->Update();
    ortographicCamera->Update();
    renderingManager->Update(perspectiveCamera);

    glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    for (auto const & [id, info] : renderingManager->instancedMeshes) {
        if (id == "bbox" && !renderingManager->enableBoundingBoxes) continue;
        glPolygonMode(GL_FRONT_AND_BACK, id == "bbox"? GL_LINE : GL_FILL);
        getCamera(info->renderer->projection)->renderInstanced(info);
    }

    for (auto const & info : renderingManager->meshes) {
        getCamera(info->renderer->projection)->render(info);
    }
}

void EngineRenderer::createFramebuffer() {

    glGenFramebuffers(1, &framebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);

    glGenTextures(1, &mainTexture);
    glBindTexture(GL_TEXTURE_2D, mainTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, width, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &dephRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, dephRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, dephRenderBuffer);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mainTexture, 0);

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
    }
}

void EngineRenderer::setTargetSize(const glm::vec2 & size) {

    if (std::abs(size.x - width) < 1.0f && std::abs(size.y - height) < 1.0f) return;

    width = size.x;
    height = size.y;

    glBindTexture(GL_TEXTURE_2D, mainTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, dephRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    perspectiveCamera->updateAspectRatio(size);
    ortographicCamera->updateSize(size);
}

std::shared_ptr<BaseCamera> EngineRenderer::getCamera(const Projection & projection) {
    switch (projection) {
        case PERSPECTIVE: return perspectiveCamera;
        case ORTOGRAPHIC: return ortographicCamera;
    }
}

void EngineRenderer::setBoundingBoxesEnabled(const bool & enabled) {
    renderingManager->enableBoundingBoxes = enabled;
}


