#pragma once

#include <memory>
#include <vector>

#include <Scene/BoundingBoxObject/BoundingBoxObject.h>
#include <Rendering/Mesh/Primitives/LineMeshComponent.h>
#include <Rendering/Mesh/MeshRenderer/MeshRenderer.h>

class BoundingBoxGenerator {
    public:
        static std::shared_ptr<BoundingBoxObject> calculateBoundingBox(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<GameObjectBase> & child);
};