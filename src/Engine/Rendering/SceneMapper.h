#ifndef OPENGL_SCENEMAPPER_H
#define OPENGL_SCENEMAPPER_H

#include "UserScene.h"
#include "EngineScene.h"
#include "EngineObject.h"

class SceneMapper {
    public:
        static std::shared_ptr<EngineScene> mapToEngine(std::shared_ptr<UserScene> & userScene) {
            std::shared_ptr<EngineScene> engineScene = std::make_shared<EngineScene>();

            for (auto & gameObject : userScene->objectsToRender) {
                std::shared_ptr<EngineObject> engineObject = std::make_shared<EngineObject>(gameObject);
                engineScene->addObject(engineObject);
            }

            return engineScene;
        }
};

#endif //OPENGL_SCENEMAPPER_H
