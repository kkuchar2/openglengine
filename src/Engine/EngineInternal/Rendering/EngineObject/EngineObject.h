#pragma once

#include "GameObject/GameObject.h"
#include "Primitives/Cube.h"
#include "Primitives/Line.h"
#include "Mesh/MeshType.h"

class EngineObject {
    public:
        std::shared_ptr<GameObject> gameObject;

        EngineObject(const std::shared_ptr<GameObject> & gameObject);
        MeshType getMeshType();
        std::shared_ptr<MeshPrototype> getMeshPrototype();
        std::shared_ptr<Mesh> getMesh();
        Transform getTransform();
};