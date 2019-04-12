#pragma once


#include <Rendering/Primitives/Quad.h>
#include <Rendering/Primitives/Cube.h>
#include <Rendering/Primitives/Surface.h>

#include <Rendering/Camera/Projection.h>
#include <Rendering/Shading/ShaderPool.h>
#include <Rendering/Primitives/Line.h>

#include "SurfacePrototype.h"

class MeshBuilder {

    static std::shared_ptr<Surface> createSurfaceMesh(const std::shared_ptr<MeshPrototype> & proto) {
        std::shared_ptr<SurfacePrototype> surfProto = std::dynamic_pointer_cast<SurfacePrototype>(proto);
        std::shared_ptr<Surface> surface = std::make_shared<Surface>(300, 300);
        return surface;
    }

    public:
        static std::shared_ptr<Mesh> of(const std::shared_ptr<MeshPrototype> & proto, const Projection & projection) {

            std::shared_ptr<Mesh> mesh;

            switch(proto->meshType) {
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
                    mesh =  std::make_shared<Surface>(300, 300);
                    break;
                case RESOURCE:
                    mesh = std::make_shared<Mesh>(proto->path);
                    break;
                case NONE:
                    break;
            }

            mesh->shader = ShaderPool::Instance().getShader(proto->shaderType);
            mesh->isInstanced = true;
            mesh->disableNormals = false;
            mesh->shaderInit = [proto](ShaderPtrRef s) {
                s->setVec4("color", proto->color);
                s->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                s->setVec3("lightPos", glm::vec3(0.0f, 2.0f, 0.0f));
            };
            mesh->projection = projection;
            return mesh;
        }
};