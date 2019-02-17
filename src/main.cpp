#include "Engine/Engine.h"

std::shared_ptr<Scene> createMainScene();
std::shared_ptr<Scene> createTestScene();

int main() {
    std::shared_ptr<Engine> engine;

    try {
        engine = std::make_shared<Engine>();
    }
    catch (EngineException e) {
        return -1;
    }

    engine->scene = createMainScene();
    engine->renderingLoop();

    glfwTerminate();

    return 0;
}

std::shared_ptr<Scene> createMainScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(-1.2f, 1.0f, 2.0f);

    auto mandelbrotShader = std::make_shared<Shader>("resources/shaders/Mandelbrot.vert", "resources/shaders/Mandelbrot.frag");
    auto gridShader = std::make_shared<Shader>("resources/shaders/Grid.vert", "resources/shaders/Grid.frag");
    auto diffuseShader = std::make_shared<Shader>("resources/shaders/Diffuse.vert", "resources/shaders/Diffuse.frag");
    auto colorShader = std::make_shared<Shader>("resources/shaders/Color.vert", "resources/shaders/Color.frag");
    auto texturedShader = std::make_shared<Shader>("resources/shaders/Textured.vert", "resources/shaders/Textured.frag");

    std::shared_ptr<Quad> gridQuad = std::make_shared<Quad>();
    gridQuad->shader = gridShader;
    gridQuad->loadTexture("resources/textures/texture_white.bmp");
    gridQuad->transform.scale = glm::vec3(100.0f, 100.0f, 100.0f);
    gridQuad->transform.rotation = glm::vec3(glm::radians(90.0), 0.0f, 0.0f);

    std::shared_ptr<Mesh> lampMesh = std::make_shared<Mesh>();
    lampMesh->loadMesh("resources/models/sphere.obj");
    lampMesh->shader = colorShader;
    lampMesh->transform.scale = glm::vec3(0.1f);
    lampMesh->transform.position = *lightPos.get();
    lampMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    };

    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    cube->loadMesh("resources/models/cube.obj");
    cube->shader = diffuseShader;
    cube->transform.position = glm::vec3(2.0f, 0.5f, 0.0f);
    cube->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(0.4f, 0.4f, 0.9f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Mesh> bunnyMesh = std::make_shared<Mesh>();
    bunnyMesh->loadMesh("resources/models/bunny.obj");
    bunnyMesh->shader = diffuseShader;
    bunnyMesh->transform.scale = glm::vec3(10.0f);
    bunnyMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Mesh> suzanneMesh = std::make_shared<Mesh>();
    suzanneMesh->loadMesh("resources/models/suzanne.obj");
    suzanneMesh->shader = diffuseShader;
    suzanneMesh->transform.position = glm::vec3(0.0f, 3.0f, 0.0f);
    suzanneMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Mesh> teapotMesh = std::make_shared<Mesh>();
    teapotMesh->loadMesh("resources/models/teapot.obj");
    teapotMesh->shader = diffuseShader;
    teapotMesh->transform.position = glm::vec3(-3.0f, 1.0f, 0.0f);
    teapotMesh->transform.scale = glm::vec3(0.5f);
    teapotMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Line> axisX = std::make_shared<Line>();
    axisX->shader = colorShader;
    axisX->setCoords(glm::vec3(-20.0f, 0.0f, 0.0f), glm::vec3(20.0f, 0.0f, 0.0f));
    axisX->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(0.0f, 1.0, 0.0, 1.0));
    };

    std::shared_ptr<Line> axisY = std::make_shared<Line>();
    axisY->shader = colorShader;
    axisY->setCoords(glm::vec3(0.0f, -20.0f, 0.0f), glm::vec3(0.0f, 20.0f, 0.0f));
    axisY->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 0.0, 0.0, 1.0));
    };

    std::shared_ptr<Line> axisZ = std::make_shared<Line>();
    axisZ->shader = colorShader;
    axisZ->setCoords(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f, 0.0f, 20.0f));
    axisZ->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(0.0f, 0.0, 1.0, 1.0));
    };

    auto gridObject = std::make_shared<GameObject>();
    gridObject->addComponent(gridQuad);

    auto lampMeshObject = std::make_shared<GameObject>();
    lampMeshObject->addComponent(lampMesh);

    auto cubeObject = std::make_shared<GameObject>();
    cubeObject->addComponent(cube);

    auto bunnyObject = std::make_shared<GameObject>();
    bunnyObject->addComponent(bunnyMesh);

    auto suzanneMeshObject = std::make_shared<GameObject>();
    suzanneMeshObject->addComponent(suzanneMesh);

    auto teapotMeshObject = std::make_shared<GameObject>();
    teapotMeshObject->addComponent(teapotMesh);

    auto axisXObject = std::make_shared<GameObject>();
    axisXObject->addComponent(axisX);

    auto axisYObject = std::make_shared<GameObject>();
    axisYObject->addComponent(axisY);

    auto axisZObject = std::make_shared<GameObject>();
    axisZObject->addComponent(axisZ);

    scene->addObject(axisXObject);
    scene->addObject(axisYObject);
    scene->addObject(axisZObject);
    scene->addObject(lampMeshObject);
    scene->addObject(teapotMeshObject);
    scene->addObject(suzanneMeshObject);
    scene->addObject(bunnyObject);
    scene->addObject(cubeObject);
    scene->addObject(lampMeshObject);
    scene->addObject(gridObject);

    return scene;
}

