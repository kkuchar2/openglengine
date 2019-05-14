#pragma once

#include <glad.h>

#include <Rendering/Camera/OrtographicCamera/OrtographicCamera.h>
#include <Rendering/Camera/PerspectiveCamera/PerspectiveCamera.h>
#include <Scene/Scene.h>

#include "Rendering/RenderingManager/RenderingManager.h"

class EngineRenderer {

    private:

        std::shared_ptr<RenderingManager> renderingManager;

        std::shared_ptr<BaseCamera> getCamera(const Projection & projection, const int & idx);

    public:
        double widths[2] = {1.0, 1.0};
        double heights[2] = {1.0, 1.0};

        GLuint textures[2];
        GLuint framebuffers[2];
        GLuint depthBuffers[2];

        std::shared_ptr<OrtographicCamera> ortographicCamera;
        std::shared_ptr<PerspectiveCamera> perspectiveCameras[2];

        explicit EngineRenderer(const std::shared_ptr<Window> & window, const std::shared_ptr<PhysicsEngine> & physicsEngine);

        void addScene(const std::shared_ptr<Scene> & scene);

        void prepare();

        void renderFrame();

        void createFramebuffers();

        void setTargetSize(const glm::vec2 & size, const int & idx);

        void setBoundingBoxesEnabled(const bool & enabled);

        void testFrustrum(const std::shared_ptr<RenderInfo> & info);
};