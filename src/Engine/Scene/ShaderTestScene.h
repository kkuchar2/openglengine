#pragma once

#include "../Engine.h"
#include "../Behaviour/BehaviourComponent.h"

class SphereUpdateBehaviour : public BehaviourComponent {
    void Update() override {
        //std::cout << "Sphere on update, parent: " << obj << std::endl;
    }
};

std::shared_ptr<UserScene> shaderTestScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(1.2f, 1.0f, 2.0f);

    std::shared_ptr<Mesh> sphereMesh = Mesh::create("../resources/models/sphere.obj");
    sphereMesh->shader = ShaderPool::Instance().diffuseShader;
    sphereMesh->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    sphereMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<GameObject> sphereObject = GameObject::create();

    sphereObject->addComponent(sphereMesh);
    sphereObject->addComponent(std::make_shared<SphereUpdateBehaviour>());
    sphereObject->drawBoundingBox = true;

    scene->addObject(sphereObject);

    return scene;
}