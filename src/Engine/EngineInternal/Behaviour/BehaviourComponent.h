#pragma once

#include "GameObject/GameObjectBase.h"

class BehaviourComponent : public Component {
    public:
        GameObjectBase * obj;

        virtual void Update() {}

        void SetObject(GameObjectBase * obj);
};