#ifndef OPENGL_COMPONENT_H
#define OPENGL_COMPONENT_H

#include "../MessageSystem/BusNode.h"

class Component : BusNode {
public:
    virtual void Start() {}
    virtual void Update() {}
};

#endif //OPENGL_COMPONENT_H