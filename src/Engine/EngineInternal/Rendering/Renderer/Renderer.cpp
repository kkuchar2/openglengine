#include <Rendering/Mesh/MeshBuilder.h>
#include "Renderer.h"
#include <ctime>
#include <thread>

Renderer::Renderer(const std::shared_ptr<Window> & window) {
    createFrameBuffer();
    ortographicCamera = std::make_shared<OrtographicCamera>(window->width, window->height);
    perspectiveCamera = std::make_shared<PerspectiveCamera>(glm::vec3(0.0, 5.0, 10.0));
}

void Renderer::addScene(const std::shared_ptr<Scene> & scene) {
    for (auto & child : scene->children) {
        child->projection = scene->projection;
        objectsToRender.push_back(std::move(child));
    }
}

void Renderer::prepare() {
    for (auto const &[meshTypeString, shaderTypeToMeshesMap] : map) {
        for (auto const &[shaderType, meshInfo] : shaderTypeToMeshesMap) {
            meshInfo->mesh->prepare();
        }
    }

    for (auto const &[mesh, object] : meshesToRender) {
        mesh->prepare();
    }
}

ShaderToMeshesMap Renderer::createShaderToMeshesMap(const ShaderType & shaderType, const std::shared_ptr<Mesh> & mesh,
                                                    const Projection & projection, const Transform & transform) {
    ShaderToMeshesMap shaderToMeshes;
    shaderToMeshes.insert(std::make_pair(shaderType, InstancedMeshInfo::ptr(mesh, 1)));
    shaderToMeshes.at(shaderType)->mesh->modelMatrices.push_back(transform.modelMatrix);
    return shaderToMeshes;
}

void Renderer::preprocessScenes() {

    for (auto & child : objectsToRender) {

        child->transform.calculatePRSMatrices();
        child->transform.calculateModelMatrix();

        Projection projection = child->projection;

        auto meshPrototype = child->getMeshPrototype();

        if (!meshPrototype.get()) continue;

        const char * meshType = meshPrototype->meshTypeStr;

        ShaderType shaderType = meshPrototype->shaderType;

        bool instanced = meshPrototype->instanced;

        if (instanced) {
            if (map.count(meshType) == 0) {
                auto mesh = MeshBuilder::of(meshPrototype, projection, child->transform);
                map.insert(std::make_pair(meshType, createShaderToMeshesMap(shaderType, mesh, projection, child->transform)));
            }
            else {
                if (map.at(meshType).count(shaderType) == 0) {
                    auto mesh = MeshBuilder::of(meshPrototype, projection, child->transform);
                    map.at(meshType) = createShaderToMeshesMap(shaderType, mesh, projection, child->transform);
                }
                else {
                    map[meshType][shaderType]->addInstance(child->transform.modelMatrix);
                }
            }
            allInstancedCount++;
        }
        else {
            auto mesh = MeshBuilder::of(meshPrototype, projection, child->transform);
            meshesToRender.emplace_back(mesh, child);
        }
    }
}


void Renderer::updateModelMatrices(int startRange, int endRange) {
    int idx = 0;

    for (auto & child : objectsToRender) {

        if (idx < startRange) {
            idx++;
            continue;
        }
        if (idx > endRange) {
            break;
        }
        child->OnUpdate();
        auto meshPrototype = child->getMeshPrototype();
        if (!meshPrototype.get()) continue;
        if (!meshPrototype->instanced) continue;
        map[meshPrototype->meshTypeStr][meshPrototype->shaderType]->mesh->modelMatrices[idx] = child->transform.modelMatrix;
        idx++;
    }
}

void Renderer::renderAllMeshes() {

    std::thread t1 (&Renderer::updateModelMatrices, this, (allInstancedCount / 4) * 0 + 0, (allInstancedCount / 4) * 1);
    std::thread t2 (&Renderer::updateModelMatrices, this, (allInstancedCount / 4) * 1 + 1, (allInstancedCount / 4) * 2);
    std::thread t3 (&Renderer::updateModelMatrices, this, (allInstancedCount / 4) * 2 + 1, (allInstancedCount / 4) * 3);
    std::thread t4 (&Renderer::updateModelMatrices, this, (allInstancedCount / 4) * 3 + 1, (allInstancedCount / 4) * 4 - 1);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // Instanced render
    for (auto const &[meshTypeString, shaderTypeToMeshesMap] : map) {
        for (auto const &[shaderType, instancedMeshInfo] : shaderTypeToMeshesMap) {
            getCamera(instancedMeshInfo->mesh->projection)->renderInstanced(instancedMeshInfo);
        }
    }

    // Classic render
    for (auto const & [mesh, object] : meshesToRender) {
        getCamera(mesh->projection)->render(mesh, object->transform);
    }
}

void Renderer::updateCameras() {
    perspectiveCamera->Update();
    ortographicCamera->Update();
}

void Renderer::render() {
    updateCameras();
    renderAllMeshes();
}

void Renderer::createFrameBuffer() {

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

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
    }
}

void Renderer::renderToTexture() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);
    render();
}

void Renderer::updateSize(const glm::vec2 & newSize) {

    if (std::abs(newSize.x - width) < 1.0f && std::abs(newSize.y - height) < 1.0f) return;

    width = newSize.x;
    height = newSize.y;

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, dephRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

std::shared_ptr<BaseCamera> Renderer::getCamera(const Projection & projection) {
    switch (projection) {
        case PERSPECTIVE: return perspectiveCamera;
        case ORTOGRAPHIC: return ortographicCamera;
    }
}

void Renderer::logRenderMap() {
    std::cout << "INSTANCED RENDERING:" << std::endl;
    for (auto const &[meshTypeString, shaderTypeToMeshesMap] : map) {
        std::cout << "\t* Mesh type: [" << meshTypeString << "]" << std::endl;

        for (auto const &[shaderType, meshInfo] : shaderTypeToMeshesMap) {
            std::cout << "\t\t---> Shader type: " << shaderType << " Instances: " << meshInfo->instanceCount
                      << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "CLASSIC RENDERING:" << std::endl;
    for (auto const &[mesh, object] : meshesToRender) {
        std::cout << "\t* Mesh type: [" << mesh->meshType << "]" << std::endl;
    }
}