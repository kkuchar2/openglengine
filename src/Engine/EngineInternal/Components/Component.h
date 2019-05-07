#pragma once

class Component {
    public:
        Component() = default;
        virtual void Start() {}
        virtual void Update() {}

        template<typename T>
        static bool isTypeOf(const std::shared_ptr<Component> & ptr) {
            return std::dynamic_pointer_cast<T>(ptr).get() != nullptr;
        }

        template<typename T>
        static std::shared_ptr<T> asType(const std::shared_ptr<Component> & ptr) {
            return std::dynamic_pointer_cast<T>(ptr);
        }
};