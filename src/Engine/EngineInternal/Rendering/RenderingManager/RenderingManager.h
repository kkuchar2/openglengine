#pragma once

#include <Scene/GameObject/GameObject.h>
#include <Engine/EngineInternal/Rendering/Mesh/MeshInfo.h>
#include <Rendering/Camera/PerspectiveCamera/PerspectiveCamera.h>
#include <PhysicsEngine/PhysicsEngine.h>

class RenderingManager {
    public:


        bool physicsEnabled = false;
        bool enableBoundingBoxes = false;

        std::vector<std::shared_ptr<GameObject>> children;

        std::vector<std::shared_ptr<MeshInfo>> meshes;

        std::map<std::string, std::shared_ptr<MeshInfo>> instancedMeshes;

        std::shared_ptr<PhysicsEngine> physicsEngine;

        RenderingManager();

        void addChild(const std::shared_ptr<GameObject> & child);

        void preprocessScenes();

        void Update(const std::shared_ptr<PerspectiveCamera> & camera);

        void logRenderMap();
};