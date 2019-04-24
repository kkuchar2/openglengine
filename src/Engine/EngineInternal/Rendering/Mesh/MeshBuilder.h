#pragma once
#include <Rendering/Primitives/Quad.h>
#include <Rendering/Primitives/Cube.h>
#include <Rendering/Primitives/Surface.h>

#include <Rendering/Camera/Projection.h>
#include <Rendering/Shading/ShaderPool.h>
#include <Rendering/Primitives/Line.h>
#include <Rendering/Primitives/LinePrototype.h>
#include <Rendering/Primitives/SkyboxPrototype.h>
#include <Rendering/Primitives/Point.h>
#include <Rendering/GameObject/Transform.h>
#include <Rendering/GameObject/GameObject.h>

#include "SurfacePrototype.h"

class MeshBuilder {
    public:
        static std::shared_ptr<Mesh> of(const std::shared_ptr<MeshPrototype> & proto, const std::shared_ptr<GameObject> & obj) {

            std::shared_ptr<Mesh> mesh;

            if (proto->path.empty()) {
                 switch (proto->meshType) {
                    case LINE:
                        mesh = std::make_shared<Line>();
                        break;
                    case QUAD:
                        mesh = std::make_shared<Quad>();
                        break;
                    case CUBE:
                        mesh = std::make_shared<Cube>();
                        break;
                    case SURFACE:
                        mesh = std::make_shared<Surface>(300, 300);
                        break;
                    case POINT:
                        mesh = std::make_shared<Point>();
                        break;
                    case SKYBOX:
                        mesh = std::make_shared<Cube>();
                        break;
                    case RESOURCE:
                        mesh = std::make_shared<Mesh>(proto->path);
                        break;
                    case NONE:
                        mesh = std::make_shared<Mesh>(proto->path);
                        break;

                 }

                if (proto->meshType == LINE) {
                    auto lineProto = std::dynamic_pointer_cast<LinePrototype>(proto);
                    auto lineMesh = std::dynamic_pointer_cast<Line>(mesh);
                    lineMesh->setCoords(lineProto->start, lineProto->end);
                }
            }
            else {
                mesh = std::make_shared<Mesh>(proto->path);
            }

            if (!mesh.get()) {
                std::cerr << "Mesh of type: " << proto->meshType << ", " << proto->path << " is null" << std::endl;
            }

            mesh->meshType = proto->getMeshTypeStr();
            mesh->shaderType = proto->getShaderTypeStr();
            mesh->projection = obj->projection;
            mesh->modelMatrices.push_back(obj->transform.modelMatrix);
            mesh->colorVectors.push_back(proto->color);
            mesh->shader = ShaderPool::Instance().getShader(proto->shaderType);
            mesh->cubeMap = proto->cubeMap;
            mesh->disableNormals = proto->disableNormals;
            mesh->shaderInit = [proto](ShaderPtrRef s) {
                s->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                s->setVec3("lightPos", glm::vec3(2.2f, 3.0f, 2.0f));
            };

            if (proto->meshType != SKYBOX) {
                if (proto->texture != nullptr) {
                    mesh->loadTexture(proto->texture);
                }
            }
            else {
                auto skyboxProto = std::dynamic_pointer_cast<SkyboxPrototype>(proto);
                mesh->cubeMap = true;
                mesh->loadCubeMap(skyboxProto->paths);
            }

            return mesh;
        }
};