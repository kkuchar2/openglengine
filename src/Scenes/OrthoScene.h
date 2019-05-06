#pragma once

#include <Scene/Scene.h>

std::shared_ptr<Scene> orthoScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<MeshComponent> quadProto = std::make_shared<MeshComponent>();
    quadProto->meshType = QUAD;
    quadProto->shaderType = AMBIENT;
    quadProto->color = glm::vec4(0.0f, 0.0f, 1.0f, 0.2f);
    quadProto->disableNormals = true;

    std::shared_ptr<MeshComponent> quadProto2 = std::make_shared<MeshComponent>();
    quadProto2->meshType = QUAD;
    quadProto2->shaderType = AMBIENT;
    quadProto2->color = glm::vec4(1.0f, 0.0f, 0.0f, 0.2f);
    quadProto2->disableNormals = true;

    std::shared_ptr<MeshComponent> line = std::make_shared<MeshComponent>();
    line->meshType = QUAD;
    line->shaderType = AMBIENT;
    line->color = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
    line->disableNormals = true;

    std::shared_ptr<MeshComponent> line2 = std::make_shared<MeshComponent>();
    line2->meshType = QUAD;
    line2->shaderType = AMBIENT;
    line2->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    line2->disableNormals = true;

    std::shared_ptr<MeshComponent> line3 = std::make_shared<MeshComponent>();
    line3->meshType = QUAD;
    line3->shaderType = AMBIENT;
    line3->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    line3->disableNormals = true;

    std::shared_ptr<GameObject> obj1 = std::make_shared<GameObject>();
    obj1->addComponent(quadProto);

    obj1->transform.scale = glm::vec3(0.1f, 0.1f, 0.0f);
    obj1->transform.position = glm::vec3(0.1f, 0.1f, 0.0f);
    //obj1->transform.rotation = glm::vec3(0.0f, 0.0f, 0.2f);

    std::shared_ptr<GameObject> obj2 = std::make_shared<GameObject>();
    obj2->addComponent(quadProto2);

    obj2->transform.scale = glm::vec3(0.1f, 0.25f, 0.0f);
    obj2->transform.position = glm::vec3(0.1f, -0.02f, -0.1f);
    obj2->transform.rotation = glm::vec3(0.0f, 0.0f, 0.2f);

    std::shared_ptr<GameObject> lineVertical = std::make_shared<GameObject>();
    lineVertical->addComponent(line);

    lineVertical->transform.scale = glm::vec3(0.001f, 1.0f, 0.0f);
    lineVertical->transform.position = obj1->transform.position;

    std::shared_ptr<GameObject> lineHorizontal = std::make_shared<GameObject>();
    lineHorizontal->addComponent(line);

    lineHorizontal->transform.scale = glm::vec3(1.0f, 0.001f, 0.0f);
    lineHorizontal->transform.position = obj1->transform.position;

    std::shared_ptr<GameObject> lineVertical2 = std::make_shared<GameObject>();
    lineVertical2->addComponent(line2);

    lineVertical2->transform.scale = glm::vec3(0.001f, 1.0f, 0.0f);
    lineVertical2->transform.position = obj2->transform.position;

    std::shared_ptr<GameObject> lineHorizontal2 = std::make_shared<GameObject>();

    lineHorizontal2->addComponent(line2);
    lineHorizontal2->transform.scale = glm::vec3(1.0f, 0.001f, 0.0f);
    lineHorizontal2->transform.position = obj2->transform.position;

    std::shared_ptr<GameObject> lineVertical3 = std::make_shared<GameObject>();
    lineVertical3->addComponent(line3);

    lineVertical3->transform.scale = glm::vec3(0.001f, 1.0f, 0.0f);

    std::shared_ptr<GameObject> lineHorizontal3 = std::make_shared<GameObject>();
    lineHorizontal3->addComponent(line3);
    lineHorizontal3->transform.scale = glm::vec3(1.0f, 0.001f, 0.0f);

    scene->projection = ORTOGRAPHIC;
    scene->addChild(lineHorizontal);
    scene->addChild(lineVertical);
    scene->addChild(lineHorizontal2);
    scene->addChild(lineVertical2);
    scene->addChild(lineHorizontal3);
    scene->addChild(lineVertical3);
    scene->addChild(obj2);
    scene->addChild(obj1);

    return scene;
}