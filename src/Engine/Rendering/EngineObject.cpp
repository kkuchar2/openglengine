#include "EngineObject.h"

EngineObject::EngineObject(const std::shared_ptr<GameObject> & gameObject) {
    this->gameObject = gameObject;
}

void EngineObject::render(const std::shared_ptr<BaseCamera> & camera) {
    if (gameObject) {
        gameObject->render(camera);
    }

    if (gameObject->drawBoundingBox) {
        for (auto & lineObj : boundingBoxLines) {
            lineObj->render(camera);
        }
    }

    for (auto & line : normalsLines) {
        if (line) {
            line->render(camera);
        }
    }
}

void EngineObject::prepare() {
    gameObject->prepare();

    if (gameObject->drawBoundingBox) {
        boundingBoxLines = gameObject->createBoundingBox();
    }
}