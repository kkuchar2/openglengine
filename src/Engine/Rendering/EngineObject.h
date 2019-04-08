#pragma once

#include "GameObject.h"
#include "Primitives/Cube.h"
#include "Primitives/Line.h"
#include "Primitives/MeshType.h"

class EngineObject {
    public:
        std::shared_ptr<GameObject> gameObject;
        std::vector<std::shared_ptr<GameObject>> boundingBoxLines;
        std::vector<std::shared_ptr<GameObject>> normalsLines;

        EngineObject(const std::shared_ptr<GameObject> & gameObject);
        void prepare();
        MeshType getMeshType();
        std::shared_ptr<Mesh> getMesh();
        Transform getTransform();
};