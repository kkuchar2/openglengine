#pragma once

#include "SceneDefinition/UserScene.h"
#include "SceneDefinition/EngineScene.h"
#include "EngineObject/EngineObject.h"

class SceneMapper {
    public:
        static std::shared_ptr<EngineScene> mapToEngine(const std::shared_ptr<UserScene> & userScene) {
            std::shared_ptr<EngineScene> engineScene = std::make_shared<EngineScene>();

            engineScene->projection = userScene->projection;

            for (auto & gameObject : userScene->objectsToRender) {
                engineScene->addObject(std::make_shared<EngineObject>(gameObject));
            }

            return engineScene;
        }
};