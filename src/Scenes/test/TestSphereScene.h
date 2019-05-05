#pragma once

#include <Engine/Engine.h>
#include <Scene/GameObjectFactory/GameObjectFactory.h>

std::shared_ptr<Scene> testSphereScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->addChild(GameObjectFactory::sphere());
    return scene;
}