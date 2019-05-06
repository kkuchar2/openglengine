#include "GameObject.h"

#include <Engine/EngineInternal/Components/Behaviour/BehaviourComponent.h>

GameObject::GameObject() = default;

GameObject::GameObject(const std::shared_ptr<Component> & component) {
    addComponent(component);
}

void GameObject::addComponent(const std::shared_ptr<Component> & component) {

    auto behaviour = castComponent<BehaviourComponent>(component);

    if (behaviour) {
        behaviour->SetObject(static_cast<GameObject *>(this));
    }

    auto proto = castComponent<MeshComponent>(component);

    if (proto) {
        meshProto = proto;
    }

    components.push_back(component);
}

void GameObject::init() {
    transform.init();
    if (!boundingBox.get()) return;

    boundingBox->transform.position = transform.position;
    boundingBox->transform.pivot = transform.scale * bbox.center;
    boundingBox->transform.rotation = transform.rotation;
    boundingBox->transform.scale = transform.scale * bbox.size;

    boundingBox->transform.init();
}

void GameObject::Update() {
    transform.calculateModelMatrix();

    if (!boundingBox.get()) return;

    boundingBox->transform.position = transform.position;
    boundingBox->transform.pivot = transform.scale * bbox.center;
    boundingBox->transform.rotation = transform.rotation;
    boundingBox->transform.scale = transform.scale * bbox.size;

    boundingBox->transform.init();
    boundingBox->transform.calculateModelMatrix2();

    for (auto & component : components) {
        component->Update();
    }
}

std::shared_ptr<GameObject>
GameObject::create(const glm::vec3 & position, const glm::vec3 & rotation, const glm::vec3 & scale) {
    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
    obj->transform.position = position;
    obj->transform.rotation = rotation;
    obj->transform.scale = scale;
    return obj;
}
