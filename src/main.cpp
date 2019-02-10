#include "Engine/Engine.h"
#include "Engine/OBJ_Loader.h"

glm::vec3 lightPos = glm::vec3(-1.2f, 1.0f, 2.0f);

void addAxes(std::shared_ptr<Engine> &engine, std::shared_ptr<Shader> &shader);

// OBJ_Loader is copied from https://github.com/Bly7/OBJ-Loader
// It creates more vertices, than necessary, TODO: Investigate
void addOBJ(const char * path, std::shared_ptr<Engine> & engine, std::shared_ptr<Shader> & diffuseShader, std::shared_ptr<Shader> & colorShader);

int main() {

    std::shared_ptr<Engine> engine;

    try {
        engine = std::make_shared<Engine>();
    }
    catch (EngineException & e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    auto mandelbrotShader = std::make_shared<Shader>("resources/shaders/Mandelbrot.vert", "resources/shaders/Mandelbrot.frag");
    auto gridShader = std::make_shared<Shader>("resources/shaders/Grid.vert", "resources/shaders/Grid.frag");
    auto diffuseShader = std::make_shared<Shader>("resources/shaders/Diffuse.vert", "resources/shaders/Diffuse.frag");
    auto colorShader = std::make_shared<Shader>("resources/shaders/Color.vert", "resources/shaders/Color.frag");
    auto texturedShader = std::make_shared<Shader>("resources/shaders/Textured.vert", "resources/shaders/Textured.frag");

    std::shared_ptr<RenderObject> gridQuad = std::make_shared<Quad>();
    gridQuad->useRendering(RenderFlag::PERSPECTIVE);
    gridQuad->useShader(gridShader);
    gridQuad->loadTexture("resources/textures/texture_white.bmp");
    gridQuad->transform.scale = glm::vec3(100.0f, 100.0f, 100.0f);
    gridQuad->transform.rotation = glm::vec3(glm::radians(90.0), 0.0f, 0.0f);

    std::shared_ptr<Cube> lamp = std::make_shared<Cube>();
    lamp->useRendering(RenderFlag::PERSPECTIVE);
    lamp->useShader(colorShader);
    lamp->transform.scale = glm::vec3(0.1f);
    lamp->transform.position = lightPos;
    lamp ->shaderFunc = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    };

    //std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    //cube->useRendering(RenderFlag::PERSPECTIVE);
    //cube->useShader(diffuseShader);
    //cube->transform.position = glm::vec3(0.0f, 0.5f, 0.0f);
    //cube->shaderFunc = [](ShaderPtrRef shader) {
    //    shader->setVec4("color", glm::vec4(1.0f, 0.5f, 0.31f, 1.0f));
    //    shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    //    shader->setVec3("lightPos", lightPos);
    //};

    ////////// Add objects to render //////////
    addOBJ("resources/models/sphere.obj", engine, diffuseShader, colorShader);
    addAxes(engine, colorShader);
    //engine->addObject(cube);
    engine->addObject(lamp);
    engine->addObject(gridQuad);
    ///////////////////////////////////////////

    engine->renderingLoop();

    glfwTerminate();

    return 0;
}

void addAxes(std::shared_ptr<Engine> &engine, std::shared_ptr<Shader> &shader) {
    float sizeSmall = 0.01f;
    float sizeBig = 20.0f;

    std::shared_ptr<RenderObject> axisX = std::make_shared<Cube>();
    std::shared_ptr<RenderObject> axisY = std::make_shared<Cube>();
    std::shared_ptr<RenderObject> axisZ = std::make_shared<Cube>();

    axisX->useRendering(RenderFlag::PERSPECTIVE);
    axisX->useShader(shader);
    axisX->transform.scale = glm::vec3(sizeBig, sizeSmall, sizeSmall);
    axisX ->shaderFunc = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(0.0f, 1.0, 0.0, 1.0));
    };

    axisY->useRendering(RenderFlag::PERSPECTIVE);
    axisY->useShader(shader);
    axisY->transform.scale = glm::vec3(sizeSmall, sizeBig, sizeSmall);
    axisY ->shaderFunc = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 0.0, 0.0, 1.0));
    };

    axisZ->useRendering(RenderFlag::PERSPECTIVE);
    axisZ->useShader(shader);
    axisZ->transform.scale = glm::vec3(sizeSmall, sizeSmall, sizeBig);
    axisZ ->shaderFunc = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(0.0f, 0.0, 1.0, 1.0));
    };

    engine->addObject(axisX);
    engine->addObject(axisY);
    engine->addObject(axisZ);
}

void addOBJ(const char * path, std::shared_ptr<Engine> & engine, std::shared_ptr<Shader> & diffuseShader, std::shared_ptr<Shader> & colorShader) {

    objl::Loader loader;

    bool loadout = loader.LoadFile(path);

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> uvs;
    std::vector<float> normals;

    if (loadout) {
        for (const auto & mesh : loader.LoadedMeshes) {

            std::cout << "Vertices count: " << mesh.Vertices.size() << std::endl;

            for (auto & vertexInfo : mesh.Vertices) {
                vertices.push_back(vertexInfo.Position.X);
                vertices.push_back(vertexInfo.Position.Y);
                vertices.push_back(vertexInfo.Position.Z);

                //std::cout << "(VX: " << vertexInfo.Position.X  << " " << vertexInfo.Position.Y << " " << vertexInfo.Position.Z << std::endl;

                uvs.push_back(vertexInfo.TextureCoordinate.X);
                uvs.push_back(vertexInfo.TextureCoordinate.Y);

                normals.push_back(vertexInfo.Normal.X);
                normals.push_back(vertexInfo.Normal.Y);
                normals.push_back(vertexInfo.Normal.Z);
            }

            for (auto & vertexIndex : mesh.Indices) {
                indices.push_back(vertexIndex);
            }

            std::shared_ptr<RenderMesh> renderMesh = std::make_shared<RenderMesh>(vertices, indices, uvs, normals);

            renderMesh->useRendering(RenderFlag::PERSPECTIVE);
            renderMesh->useShader(diffuseShader);
            renderMesh->transform.scale = glm::vec3(0.1f);
            renderMesh->shaderFunc = [](ShaderPtrRef shader) {
                shader->setVec4("color", glm::vec4(1.0f, 0.5f, 0.31f, 1.0f));
                shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                shader->setVec3("lightPos", lightPos);
            };

            std::cout << "Vertices size: " << vertices.size() << std::endl;
            std::cout << "Normals size: " << normals.size() << std::endl;

            engine->addObject(renderMesh);


            for (int i = 0; i < normals.size(); i+=3) {

                glm::vec3 normal = glm::vec3(normals[i], normals[i + 1], normals[i + 2]);
                glm::vec3 vertex = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);

                glm::vec3 start = renderMesh->transform.scale * (glm::vec3(vertex) + renderMesh->transform.position);
                glm::vec3 end = start + normal;
                std::shared_ptr<Line> line = std::make_shared<Line>();

                line->useRendering(RenderFlag::PERSPECTIVE);
                line->setCoords(start, end);
                line->useShader(colorShader);
                line->shaderFunc = [](ShaderPtrRef shader) {
                    shader->setVec4("color", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
                };
                engine->addObject(line);
            }
        }
    }
}