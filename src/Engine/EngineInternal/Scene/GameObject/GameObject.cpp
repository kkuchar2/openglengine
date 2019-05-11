#include "GameObject.h"

#include <Components/Behaviour/BehaviourComponent.h>
#include <Rendering/Mesh/MeshRenderer/MeshRenderer.h>

GameObject::GameObject() = default;

GameObject::GameObject(const std::shared_ptr<Component> & component) {
    addComponent(component);
}

std::shared_ptr<Component> GameObject::addComponent(const std::shared_ptr<Component> & component) {

    if (Component::isTypeOf<BehaviourComponent>(component)) {
        Component::asType<BehaviourComponent>(component)->SetObject(this);
    }

    components.push_back(component);

    return components[components.size() - 1];
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

void GameObject::update() {

    if (transform.dirty) {
        transform.rotationMatrix = MatrixUtils::rotationMatrix(transform.rotation);
        transform.scaleMatrix = MatrixUtils::scaleMatrix(transform.scale);
        transform.positionMatrix = MatrixUtils::translationMatrix(transform.position);
        transform.calculateModelMatrix();
        transform.dirty = false;
    }

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
