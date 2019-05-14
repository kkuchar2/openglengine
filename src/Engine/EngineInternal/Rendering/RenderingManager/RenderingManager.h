#pragma once

#include <Scene/GameObject/GameObject.h>
#include <Rendering/Mesh/MeshBuilder.h>
#include <Rendering/Mesh/RenderInfo.h>
#include <Rendering/Camera/PerspectiveCamera/PerspectiveCamera.h>
#include <PhysicsEngine/PhysicsEngine.h>
#include <Utils/BoundingBoxGenerator/BoundingBoxGenerator.h>
#include <Components/Behaviour/RigidbodyComponent/Rigidbody.h>

class RenderingManager {

    private:

        void addBoundingBox(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<GameObjectBase> & parent);

    public:
        bool physicsEnabled = false;
        bool enableBoundingBoxes = false;

        std::vector<std::shared_ptr<GameObject>> children;

        std::vector<std::shared_ptr<RenderInfo>> renderInfos;

        std::map<std::string, std::shared_ptr<RenderInfo>> instancedRenderInfos;

        std::shared_ptr<PhysicsEngine> physicsEngine;

        RenderingManager();

        void preprocessScenes();

        void logRenderMap();
};