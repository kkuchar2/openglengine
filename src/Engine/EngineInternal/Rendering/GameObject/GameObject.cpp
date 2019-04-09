#include "GameObject.h"
#include "../../Behaviour/BehaviourComponent.h"

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

std::vector<std::shared_ptr<GameObject>> GameObject::createBoundingBox() {
    for (auto & componentPtr : components) {

        std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(componentPtr);

        if (mesh) {
            return createBoundingBoxLines(calculateBoundingBox());
        }
    }
    return std::vector<std::shared_ptr<GameObject>>();
}

void GameObject::prepare() {
    auto mesh = getMesh();

    if (mesh) {
        mesh->prepare();
    }
}

std::shared_ptr<Mesh> GameObject::getMesh() {
    for (auto & componentPtr : components) {

        std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(componentPtr);

        if (mesh) {
            return mesh;
        }
    }

    return nullptr;
}

MeshType GameObject::getMeshType() {
    auto mesh = getMesh();

    if (mesh) {
        return mesh->type;
    }
    return NONE;
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
    auto lineObject = std::make_shared<GameObject>(createLine(start, end, boundingBox.rotation, boundingBox.center));
    lineObject->transform.position = boundingBox.center;
    lineObject->transform.rotation = boundingBox.rotation;
    return lineObject;
}

std::shared_ptr<Line> GameObject::createLine(glm::vec3 start, glm::vec3 end, glm::vec3 rotation, glm::vec3 position) {
    std::shared_ptr<Line> line = std::make_shared<Line>();
    line->shader = ShaderPool::Instance().colorShader;
    line->setCoords(start, end);
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

BoundingBox GameObject::calculateBoundingBox() {

    auto mesh = getMesh();

    if (!mesh) {
        BoundingBox bbBox {};
        bbBox.size = glm::vec3(0.0f);
        bbBox.center = glm::vec3(0.0f);
        bbBox.rotation = glm::vec3(0.0f);
        return bbBox;
    }

    float minFloat = std::numeric_limits<float>::min();
    float maxFloat = std::numeric_limits<float>::max();

    float minX = maxFloat;
    float minY = maxFloat;
    float minZ = maxFloat;

    float maxX = minFloat;
    float maxY = minFloat;
    float maxZ = minFloat;

    for (unsigned int vertexId = 0; vertexId < mesh->vertices.size() / 3; vertexId++) {
        glm::vec3 coords = glm::vec3(mesh->vertices[vertexId * 3], mesh->vertices[vertexId * 3 + 1], mesh->vertices[vertexId * 3 + 2]);

        if (coords.x > maxX) {
            maxX = coords.x;
        }

        if (coords.y > maxY) {
            maxY = coords.y;
        }

        if (coords.z > maxZ) {
            maxZ = coords.z;
        }

        if (coords.x < minX) {
            minX = coords.x;
        }

        if (coords.y < minY) {
            minY = coords.y;
        }

        if (coords.z < minZ) {
            minZ = coords.z;
        }
    }

    glm::vec3 size = glm::vec3(std::abs(maxX - minX), std::abs(maxY - minY), std::abs(maxZ - minZ));
    glm::vec3 center = glm::vec3(minX + (maxX - minX) / 2.0f, minY + (maxY - minY) / 2.0f, minZ + (maxZ - minZ) / 2.0f);
    glm::vec3 max = glm::vec3(maxX, maxY, maxZ);
    glm::vec3 min = glm::vec3(minX, minY, minZ);

    BoundingBox bbBox {};
    bbBox.size = transform.scale * size;
    bbBox.center = center * transform.scale + transform.position;
    bbBox.rotation = transform.rotation;
    return bbBox;
}