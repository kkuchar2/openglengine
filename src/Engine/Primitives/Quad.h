#ifndef OPENGL_QUAD_H
#define OPENGL_QUAD_H

class Quad : public RenderObject {
    public:
        float vertices[12] = {
                -1.0f, -1.0f,  0.0, // 0 - bottom left
                -1.0f,  1.0f,  0.0, // 1 - top left
                1.0f,  1.0,   0.0, // 2 - top right
                1.0,  -1.0f,  0.0, // 3 - bottom right
        };

        unsigned int indices[6] = {
                0, 1, 2,
                2, 3, 0
        };

        float uvs[8] {
                0.0f, 0.0f, // bottom left
                0.0f, 1.0f, // top left
                1.0f, 1.0f, // top right
                1.0f, 0.0f  // bottom right
        };

        float normals[12]{};

        explicit Quad() : RenderObject() {
            prepare(vertices, indices, uvs, normals, sizeof(vertices), sizeof(indices), sizeof(uvs), sizeof(normals));
        }

        void Render() override {
            RenderObject::Render(GL_TRIANGLES, 6);
        }
};

#endif //OPENGL_QUAD_H
