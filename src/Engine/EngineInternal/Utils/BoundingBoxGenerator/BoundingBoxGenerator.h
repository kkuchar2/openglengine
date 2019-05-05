#pragma once

#include <memory>
#include <vector>
#include <Scene/GameObject/GameObject.h>
#include <Rendering/Primitives/LinePrototype.h>

class BoundingBoxGenerator {
    public:
        static void calculateBoundingBox(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<GameObject> & child);
};