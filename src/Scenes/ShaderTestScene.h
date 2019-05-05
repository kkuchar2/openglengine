#pragma once

#include <Engine/Engine.h>
#include "../Engine/EngineInternal/Behaviour/Component.h"

class SphereUpdateBehaviour : public Component {
    void Update() override {
        //std::cout << "Sphere on update, parent: " << obj << std::endl;
    }
};

std::shared_ptr<Scene> shaderTestScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(1.2f, 1.0f, 2.0f);
    std::shared_ptr<Mesh> sphereMesh = Mesh::create("../resources/models/sphere.obj");
    sphereMesh->shader = ShaderPool::Instance().diffuseShader;
    sphereMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setglm::vec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setglm::glm::vec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setglm::glm::vec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<GameObject> sphereObject = GameObject::create();
    sphereObject->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

    sphereObject->addComponent(sphereMesh);
    sphereObject->addComponent(std::make_shared<SphereUpdateBehaviour>());
    sphereObject->drawBoundingBox = true;

    scene->addChild(sphereObject);

    return scene;
}