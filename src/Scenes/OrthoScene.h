#pragma once

#include <Scene/Scene.h>

std::shared_ptr<Scene> orthoScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    return scene;
}