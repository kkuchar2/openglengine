#ifndef OPENGL_QUAD_H
#define OPENGL_QUAD_H

#include "TrianglePrimitive.h"

static float vertices[] = {
    -1.0f, -1.0f,  0.0, // 0 - bottom left
    -1.0f,  1.0f,  0.0, // 1 - top left
     1.0f,  1.0,   0.0, // 2 - top right
     1.0,  -1.0f,  0.0, // 3 - bottom right
};

static unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

static float uvs[] {
    0.0f, 0.0f, // bottom left
    0.0f, 1.0f, // top left
    1.0f, 1.0f, // top right
    1.0f, 0.0f  // bottom right
};

static int count = 6;

class Quad : public TrianglePrimitive {
    public:
        explicit Quad(Shader * shader) : TrianglePrimitive(shader) {
            prepare(vertices, indices, uvs, sizeof(vertices), sizeof(indices), sizeof(uvs));
        }

        void Render() override {
            TrianglePrimitive::Render(count);
        }
};

#endif //OPENGL_QUAD_H
