#pragma once

#include <glad.h>

#include "Camera/BaseCamera.h"
#include "UserScene.h"
#include "Camera/PerspectiveCamera.h"
#include "EngineScene.h"

class TextureRenderer {

    public:
        double width = 400.0;
        double height = 400.0;

        GLuint texture {};
        GLuint dephRenderBuffer {};
        GLuint framebufferName = 0;

        std::map<Projection, std::vector<std::shared_ptr<EngineScene>>> scenes = {{ PERSPECTIVE, {} },{ ORTOGRAPHIC, {} }};

        std::vector<std::shared_ptr<BaseCamera>> cameras;

        TextureRenderer(std::shared_ptr<Window> & windowPtr) {
            createFrameBuffer();
        }

        template<typename T, typename std::enable_if<std::is_base_of<BaseCamera, T>::value>::type* = nullptr>
        void addCamera(std::shared_ptr<T> camera) {
            cameras.push_back(camera);
        }

        void addScene(std::shared_ptr<EngineScene> scene) {
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
                camera->Update();

                for (auto & scene : scenes.at(camera->projection)) {
                    scene->render(camera);
                }
            }
        }

        void createFrameBuffer() {

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
            GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
            glDrawBuffers(1, DrawBuffers);

            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                std::cout << "Framebuffer is not complete!" << std::endl;
            }
        }

        int frameCounter = 0;

        void renderToTexture() {
            frameCounter++;

            glBindFramebuffer(GL_FRAMEBUFFER, framebufferName);
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, width, height);
            renderScenes();
        }

        void updateSize(glm::vec2 & newSize) {

            if (abs(newSize.x - width) < 1.0f && abs(newSize.y - height) < 1.0f) {
                return;
            }

            width = newSize.x;
            height = newSize.y;

            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
            glBindTexture(GL_TEXTURE_2D, 0);

            glBindRenderbuffer(GL_RENDERBUFFER, dephRenderBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }
};