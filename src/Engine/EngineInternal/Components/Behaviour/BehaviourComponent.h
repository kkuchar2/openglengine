#pragma once

#include <Scene/GameObject/GameObject.h>

class BehaviourComponent : public Component {

    public:
        GameObject * gameObject = nullptr;

        void Start() override {

        }

        void Update() override {

        }

        void SetObject(GameObject * obj);
};