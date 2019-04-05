#pragma once

#include <memory>
#include <vector>

#include "Mesh.h"
#include "Primitives/Cube.h"
#include "Camera/BaseCamera.h"
#include "Shading/ShaderPool.h"
#include "Primitives/Line.h"
#include "../Window/Input/MessageListener.h"

class GameObject {

    public:
        std::string name = "Default";
        std::vector<std::shared_ptr<MessageListener>> components;

        GameObject() = default;

        template<typename T, typename std::enable_if<std::is_base_of<MessageListener, T>::value>::type * = nullptr>
        GameObject(std::shared_ptr<T> component) {
            addComponent(component);
        }


        template<typename T, typename std::enable_if<std::is_base_of<MessageListener, T>::value>::type * = nullptr>
        void addComponent(std::shared_ptr<T> component) {
            components.push_back(component);
        }

        template<typename T, typename std::enable_if<std::is_base_of<BaseCamera, T>::value>::type * = nullptr>
        void Render(std::shared_ptr<T> & camera) {
            for (auto & componentPtr : components) {

                std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(componentPtr);

                if (mesh) {
                    camera->Render(mesh);
                }
            }
        }

        std::vector<std::shared_ptr<GameObject>> CreateBoundingBox() {
            for (auto & componentPtr : components) {

                std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(componentPtr);

                if (mesh) {
                    mesh->prepare();
                    return CreateBoundingBoxLines(mesh->calculateBoundingBox());
                }
            }
            return std::vector<std::shared_ptr<GameObject>>();
        }

        std::vector<std::shared_ptr<GameObject>> CreateBoundingBoxLines(BoundingBox boundingBox) {
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

        std::shared_ptr<GameObject> createLineObject(glm::vec3 start, glm::vec3 end, BoundingBox & boundingBox) {
            return std::make_shared<GameObject>(createLine(start, end, boundingBox.rotation, boundingBox.center));
        }

        std::shared_ptr<Line> createLine(glm::vec3 start, glm::vec3 end, glm::vec3 rotation, glm::vec3 position) {
            std::shared_ptr<Line> line = std::make_shared<Line>();
            line->shader = ShaderPool::Instance().colorShader;
            line->drawWireframe = false;
            line->setCoords(start, end);
            line->transform.position = position;
            line->transform.rotation = rotation;
            line->shaderInit = [](ShaderPtrRef shader) {
                shader->setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
            };
            line->prepare();
            return line;
        }
};