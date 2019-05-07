#pragma once

#include "MeshComponent.h"

class SurfaceMeshComponent : public MeshComponent {
    public:
        float width = 10.0;
        float height = 10.0;

        SurfaceMeshComponent() : MeshComponent(SURFACE) {}

        static std::shared_ptr<SurfaceMeshComponent> create() {
            return std::make_shared<SurfaceMeshComponent>();
        }
};