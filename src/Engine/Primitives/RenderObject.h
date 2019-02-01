#ifndef OPENGL_RENDEROBJECT_H
#define OPENGL_RENDEROBJECT_H

#include <memory>

#include "Transform.h"
#include "../TextureLoader.h"

enum RenderFlag {
    ORTHOGRAPHIC,
    PERSPECTIVE
};

class RenderObject {
    public:
        RenderFlag renderFlag;
        GLuint textureId = 0;

        std::shared_ptr<Shader> shader;

        GLuint vao{};
        GLuint vbo{};
        GLuint uvbo{};
        GLuint ibo{};

        Transform transform;

        void loadTexture(const char * path) {
            textureId = TextureLoader::load(path);
        }

        void useRendering(RenderFlag renderFlag) {
            this->renderFlag = renderFlag;
        }

        void useShader(std::shared_ptr<Shader> & shader) {
            this->shader = shader;
        }

        void prepare(float * vertices, unsigned int * indices, float * uvs, int vSize, int iSize, int uvSize) {
            prepare_common(vertices, indices, vSize, iSize);

            // Create UV buffer
            glGenBuffers(1, &uvbo);
            glBindBuffer(GL_ARRAY_BUFFER, uvbo);
            glBufferData(GL_ARRAY_BUFFER, uvSize, uvs, GL_DYNAMIC_DRAW);

            // Enable uv attribute array and set uv attribute pointers
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

            glBindVertexArray(0);
        }

        void prepare(float * vertices, unsigned int * indices, int vSize, int iSize) {
            prepare_common(vertices, indices, vSize, iSize);
            glBindVertexArray(0);
        }

        void prepare_common(float * vertices, unsigned int * indices, int vSize, int iSize) {
            // Create vertex attribute buffer
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            // Create index buffer
            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indices, GL_STATIC_DRAW);

            // Create vertex buffer
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vSize, vertices, GL_DYNAMIC_DRAW);

            // Enable vertex attribute array and set vertex attribute pointers
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }

        void UpdateVertexBuffer(float * vertices, int vSize) {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vSize, vertices, GL_DYNAMIC_DRAW);
        }

        virtual void Render() {}

        void Render(GLenum mode, int count) {
            glBindVertexArray(vao);
            glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
        }
};

#endif //OPENGL_RENDEROBJECT_H
