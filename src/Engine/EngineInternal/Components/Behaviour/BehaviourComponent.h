#pragma once

#include <Scene/GameObject/GameObjectBase.h>

class BehaviourComponent : public Component {

    public:
        GameObjectBase * gameObject = nullptr;

        void Start() override {

        }

        void Update() override {

        }

        void SetObject(GameObjectBase * obj);
};