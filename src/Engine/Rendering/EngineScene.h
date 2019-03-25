#pragma once

#include "GameObject.h"
#include "Camera/BaseCamera.h"
#include "Mesh.h"
#include "EngineObject.h"

class EngineScene {
    public:

        Projection projection = PERSPECTIVE;

        std::vector<std::shared_ptr<EngineObject>> objects;

        EngineScene() = default;

        void addObject(std::shared_ptr<EngineObject> & obj) {
            objects.push_back(obj);
        }

        void prepare() {
            std::for_each(objects.begin(), objects.end(), [](auto obj){ obj->Prepare(); });
        }

        template<typename T, typename std::enable_if<std::is_base_of<BaseCamera, T>::value>::type* = nullptr>
        void render(std::shared_ptr<T> & camera) {
            std::for_each(objects.begin(), objects.end(), [&camera](auto obj){ obj->Render(camera); });
        }
};