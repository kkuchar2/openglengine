#pragma once

#include <Engine/Engine.h>
#include <Scene/GameObjectFactory/GameObjectFactory.h>
#include <Components/Behaviour/RigidbodyComponent/Rigidbody.h>

std::shared_ptr<Scene> testSphereScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    auto sphereObject = GameObjectFactory::sphere(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f));

    auto rigidbody = std::make_shared<Rigidbody>();
    rigidbody->mass = 1.0f;
    rigidbody->restitution = 0.2f;

    sphereObject->addComponent(rigidbody);

    scene->addChild(sphereObject);
    return scene;
}