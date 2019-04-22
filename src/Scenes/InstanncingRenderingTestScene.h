#pragma oncewhereis

#include <Engine.h>
#include <Utils/Objects.h>

void addScatteredCubes(const std::shared_ptr<Scene> & scene) {

    for (int x = 0; x < 30; x++) {
        for (int y = 0; y < 100; y++) {
            for (int z = 0; z < 100; z++) {
                scene->addChild(cube(glm::vec3(0.2f), glm::vec3(x * 4, y * 4, z * 4), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
            }
        }
    }
}

void addChart(const std::shared_ptr<Scene> & scene) {

    scene->projection = ORTOGRAPHIC;

    std::function<float(float, float, float)> t = [](float in, float max, float min) {
        float q = max - min;
        return (2.0f / q) * in - 1 - (2.0f * min) / (max - min);
    };

    float min = -10.0f;
    float max = 10.0f;

    float samples = 350.0f;
    float step = (max-min) / samples;

    float sampleWidth = 2.0f / samples;

    for (int sample = 0; sample < samples; sample++) {
        float x = min + sample * step;
        float y = x;
        scene->addChild(quad(glm::vec3(sampleWidth, 0.5f, 1.0f), glm::vec3(t(x, min, max) + sampleWidth / 2.0f, t(-y, min, max), 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    }
}

void addChartQuad(const std::shared_ptr<Scene> & scene) {

    scene->projection = ORTOGRAPHIC;

    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->transform.scale = glm::vec3(1.0f);
    obj->transform.position = glm::vec3(0.0f);

    auto proto = MeshPrototype::of(QUAD, MANDELBROT, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

    proto->texture = "../resources/textures/texture_white.bmp";
    obj->addComponent(proto);
    scene->addChild(obj);
}

std::shared_ptr<Scene> instancedScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    addScatteredCubes(scene);

    return scene;
}