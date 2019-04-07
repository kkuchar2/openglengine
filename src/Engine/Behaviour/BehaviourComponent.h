#pragma once

#include "../Rendering/GameObject.h"

class BehaviourComponent : public Component {
    public:
        GameObject * obj;

        virtual void Update() {}

        void SetObject(GameObject * obj);
};