std::shared_ptr<Scene> createTestScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(-1.2f, 1.0f, 2.0f);

    auto mandelbrotShader = std::make_shared<Shader>("resources/shaders/Mandelbrot.vert", "resources/shaders/Mandelbrot.frag");
    auto gridShader = std::make_shared<Shader>("resources/shaders/Grid.vert", "resources/shaders/Grid.frag");
    auto diffuseShader = std::make_shared<Shader>("resources/shaders/Diffuse.vert", "resources/shaders/Diffuse.frag");
    auto colorShader = std::make_shared<Shader>("resources/shaders/Color.vert", "resources/shaders/Color.frag");
    auto texturedShader = std::make_shared<Shader>("resources/shaders/Textured.vert", "resources/shaders/Textured.frag");

    std::shared_ptr<Quad> gridQuad = std::make_shared<Quad>();
    gridQuad->shader = gridShader;
    gridQuad->loadTexture("resources/textures/texture_white.bmp");
    gridQuad->transform.scale = glm::vec3(100.0f, 100.0f, 100.0f);
    gridQuad->transform.rotation = glm::vec3(glm::radians(90.0), 0.0f, 0.0f);

    std::shared_ptr<Mesh> lampMesh = std::make_shared<Mesh>();
    lampMesh->loadMesh("resources/models/sphere.obj");
    lampMesh->shader = colorShader;
    lampMesh->transform.scale = glm::vec3(0.1f);
    lampMesh->transform.position = *lightPos.get();
    lampMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    };

    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    cube->loadMesh("resources/models/cube.obj");
    cube->shader = diffuseShader;
    cube->transform.position = glm::vec3(0.0f, 0.5f, 0.0f);
    cube->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Line> axisX = std::make_shared<Line>();
    axisX->shader = colorShader;
    axisX->setCoords(glm::vec3(-20.0f, 0.0f, 0.0f), glm::vec3(20.0f, 0.0f, 0.0f));
    axisX->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(0.0f, 1.0, 0.0, 1.0));
    };

    std::shared_ptr<Line> axisY = std::make_shared<Line>();
    axisY->shader = colorShader;
    axisY->setCoords(glm::vec3(0.0f, -20.0f, 0.0f), glm::vec3(0.0f, 20.0f, 0.0f));
    axisY->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 0.0, 0.0, 1.0));
    };

    std::shared_ptr<Line> axisZ = std::make_shared<Line>();
    axisZ->shader = colorShader;
    axisZ->setCoords(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f, 0.0f, 20.0f));
    axisZ->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(0.0f, 0.0, 1.0, 1.0));
    };

    auto gridObject = std::make_shared<GameObject>();
    gridObject->addComponent(gridQuad);

    auto lampMeshObject = std::make_shared<GameObject>();
    lampMeshObject->addComponent(lampMesh);

    auto cubeObject = std::make_shared<GameObject>();
    cubeObject->addComponent(cube);

    auto axisXObject = std::make_shared<GameObject>();
    axisXObject->addComponent(axisX);

    auto axisYObject = std::make_shared<GameObject>();
    axisYObject->addComponent(axisY);

    auto axisZObject = std::make_shared<GameObject>();
    axisZObject->addComponent(axisZ);

    scene->addObject(axisXObject);
    scene->addObject(axisYObject);
    scene->addObject(axisZObject);
    scene->addObject(lampMeshObject);

    scene->addObject(cubeObject);
    scene->addObject(lampMeshObject);
    scene->addObject(gridObject);

    return scene;
}