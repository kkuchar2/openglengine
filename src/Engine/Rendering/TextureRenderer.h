#ifndef OPENGL_TEXTURERENDERER_H
#define OPENGL_TEXTURERENDERER_H

#include <deps/glad/glad.h>

#include "Camera/BaseCamera.h"
#include "RenderScene.h"
#include "Camera/PerspectiveCamera.h"

class TextureRenderer {

    public:
        double texWidth = 400.0;
        double texHeight = 400.0;

        GLuint renderedTexture;
        GLuint depthrenderbuffer;
        GLuint FramebufferName = 0;


        std::map<Projection, std::vector<std::shared_ptr<RenderScene>>> scenes = {{ PERSPECTIVE, {} },{ ORTOGRAPHIC, {} }};

        std::vector<std::shared_ptr<BaseCamera>> cameras;

        TextureRenderer(std::shared_ptr<Window> & windowPtr) {
            createFrameBuffer();
        }

        template<typename T, typename std::enable_if<std::is_base_of<BaseCamera, T>::value>::type* = nullptr>
        void addCamera(std::shared_ptr<T> & camera) {
            cameras.push_back(camera);
        }

        void addScene(std::shared_ptr<RenderScene> & scene) {
            scenes.at(scene->projection).push_back(scene);
        }

        void prepareScenes() {
            for (auto & pair : scenes) {
                for (auto & scene : pair.second) {
                    scene->prepare();
                }
            }
        }

        void renderScenes() {
            for (auto & camera : cameras) {

                if (camera->projection == PERSPECTIVE) {
                    std::shared_ptr<PerspectiveCamera> pCamera = std::dynamic_pointer_cast<PerspectiveCamera>(camera);
                    pCamera->aspectRatio = static_cast<float>(texWidth / texHeight);
                }

                camera->Update();

                for (auto & scene : scenes.at(camera->projection)) {
                    scene->render(camera);
                }
            }
        }

        void updateSize(float width, float height) {

            if (abs(texWidth - width) > 2.0 || abs(texHeight - height) > 2.0) {
                texWidth = width;
                texHeight = height;
                createFrameBuffer();
            }
        }

        void createFrameBuffer() {

            glGenFramebuffers(1, &FramebufferName);
            glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

            glGenTextures(1, &renderedTexture);
            glBindTexture(GL_TEXTURE_2D, renderedTexture);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(texWidth), static_cast<GLsizei>(texHeight), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            glGenRenderbuffers(1, &depthrenderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, static_cast<GLsizei>(texWidth), static_cast<GLsizei>(texHeight));
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

            glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

            // Set the list of draw buffers.
            GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
            glDrawBuffers(1, DrawBuffers);

            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                std::cout << "Framebuffer is not complete!" << std::endl;
            }
        }

        void renderToTexture() {
            glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, texWidth, texHeight);
            renderScenes();
        }

        void updateSize(glm::vec2 & newSize) {
            texWidth = newSize.x;
            texHeight = newSize.y;

            glBindTexture(GL_TEXTURE_2D, renderedTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(texWidth), static_cast<GLsizei>(texHeight), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
            glBindTexture(GL_TEXTURE_2D, 0);

            glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, static_cast<GLsizei>(texWidth), static_cast<GLsizei>(texHeight));
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }
};

#endif //OPENGL_TEXTURERENDERER_H
