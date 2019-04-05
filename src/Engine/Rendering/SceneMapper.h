#pragma once

#include "UserScene.h"
#include "EngineScene.h"
#include "EngineObject.h"

class SceneMapper {
    public:
        static std::shared_ptr<EngineScene> mapToEngine(const std::shared_ptr<UserScene> & userScene) {
            std::shared_ptr<EngineScene> engineScene = std::make_shared<EngineScene>();

            for (auto & gameObject : userScene->objectsToRender) {
                engineScene->addObject(std::make_shared<EngineObject>(gameObject));
            }

            return engineScene;
        }
};