#pragma once

#include <Engine/EngineInternal/Utils/Timer.h>
#include "../BehaviourComponent.h"

class Rotator : public BehaviourComponent {

    private:
        Timer timer;

    public:
        void Start() override;
        void Update() override;
};