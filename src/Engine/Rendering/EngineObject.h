#pragma once

#include "GameObject.h"
#include "Primitives/Cube.h"
#include "Primitives/Line.h"

class EngineObject {
    public:
        std::shared_ptr<GameObject> gameObject;
        std::shared_ptr<GameObject> boundingBox;
        std::vector<std::shared_ptr<GameObject>> normalsLines;

        EngineObject(std::shared_ptr<GameObject> & gameObject) {
            this->gameObject = gameObject;
        }

        template<typename T, typename std::enable_if<std::is_base_of<BaseCamera, T>::value>::type* = nullptr>
        void Render(std::shared_ptr<T> & camera) {
            if (gameObject) {
                gameObject->Render(camera);
            }

            if (boundingBox) {
                boundingBox->Render(camera);
            }

            for (auto & line : normalsLines) {
                if (line) {
                    line->Render(camera);
                }
            }
        }

        void Prepare() {
            boundingBox = gameObject->CreateBoundingBox();
        }
};