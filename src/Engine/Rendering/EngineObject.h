#pragma once

#include "GameObject.h"
#include "Primitives/Cube.h"
#include "Primitives/Line.h"

class EngineObject {
    public:
        std::shared_ptr<GameObject> gameObject;
        std::vector<std::shared_ptr<GameObject>> boundingBoxLines;
        std::vector<std::shared_ptr<GameObject>> normalsLines;

        EngineObject(const std::shared_ptr<GameObject> & gameObject);
        void render(const std::shared_ptr<BaseCamera> & camera) ;
        void prepare();
};