#pragma once

#include "GameObjectBase.h"

#include <Rendering/Mesh/MeshPrototype.h>
#include "Mesh/Mesh.h"
#include "Primitives/Cube.h"
#include "Shading/ShaderPool.h"
#include "Primitives/Line.h"
#include "Mesh/MeshType.h"
#include "Transform.h"

class GameObject : public GameObjectBase {

    public:

        Transform transform;

        GameObject() = default;

        explicit GameObject(const std::shared_ptr<Component> & component);

        MeshType getMeshType();

        static std::shared_ptr<GameObject> create(const std::shared_ptr<Component> & component);

        static std::shared_ptr<GameObject> create();
};