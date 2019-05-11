#pragma once

#include <Rendering/Mesh/Primitives/Quad.h>
#include <Rendering/Mesh/Primitives/Cube.h>
#include <Rendering/Mesh/Primitives/Surface.h>
#include <Rendering/Mesh/Primitives/Line.h>
#include <Rendering/Mesh/Primitives/LineMeshComponent.h>
#include <Rendering/Mesh/Primitives/Point.h>

class MeshBuilder {
    public:
        static std::shared_ptr<Mesh> buildMesh(const std::shared_ptr<MeshComponent> & meshComponent) {

            std::shared_ptr<Mesh> mesh;

            if (meshComponent->path.empty()) {
                switch (meshComponent->meshType) {
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
                    case RESOURCE:
                        mesh = std::make_shared<Mesh>(meshComponent->path);
                        break;
                    case NONE:
                        mesh = std::make_shared<Mesh>(meshComponent->path);
                        break;
                }

                if (meshComponent->meshType == LINE) {
                    auto lineProto = std::dynamic_pointer_cast<LineMeshComponent>(meshComponent);
                    std::shared_ptr<Line> lineMesh = std::static_pointer_cast<Line>(mesh);
                    lineMesh->setCoords(lineProto->start, lineProto->end);
                }
            }
            else {
                mesh = std::make_shared<Mesh>(meshComponent->path);
            }

            if (!mesh.get()) {
                std::cerr << "Mesh of type: " << meshComponent->meshType << ", " << meshComponent->path << " is null" << std::endl;
            }

            mesh->meshId = meshComponent->getMeshIdText();

            return mesh;
        }
};