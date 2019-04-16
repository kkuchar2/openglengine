#pragma once

#include <Rendering/SceneDefinition/UserScene.h>

std::shared_ptr<UserScene> orthoScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    std::shared_ptr<MeshPrototype> quadProto = std::make_shared<MeshPrototype>();

    quadProto->instanced = true;
    quadProto->meshType = QUAD;
    quadProto->shaderType = COLOR_INSTANCED;
    quadProto->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    quadProto->disableNormals = true;

    std::shared_ptr<GameObject> obj1 = std::make_shared<GameObject>(quadProto);

    obj1->transform.scale = glm::vec3(0.5f, 0.5f, 0.0f);
    obj1->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

    scene->projection = ORTOGRAPHIC;
    scene->addObject(obj1);

    return scene;
}