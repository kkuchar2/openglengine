#pragma once

#include <Rendering/Mesh/Mesh.h>

class Cube : public Mesh {
    public:

        explicit Cube() : Mesh() {

            vertices = {
                    // back bottom
                     0.5f,  0.5f, -0.5f,
                     0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,

                    // back top
                    -0.5f, -0.5f, -0.5f,
                    -0.5f,  0.5f, -0.5f,
                     0.5f,  0.5f, -0.5f,

                    // front bottom
                     0.5f,  0.5f,  0.5f,
                    -0.5f, -0.5f,  0.5f,
                     0.5f, -0.5f,  0.5f,

                    // front top
                     0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f,  0.5f,
                    -0.5f, -0.5f,  0.5f,

                    // left top
                    -0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,

                    // left bottom
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f,  0.5f,
                    -0.5f,  0.5f,  0.5f,

                    // right top
                    0.5f, -0.5f, -0.5f,
                    0.5f,  0.5f, -0.5f,
                    0.5f,  0.5f,  0.5f,

                    // right bottom
                    0.5f, -0.5f, -0.5f,
                    0.5f,  0.5f,  0.5f,
                    0.5f, -0.5f,  0.5f,

                    // bottom top
                   -0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f,  0.5f,

                    // bottom bottom
                    0.5f, -0.5f,  0.5f,
                   -0.5f, -0.5f,  0.5f,
                   -0.5f, -0.5f, -0.5f,

                    // top top
                    0.5f,  0.5f,  0.5f,
                    0.5f,  0.5f, -0.5f,
                   -0.5f,  0.5f, -0.5f,

                    // top bottom
                   -0.5f,  0.5f, -0.5f,
                   -0.5f,  0.5f,  0.5f,
                    0.5f,  0.5f,  0.5f,

            };

            indices = {
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                31, 32, 33, 34, 35
            };

            uvs = {
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
            };
        }
};