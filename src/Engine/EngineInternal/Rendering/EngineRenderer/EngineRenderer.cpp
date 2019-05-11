#include <Rendering/Mesh/MeshBuilder.h>
#include "EngineRenderer.h"
#include <ctime>
#include <thread>

EngineRenderer::EngineRenderer(const std::shared_ptr<Window> & window,
                               const std::shared_ptr<PhysicsEngine> & physicsEngine) {
    createFramebuffers();
    ortographicCamera = std::make_shared<OrtographicCamera>(window->size);
    perspectiveCameras[0] = std::make_shared<PerspectiveCamera>(glm::vec3(0.0, 5.0, 10.0));
    perspectiveCameras[1] = std::make_shared<PerspectiveCamera>(glm::vec3(0.0, 40.0, 0.1f));
    perspectiveCameras[1]->disableMovement = true;
    perspectiveCameras[1]->fovy = 90.0f;

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

    for (auto  &[id, info] : renderingManager->instancedMeshes) {
        info->renderer->prepare();
    }
}

void EngineRenderer::renderFrame() {
    perspectiveCameras[0]->Update();
    perspectiveCameras[1]->Update();
    ortographicCamera->Update();

    /////// Update children /////////
    for (auto const & [id, info] : renderingManager->instancedMeshes) {

        if (id != "bbox") {
            info->renderer->not_culled_indexes.clear();

            for (int i = 0; i < info->objects.size(); i++) {
                bool notCulled = perspectiveCameras[0]->testFrustum(info->objects[i]);

                if (notCulled || !info->renderer->frustumCulling) {
                    info->renderer->not_culled_indexes.push_back(i);
                    info->objects[i]->update();
                }
            }
        }
        else {
            info->renderer->not_culled_indexes.clear();
            for (int i = 0; i < info->objects.size(); i++) {
                info->objects[i]->update();
                info->renderer->not_culled_indexes.push_back(i);
            }
        }
    }

    for (auto const & info : renderingManager->meshes) {
        bool render = perspectiveCameras[0]->testFrustum(info->objects[0]);
        if ((render && info->renderer->frustumCulling) || !info->renderer->frustumCulling) {
            info->renderer->not_culled_indexes.clear();
            info->renderer->not_culled_indexes.push_back(0);
        }
        info->objects[0]->update();
    }
    /////////////////////////////////


    ///////// Render children ///////

    for (int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);
        glClearColor(0.17f, 0.17f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    for (int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);
        glViewport(0, 0, widths[i], heights[i]);

        for (auto const &[id, info] : renderingManager->instancedMeshes) {
            if (id == "bbox" && !renderingManager->enableBoundingBoxes) continue;
            glPolygonMode(GL_FRONT_AND_BACK, id == "bbox" ? GL_LINE : GL_FILL);
            getCamera(info->renderer->projection, i)->renderInstanced(info);
        }

        for (auto const & info : renderingManager->meshes) {
            getCamera(info->renderer->projection, i)->render(info);
        }
    }
}

void EngineRenderer::createFramebuffers() {
    for (int i = 0; i < 2; i++) {
        glGenFramebuffers(1, &framebuffers[i]);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);

        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widths[i], heights[i], 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glGenRenderbuffers(1, &depthBuffers[i]);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffers[i]);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, widths[i], heights[i]);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffers[i]);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textures[i], 0);

        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "Framebuffer is not complete!" << std::endl;
        }
    }
}

void EngineRenderer::setTargetSize(const glm::vec2 & size, const int & idx) {

    if (std::abs(size.x - widths[idx]) < 1.0f && std::abs(size.y - heights[idx]) < 1.0f) return;

    widths[idx] = size.x;
    heights[idx] = size.y;

    glBindTexture(GL_TEXTURE_2D, textures[idx]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widths[idx], heights[idx], 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffers[idx]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, widths[idx], heights[idx]);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    perspectiveCameras[idx]->updateAspectRatio(size);
    ortographicCamera->updateSize(size);
}

std::shared_ptr<BaseCamera> EngineRenderer::getCamera(const Projection & projection, const int & idx) {
    switch (projection) {
        case PERSPECTIVE:
            return perspectiveCameras[idx];
        case ORTOGRAPHIC:
            return ortographicCamera;
    }
}

void EngineRenderer::setBoundingBoxesEnabled(const bool & enabled) {
    renderingManager->enableBoundingBoxes = enabled;
}


