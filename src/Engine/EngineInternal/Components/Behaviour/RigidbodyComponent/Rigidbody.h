#pragma once

#include "../BehaviourComponent.h"

class Rigidbody : public BehaviourComponent {

    public:

        float mass = 1.0f;
        float restitution = 1.0f;

        void Start() override;

        void Update() override;
};