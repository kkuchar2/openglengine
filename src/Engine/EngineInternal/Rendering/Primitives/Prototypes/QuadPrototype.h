#pragma once

#include <Rendering/Mesh/MeshPrototype.h>

class QuadPrototype : public MeshPrototype {
    public:
        QuadPrototype() : MeshPrototype() {
            meshType = QUAD;
        }
};