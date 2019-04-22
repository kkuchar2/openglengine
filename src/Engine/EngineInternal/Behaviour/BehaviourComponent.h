#pragma once

#include "GameObject/GameObjectBase.h"

class BehaviourComponent : public Component {

    public:
        GameObjectBase * gameObject = nullptr;

        void Update() override {}

        void SetObject(GameObjectBase * obj);
};