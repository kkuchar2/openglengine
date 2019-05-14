#pragma once

#include <Engine/EngineInternal/Utils/Timer.h>
#include "../BehaviourComponent.h"

class Rotator : public BehaviourComponent {

    private:

        int a = 0;

        Timer timer;

    public:
        void Start() override;
        void Update() override;
};