#ifndef OPENGL_CUBE_H
#define OPENGL_CUBE_H


#include <deps/linmath.h>
#include <map>


class Cube : public Mesh {
    public:

        explicit Cube() : Mesh() {

            vertices = {
                    // Front
                    -0.5f, -0.5f, -0.5f, // 0 - bottom lefts
                    -0.5f, 0.5f, -0.5f, // 1 - top left
                    0.5f, 0.5, -0.5f, // 2 - top right
                    0.5, -0.5f, -0.5f, // 3 - bottom right

                    // Back

                    -0.5f, -0.5f, 0.5, // 4 - bottom left
                    -0.5f, 0.5f, 0.5, // 5 - top left
                    0.5f, 0.5, 0.5, // 6 - top right
                    0.5, -0.5f, 0.5, // 7 - bottom right
            };

            indices = {
                    // front
                    0, 1, 2,
                    2, 3, 0,
                    // right
                    1, 5, 6,
                    6, 2, 1,
                    // back
                    7, 6, 5,
                    5, 4, 7,
                    // left
                    4, 0, 3,
                    3, 7, 4,
                    // bottom
                    4, 5, 1,
                    1, 0, 4,
                    // top
                    3, 2, 6,
                    6, 7, 3
            };

            uvs = {
                    0.0f, 0.0f, // bottom left
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    1.0f, 0.0f,  // bottom right

                    0.0f, 0.0f, // bottom left
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    1.0f, 0.0f,  // bottom right

                    0.0f, 0.0f, // bottom left
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    1.0f, 0.0f,  // bottom right

                    0.0f, 0.0f, // bottom left
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    1.0f, 0.0f,  // bottom right

                    0.0f, 0.0f, // bottom left
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    1.0f, 0.0f,  // bottom right

                    0.0f, 0.0f, // bottom left
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    1.0f, 0.0f  // bottom right
            };

            prepare();
        }
};


#endif //OPENGL_CUBE_H