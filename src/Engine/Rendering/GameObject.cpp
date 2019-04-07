#include "GameObject.h"
#include "../Behaviour/BehaviourComponent.h"

GameObject::GameObject(const std::shared_ptr<Component> & component) {
    addComponent(component);
}

void GameObject::addComponent(const std::shared_ptr<Component> & component) {
    std::shared_ptr<BehaviourComponent> behaviour = std::dynamic_pointer_cast<BehaviourComponent>(component);

    if (behaviour) {
       behaviour->SetObject(this);
    }

    components.push_back(component);
}

void GameObject::render(const std::shared_ptr<BaseCamera> & camera) {

    for (auto & componentPtr : components) {

        std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(componentPtr);

        if (mesh) {
            camera->Render(mesh);
        }
        else {
            std::shared_ptr<BehaviourComponent> behaviour = std::dynamic_pointer_cast<BehaviourComponent>(componentPtr);

            if (behaviour) {
                behaviour->Update();
            }
        }
    }
}

std::vector<std::shared_ptr<GameObject>> GameObject::createBoundingBox() {
    for (auto & componentPtr : components) {

        std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(componentPtr);

        if (mesh) {
            return createBoundingBoxLines(mesh->calculateBoundingBox());
        }
    }
    return std::vector<std::shared_ptr<GameObject>>();
}

void GameObject::prepare() {
    for (auto & componentPtr : components) {

        std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(componentPtr);

        if (mesh) {
            mesh->prepare();
        }
    }
}

std::vector<std::shared_ptr<GameObject>> GameObject::createBoundingBoxLines(BoundingBox boundingBox) {
    std::vector<std::shared_ptr<GameObject>> lines;

    glm::vec3 size = boundingBox.size;
    glm::vec3 center = boundingBox.center;
    glm::vec3 rotation = boundingBox.rotation;

    glm::vec3 start = glm::vec3(-size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
    glm::vec3 end = glm::vec3(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
    end = glm::vec3(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(-size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
    end = glm::vec3(-size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
    end = glm::vec3(size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(-size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
    end = glm::vec3(size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
    end = glm::vec3(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(-size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);
    end = glm::vec3(size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(-size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);
    end = glm::vec3(size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
    end = glm::vec3(-size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
    end = glm::vec3(size.x / 2.0f, -size.y / 2.0f, size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(-size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
    end = glm::vec3(-size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    start = glm::vec3(size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f);
    end = glm::vec3(size.x / 2.0f, -size.y / 2.0f, -size.z / 2.0f);

    lines.push_back(createLineObject(start, end, boundingBox));

    return lines;
}

std::shared_ptr<GameObject> GameObject::createLineObject(glm::vec3 start, glm::vec3 end, BoundingBox & boundingBox) {
    return std::make_shared<GameObject>(createLine(start, end, boundingBox.rotation, boundingBox.center));
}

std::shared_ptr<Line> GameObject::createLine(glm::vec3 start, glm::vec3 end, glm::vec3 rotation, glm::vec3 position) {
    std::shared_ptr<Line> line = std::make_shared<Line>();
    line->shader = ShaderPool::Instance().colorShader;
    line->setCoords(start, end);
    line->transform.position = position;
    line->transform.rotation = rotation;
    line->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    };
    line->prepare();
    return line;
}

std::shared_ptr<GameObject> GameObject::create() {
    return std::make_shared<GameObject>();
}

std::shared_ptr<GameObject> GameObject::create(const std::shared_ptr<Component> & component) {
    return std::make_shared<GameObject>(component);
}