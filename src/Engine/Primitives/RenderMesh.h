#ifndef OPENGL_RENDERMESH_H
#define OPENGL_RENDERMESH_H

#include <deps/glad/glad.h>
#include "RenderObject.h"

class RenderMesh : public RenderObject {
    public:

        int size;

        explicit RenderMesh(std::vector<float> & vertices, std::vector<unsigned int> & indices, std::vector<float> & uvs, std::vector<float> & normals) : RenderObject() {
            prepare(&vertices[0],&indices[0], &uvs[0], &normals[0],
                    vertices.size() * sizeof(float),
                    indices.size() * sizeof(unsigned int),
                    uvs.size() * sizeof(float),
                    normals.size() * sizeof(float)
            );

            size = indices.size();
        }

        void Render() override {
            RenderObject::Render(GL_TRIANGLES, size);
        }
};


#endif //OPENGL_RENDERMESH_H
