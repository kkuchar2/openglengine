#pragma once

#include <Rendering/GameObject/GameObject.h>
#include "GameObject/GameObjectBase.h"

class BehaviourComponent : public Component {

    public:
        GameObject * gameObject = nullptr;

        void Start() override {

        }

        void Update() override {

        }

        void SetObject(GameObject * obj);
};