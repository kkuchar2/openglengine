#pragma once

#include <Rendering/SceneDefinition/Scene.h>

std::shared_ptr<Scene> orthoScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<MeshPrototype> quadProto = std::make_shared<MeshPrototype>();

    quadProto->instanced = true;
    quadProto->meshType = QUAD;
    quadProto->shaderType = COLOR_INSTANCED;
    quadProto->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    quadProto->disableNormals = true;

    std::shared_ptr<GameObject> obj1 = std::make_shared<GameObject>(quadProto);

    obj1->transform.scale = glm::vec3(0.1f, 0.1f, 0.0f);
    obj1->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

    scene->projection = ORTOGRAPHIC;
    scene->addChild(obj1);

    return scene;
}