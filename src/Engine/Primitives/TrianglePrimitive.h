#ifndef OPENGL_TRIANGLEPRIMITIVE_H
#define OPENGL_TRIANGLEPRIMITIVE_H

#include "RenderObject.h"

class TrianglePrimitive : public RenderObject {

    public:

        explicit TrianglePrimitive(Shader * shader) : RenderObject(shader) {}

        void Render() override {}

        void Render(int count) {
            RenderObject::Render(GL_TRIANGLES, count);
        }
};

#endif //OPENGL_TRIANGLEPRIMITIVE_H
