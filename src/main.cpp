#include <Scenes/InstanncingRenderingTestScene.h>
#include <Scenes/MainScene.h>
#include <Engine/EngineInternal/Scene/BaseScene.h>
#include <Engine.h>
#include <Scenes/OrthoScene.h>
#include <iomanip>

std::ostream &operator<<(std::ostream &out, const glm::mat4x4 & m) {

    out << "\n";

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out << std::setw(10) << m[j][i] << " ";
        }
        out << "\n";
    }

    return out;
}

int main() {
    std::shared_ptr<Engine> engine;

    try {
        engine = std::make_shared<Engine>();
    }
    catch (EngineException & e) {
        std::cout << e.what() << std::endl;
    }

    glm::vec3 rot = glm::vec3(34.0f, 15.0f, 16.0f);
    glm::vec3 pos = glm::vec3(2.0f, 2.0f, 2.0f);
    glm::vec3 scale = glm::vec3(2.3f, 3.9f, 0.3f);

    glm::mat4x4 rotationMatrix = MatrixUtils::rotationMatrix(rot);
    glm::mat4x4 translationMatrix = MatrixUtils::translationMatrix(pos);
    glm::mat4x4 scaleMatrix = MatrixUtils::scaleMatrix(scale);

    glm::mat4x4 tr = translationMatrix * rotationMatrix;

    glm::mat4x4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

    std::cout << std::endl;
    std::cout << "Rotation matrix:" << std::endl;
    std::cout << rotationMatrix << std::endl;

    std::cout << std::endl;
    std::cout << "Translation matrix:" << std::endl;
    std::cout << translationMatrix << std::endl;


    std::cout << std::endl;
    std::cout << "Scale matrix:" << std::endl;
    std::cout << scaleMatrix << std::endl;

    std::cout << std::endl;
    std::cout << "Position * rotation matrix:" << std::endl;
    std::cout << tr << std::endl;

    std::cout << std::endl;
    std::cout << "Model matrix:" << std::endl;
    std::cout << modelMatrix << std::endl;

    std::cout << std::endl;
    std::cout << "Model matrix:" << std::endl;
    std::cout << MatrixUtils::modelMatrix(scale, pos, rotationMatrix) << std::endl;

    engine->addScene(baseScene());
    engine->addScene(instancedScene());
    //engine->addScene(orthoScene());

    engine->start();

    glfwTerminate();

    return 0;
}