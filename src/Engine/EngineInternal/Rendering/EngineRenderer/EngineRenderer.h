#pragma once

#include <glad.h>

#include <Rendering/Camera/OrtographicCamera/OrtographicCamera.h>
#include <Rendering/Camera/PerspectiveCamera/PerspectiveCamera.h>
#include <Scene/Scene.h>

#include "Rendering/RenderingManager/RenderingManager.h"

class EngineRenderer {

    private:

        std::shared_ptr<RenderingManager> renderingManager;

        std::shared_ptr<BaseCamera> getCamera(const Projection & projection);

    public:

        double width = 1.0;
        double height = 1.0;

        GLuint mainTexture = 0;
        GLuint dephRenderBuffer = 0;
        GLuint framebufferName = 0;

        std::shared_ptr<OrtographicCamera> ortographicCamera;
        std::shared_ptr<PerspectiveCamera> perspectiveCamera;

        explicit EngineRenderer(const std::shared_ptr<Window> & window, const std::shared_ptr<PhysicsEngine> & physicsEngine);

        void addScene(const std::shared_ptr<Scene> & scene);

        void prepare();

        void renderFrame();

        void createFramebuffer();

        void setTargetSize(const glm::vec2 & size);

        void setBoundingBoxesEnabled(const bool & enabled);
};