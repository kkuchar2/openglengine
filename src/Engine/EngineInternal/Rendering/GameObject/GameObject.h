#pragma once

#include "GameObjectBase.h"

#include <Rendering/Mesh/MeshPrototype.h>
#include "Mesh/Mesh.h"
#include "Primitives/Cube.h"
#include "Shading/ShaderPool.h"
#include "Primitives/Line.h"
#include "Mesh/MeshType.h"

class GameObject : public GameObjectBase {

    public:
        bool rendered = true;

        GameObject() = default;

        explicit GameObject(const std::shared_ptr<Component> & component);

        static std::shared_ptr<GameObject> create(const std::shared_ptr<Component> & component);

        static std::shared_ptr<GameObject> create();
};