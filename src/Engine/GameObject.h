#ifndef OPENGL_GAMEOBJECT_H
#define OPENGL_GAMEOBJECT_H

#include "../MessageSystem/BusNode.h"

class GameObject : BusNode {
    virtual void onNotify(Message message) {}
};

#endif //OPENGL_GAMEOBJECT_H