#pragma once

class Component {
    public:
        Component() = default;
        virtual void Start() {}
        virtual void Update() {}
};