#include <Rendering/Mesh/MeshBuilder.h>
#include "Renderer.h"
#include <ctime>
#include <thread>

Renderer::Renderer(const std::shared_ptr<Window> & window) {
    createFramebuffer();
    ortographicCamera = std::make_shared<OrtographicCamera>(window->size);
    perspectiveCamera = std::make_shared<PerspectiveCamera>(glm::vec3(0.0, 5.0, 10.0));
}

void Renderer::addScene(const std::shared_ptr<Scene> & scene) {
    for (auto & child : scene->children) {
        gameObjects.push_back(std::move(child));
    }
}

void Renderer::prepare() {

    for (auto & info : meshes) {
        info->mesh->prepare();
    }

    for (auto  & [id, info] : instancedMeshes) {
        info->mesh->prepare();
    }
}

void Renderer::preprocessScenes() {

    for (auto & child : gameObjects) {

        child->transform.calculatePositionRotationScaleMatrices();
        child->transform.calculateModelMatrix();

        auto proto = child->getMeshPrototype();

        proto->updateIds();

        if (!proto.get()) continue;

        std::string id = proto->shaderMeshTypeId;

        if (proto->instanced) {
            if (instancedMeshes.count(id) == 0) {
                auto mesh = MeshBuilder::of(proto, child);
                instancedMeshes.insert(std::make_pair(id, MeshInfo::ptr(mesh, child)));
            }
            else {
                instancedMeshes[id]->addInstance(child, proto->color);
            }
            allInstancedCount++;
        }
        else {
            meshes.emplace_back(MeshInfo::ptr(MeshBuilder::of(proto, child), child));
        }
    }

    logRenderMap();
}

void Renderer::renderFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);
    
    for (auto const & [id, info] : instancedMeshes) {
        getCamera(info->mesh->projection)->renderInstanced(info);
    }

    for (auto const & info : meshes) {
        getCamera(info->mesh->projection)->render(info->mesh);
    }

    onUpdate();
}

void Renderer::onUpdate() {
    perspectiveCamera->Update();
    ortographicCamera->Update();

    for (const auto & [id, meshInfo] : instancedMeshes) {
        meshInfo->Update();
    }

    for (const auto & meshInfo : meshes) {
        meshInfo->Update();
    }
}

void Renderer::createFramebuffer() {

    glGenFramebuffers(1, &framebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, width, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &dephRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, dephRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, dephRenderBuffer);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
    }
}

void Renderer::updateSize(const glm::vec2 & size) {

    if (std::abs(size.x - width) < 1.0f && std::abs(size.y - height) < 1.0f) return;

    width = size.x;
    height = size.y;

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, dephRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    perspectiveCamera->updateAspectRatio(size);
    ortographicCamera->updateSize(size);
}

std::shared_ptr<BaseCamera> Renderer::getCamera(const Projection & projection) {
    switch (projection) {
        case PERSPECTIVE: return perspectiveCamera;
        case ORTOGRAPHIC: return ortographicCamera;
    }
}

void Renderer::logRenderMap() {
    std::cout << "INSTANCED RENDERING:" << std::endl;

    for (auto  & [id, instancedMeshInfo] : instancedMeshes) {
        std::cout << "\t* ID: [" << id << "]: " << instancedMeshInfo->objects.size() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "CLASSIC RENDERING:" << std::endl;
    for (auto const & info : meshes) {
        std::cout << "\t* Mesh type: [" << info->mesh->meshType << "]" << std::endl;
    }
}