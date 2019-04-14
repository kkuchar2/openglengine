#include <Rendering/Mesh/MeshBuilder.h>
#include "TextureRenderer.h"

TextureRenderer::TextureRenderer(const std::shared_ptr<Window> & window) {
    createFrameBuffer();
    ortographicCamera = std::make_shared<OrtographicCamera>(window->width, window->height);
    perspectiveCamera = std::make_shared<PerspectiveCamera>(glm::vec3(0.0, 5.0, 10.0));
}

void TextureRenderer::addScene(const std::shared_ptr<EngineScene> & scene) {
    scenes.at(scene->projection).push_back(scene);
}

void TextureRenderer::prepare() {

    for (auto & pair : scenes) {
        for (auto & scene : pair.second) {

            auto projection = scene->projection;

            for (auto & engineObject : scene->objects) {


                // Get model matrix based on camera
                glm::mat4 modelMatrix;

                switch (projection) {

                    case PERSPECTIVE:
                        modelMatrix = perspectiveCamera->createModelMatrix(engineObject->getTransform());
                        break;
                    case ORTOGRAPHIC:
                        modelMatrix = ortographicCamera->createModelMatrix(engineObject->getTransform());
                        break;
                }

                // Get mesh prototype
                auto meshPrototype = engineObject->getMeshPrototype();

                if (!meshPrototype.get()) continue;

                const char * meshType = meshPrototype->getMeshType();

                ShaderType shaderType = meshPrototype->shaderType;

                // Check if instanced rendering is enabled
                bool instanced = meshPrototype->instanced;

                if (instanced) {
                    if (map.count(meshType) == 0) {
                        auto mesh = MeshBuilder::of(meshPrototype, projection);
                        ShaderToMeshesMap shaderToMeshes;
                        shaderToMeshes.insert(std::make_pair(shaderType, std::make_pair(mesh, 1)));
                        shaderToMeshes.at(shaderType).first->modelMatrices.push_back(modelMatrix);
                        map.insert(std::make_pair(meshType, shaderToMeshes));
                    }
                    else {
                        if (map.at(meshType).count(shaderType) == 0) {
                            auto instancedMesh = MeshBuilder::of(meshPrototype, projection);
                            ShaderToMeshesMap shaderToMeshes;
                            shaderToMeshes.insert(std::make_pair(shaderType, std::make_pair(instancedMesh, 1)));
                            shaderToMeshes.at(shaderType).first->modelMatrices.push_back(modelMatrix);
                            map.insert(std::make_pair(meshType, shaderToMeshes));
                        }
                        else {
                            auto currentVal = map[meshType][shaderType];
                            map[meshType][shaderType] = std::make_pair(currentVal.first, currentVal.second + 1);
                            map[meshType][shaderType].first->modelMatrices.push_back(modelMatrix);
                        }
                    }
                }
                else {
                    auto mesh = MeshBuilder::of(meshPrototype, projection);
                    mesh->projection = projection;
                    mesh->modelMatrix = modelMatrix;
                    mesh->prepare();
                    meshesToRender.emplace_back(std::make_pair(mesh, meshPrototype->getMeshType()), engineObject->getTransform());
                }
            }
        }
    }


    std::cout << "INSTANCED RENDERING:" << std::endl;
    for (auto & pair : map) {
        std::cout << "\t* Mesh type: [" << pair.first << "]" << std::endl;

        std::cout << std::endl;

        for (auto & pair2 : map[pair.first]) {
            std::cout << "\t\t---> Shader type: " << pair2.first << " Instances: " << pair2.second.second << std::endl;
            pair2.second.first->prepare();
        }

        std::cout << std::endl;
    }


    std::cout << "CLASSIC RENDERING:" << std::endl;
    for (auto & pair : meshesToRender) {
        std::cout << "\t* Mesh type: [" << pair.first.second << "]" << std::endl;
    }

    std::cout << "Preprocessing scenes end.." << std::endl;
}

void TextureRenderer::render() {
    perspectiveCamera->Update();
    ortographicCamera->Update();

    // Render all meshes in instanced rendering mode
    for (auto & pair : map) {
        for (auto & pair2 : map[pair.first]) {
            switch (pair2.second.first->projection) {

                case PERSPECTIVE:
                    perspectiveCamera->renderInstanced(pair2.second.first, pair2.second.second);
                    break;
                case ORTOGRAPHIC:
                    ortographicCamera->renderInstanced(pair2.second.first, pair2.second.second);
                    break;
            }
        }
    }

    // Render all meshes in classic rendering mode
    for (auto & pair : meshesToRender) {
        switch (pair.first.first->projection) {

            case PERSPECTIVE:
                perspectiveCamera->render(pair.first.first, pair.second);
                break;
            case ORTOGRAPHIC:
                ortographicCamera->render(pair.first.first, pair.second);
                break;
        }
    }
}

void TextureRenderer::createFrameBuffer() {

    glGenFramebuffers(1, &framebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(width), static_cast<GLsizei>(width), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &dephRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, dephRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, dephRenderBuffer);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, DrawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
    }
}

void TextureRenderer::renderToTexture() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);
    render();
}

void TextureRenderer::updateSize(const glm::vec2 & newSize) {

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