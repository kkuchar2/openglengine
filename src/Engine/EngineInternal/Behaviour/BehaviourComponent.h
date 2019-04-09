#pragma once

#include "GameObject/GameObject.h"

class BehaviourComponent : public Component {
    public:
        GameObject * obj;

        virtual void Update() {}

        void SetObject(GameObject * obj);
};