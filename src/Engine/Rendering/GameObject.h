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

        // TODO: Improve access to shaders
        ShaderPool shaderPool;

        GameObject() = default;

        template<typename T, typename std::enable_if<std::is_base_of<MessageListener, T>::value>::type* = nullptr>
        GameObject(std::shared_ptr<T> component) {
            addComponent(component);
        }


        template<typename T, typename std::enable_if<std::is_base_of<MessageListener, T>::value>::type* = nullptr>
        void addComponent(std::shared_ptr<T> component) {
            components.push_back(component);
        }

        template<typename T, typename std::enable_if<std::is_base_of<BaseCamera, T>::value>::type* = nullptr>
        void Render(std::shared_ptr<T> & camera) {
            for (auto & componentPtr : components) {

                std::shared_ptr<Mesh> mesh =  std::dynamic_pointer_cast<Mesh>(componentPtr);

                if (mesh) {
                    camera->Render(mesh);
                }
            }
        }

        std::shared_ptr<GameObject> CreateBoundingBox() {
            for (auto & componentPtr : components) {

                std::shared_ptr<Mesh> mesh =  std::dynamic_pointer_cast<Mesh>(componentPtr);

                if (mesh) {
                    mesh->prepare();
                    return CreateBoundingBoxObject(mesh->calculateBoundingBox());
                }
            }
            return std::shared_ptr<GameObject>(nullptr);
        }

        std::shared_ptr<GameObject> CreateBoundingBoxObject(BoundingBox boundingBox) {
            std::shared_ptr<Cube> bbBoxCube = std::make_shared<Cube>();
            bbBoxCube->shader = shaderPool.colorShader;
            bbBoxCube->drawWireframe = true;
            bbBoxCube->transform.position = boundingBox.center;
            bbBoxCube->transform.scale = boundingBox.size;
            bbBoxCube->transform.rotation = boundingBox.rotation;
            bbBoxCube->shaderInit = [](ShaderPtrRef shader) {
                shader->setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
            };

            return std::make_shared<GameObject>(bbBoxCube);
        }
};