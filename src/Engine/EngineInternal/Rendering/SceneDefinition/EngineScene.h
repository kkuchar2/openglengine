#pragma once

#include "GameObject/GameObject.h"
#include "Camera/BaseCamera.h"
#include "Mesh/Mesh.h"
#include "EngineObject/EngineObject.h"
#include <chrono>

class EngineScene {
    public:
        Projection projection = PERSPECTIVE;

        std::vector<std::shared_ptr<EngineObject>> objects;

        EngineScene() = default;

        void addObject(const std::shared_ptr<EngineObject> & obj) {
            objects.push_back(obj);
        }

        void prepare() {
            auto t_start = std::chrono::high_resolution_clock::now();

            for (auto & obj : objects) {
                obj->prepare();
            }

            auto t_end = std::chrono::high_resolution_clock::now();

            double elaspedTimeMs = std::chrono::duration<double, std::milli>(t_end-t_start).count();
            std::cout << elaspedTimeMs << " ms" << std::endl;
        }
};