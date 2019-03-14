#ifndef OPENGL_QUAD_H
#define OPENGL_QUAD_H

#include "../Mesh.h"

class Quad : public Mesh {
    public:

        Quad() : Mesh() {
            vertices =  {
                    -1.0f, -1.0f,  0.0, // 0 - bottom left
                    -1.0f,  1.0f,  0.0, // 1 - top left
                    1.0f,  1.0,   0.0, // 2 - top right
                    1.0,  -1.0f,  0.0, // 3 - bottom right
            };

            indices = {
                    0, 1, 2,
                    2, 3, 0
            };

            uvs = {
                    0.0f, 0.0f, // bottom left
                    0.0f, 1.0f, // top left
                    1.0f, 1.0f, // top right
                    1.0f, 0.0f  // bottom right
            };
        }
};

#endif //OPENGL_QUAD_H
