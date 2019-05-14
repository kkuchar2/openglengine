#include "GameObject.h"

#include <Components/Behaviour/BehaviourComponent.h>
#include <Rendering/Mesh/MeshRenderer/MeshRenderer.h>

GameObject::GameObject(const glm::vec3 & position, const glm::vec3 & rotation, const glm::vec3 & scale) {
    transform.position = position;
    transform.rotation = rotation;
    transform.scale = scale;
}

void GameObject::update(const bool & refreshMatrices) {
    if (transform.dirty) {
        if (refreshMatrices) {
            transform.calculateModelMatrix();
        }

        if (boundingBox.get()) {
            boundingBox->update(transform, bbox, refreshMatrices);
        }

        transform.dirty = false;
    }

    for (auto & component : components) {
        component->Update();
    }
}
