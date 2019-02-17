#ifndef OPENGL_TRIANGLEPRIMITIVE_H
#define OPENGL_TRIANGLEPRIMITIVE_H

#include "Mesh.h"

class TrianglePrimitive : public RenderObject {

    public:

        TrianglePrimitive() : RenderObject() { }

        void Render(int count) {
            RenderObject::Render(GL_TRIANGLES, count);
        }
};

#endif //OPENGL_TRIANGLEPRIMITIVE_H
