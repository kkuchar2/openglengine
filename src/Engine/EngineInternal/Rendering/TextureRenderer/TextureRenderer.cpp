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

    // Create single mesh as base for instantiation
    quadMesh = std::make_shared<Quad>();
    quadMesh->shader = ShaderPool::Instance().colorShader;
    quadMesh->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0, 0.0, 0.0, 1.0));
    };


    // TODO:

    /**
     * Group objects based on projection, type, material and ? instantiation enabled
     */

    // Create model matrices data
    std::vector<glm::mat4> matrices;

    // For now assume that all objects are quads and ortho projection as camera


    //     glm::mat4 mvp = getProjectionMatrix() * getViewMatrix() * m;

    // Grab all objects from all scenes
    for (auto & pair : scenes) {
        for (auto & scene : pair.second) {

            auto projection = scene->projection;

            for (auto & engineObject : scene->objects) {

                switch(projection) {

                    case PERSPECTIVE:
                        matrices.push_back(perspectiveCamera->createModelMatrix(engineObject));
                        break;
                    case ORTOGRAPHIC:
                        matrices.push_back(ortographicCamera->createModelMatrix(engineObject));
                        break;
                }

                quadInstancesCount++;
            }
        }
    }

    quadMesh->modelMatrices = matrices;
    quadMesh->prepare();
}

void TextureRenderer::render() {
    perspectiveCamera->Update();
    ortographicCamera->Update();
    perspectiveCamera->render(quadMesh, quadInstancesCount);
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