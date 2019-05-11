#pragma once

#include <Rendering/Mesh/Mesh.h>

class Point : public Mesh {
    public:

        Point() : Mesh() {
            vertices = { 0.0f, -1.0f, 0.0 };
            indices = { 0 };
            uvs = { 0.0f, 0.0f };
            renderingMode = GL_POINTS;
        }
};