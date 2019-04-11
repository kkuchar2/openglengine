#pragma once

#include <memory>
#include <vector>
#include <Rendering/Mesh/MeshPrototype.h>

#include "Mesh/Mesh.h"
#include "Primitives/Cube.h"
#include "Shading/ShaderPool.h"
#include "Primitives/Line.h"
#include "Mesh/MeshType.h"
#include "Transform.h"

class GameObject {

    public:
        Transform transform;

        std::vector<std::shared_ptr<Component>> components;

        GameObject() = default;

        GameObject(const std::shared_ptr<Component> & component);

        void addComponent(const std::shared_ptr<Component> & component);

        std::shared_ptr<MeshPrototype> getMeshPrototype();

        MeshType getMeshType();

        static std::shared_ptr<GameObject> create(const std::shared_ptr<Component> & component);

        static std::shared_ptr<GameObject> create();
};