#ifndef OPENGL_LINE_H
#define OPENGL_LINE_H

#include <deps/glad/glad.h>
#include "RenderObject.h"

class Line : public RenderObject {
    public:
        float vertices[6] = {
                0.0f, 0.0f, 0.0, // line start
                1.0f, 0.0f, 0.0, // line end
        };

        unsigned int indices[2] = { 0, 1 };

        float uvs[8]{};

        float normals[2]{};

        explicit Line() : RenderObject() {
            prepare(vertices, indices, uvs, normals, sizeof(vertices), sizeof(indices), sizeof(uvs), sizeof(normals));
        }

        void Render() override {
            RenderObject::Render(GL_LINES, 2);
        }

        void setCoords(glm::vec3 start, glm::vec3 end) {
            vertices[0] = start.x;
            vertices[1] = start.y;
            vertices[2] = start.z;
            vertices[3] = end.x;
            vertices[4] = end.y;
            vertices[5] = end.z;
            UpdateVertexBuffer(vertices, sizeof(vertices));
        }
};

#endif //OPENGL_LINE_H