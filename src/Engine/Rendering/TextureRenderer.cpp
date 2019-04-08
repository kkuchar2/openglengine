#include "TextureRenderer.h"

TextureRenderer::TextureRenderer(std::shared_ptr<Window> & window) {
    createFrameBuffer();
    ortographicCamera = std::make_shared<OrtographicCamera>(window);
    perspectiveCamera = std::make_shared<PerspectiveCamera>(window, glm::vec3(0.0, 5.0, 10.0));
}

void TextureRenderer::addScene(const std::shared_ptr<EngineScene> & scene) {
    scenes.at(scene->projection).push_back(scene);
}

void TextureRenderer::prepare() {

    for (auto & pair : scenes) {
        for (auto & scene : pair.second) {
            for (auto & engineObject : scene->objects) {
                objectsToRender.at(engineObject->getMeshType()).push_back(std::make_pair(engineObject, scene->projection));
            }
        }
    }

    // So the idea is that we render only first mesh, but include all n * mvp for all meshes onto attribute
    // of shader that is used with that first mesh rendering
    // and instantiate that n times

    /**
     *
     * For now it renders something. Thank god.
     *
     * But MVP are  not sent as whole (right now only sent 4 first parameters - see Mesh.cpp comment in Render method)
     * so it renders weird stuff. But many.
     *
     * 10000 colored quads and orthographic projection render on GTX 1060 6GB with ~700 FPS without vSync enabled.
     *
     * Future:
     * 1. Streamline all objects from all scenes + their additional objects (e.g. bounding boxes)
     * 2. Group all objects based on meshes type (quad / line / bunny / random loaded mesh etc.)
     * 3. For each unique mesh render it's n representations with n * mvp pregenerated data
     *    (mvp data for each mesh has information of each object transform
     *    + projection from used camera by scene, that contains that object)
     * 4. Try to add optional instancing parameter for specific mesh or mesh type
     *      (mesh type - all meshes with that type may be rendered / not rendered using instancing
     *       specific mesh -  only that mesh will be rendered with / without instancing)
     *
     *     NOTE:  If only one specific mesh has instancing enabled it's the same
     *            as rendering without instancing -> single drawcall
     *
     * 5. Rethink what to do with different types of shaders and how to make them
     *    have optional instancing enablement
     *
     *
     *    BTW: Clean up base camera like in this branch - it doesnt need scale corention, time etc. anymore
     */
    std::cout << "QUADS: " << objectsToRender.at(QUAD).size() << std::endl;

    int counter = 0;

    auto quadObjects = objectsToRender.at(QUAD);

    // Create mvps
    std::vector<glm::mat4> data;

    for (auto & pair : quadObjects) {
        data.push_back(ortographicCamera->createMVP(pair.first));
    }

    if (quadObjects.size() > 0) {
        auto firstGameObject = quadObjects[0].first;
        auto mesh = firstGameObject->getMesh();

        if (mesh) {
            mesh->instancedMVPs = data;
        }

        firstGameObject->prepare();
    }
}

void TextureRenderer::render() {

    perspectiveCamera->Update();
    ortographicCamera->Update();

    auto quadObjects = objectsToRender.at(QUAD);

    if (quadObjects.size() > 0) {
        auto firstGameObject = quadObjects[0].first;
        ortographicCamera->render(firstGameObject, quadObjects.size());
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

    if (abs(newSize.x - width) < 1.0f && abs(newSize.y - height) < 1.0f) return;

    width = newSize.x;
    height = newSize.y;

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, dephRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}