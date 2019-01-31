#ifndef OPENGL_BASECAMERA_H
#define OPENGL_BASECAMERA_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>

#include "../Window.h"
#include "../Primitives/RenderObject.h"
#include "../Shader.h"

class BaseCamera {

    protected:
        Window * window;

    public:
        explicit BaseCamera(Window * window) {
            std::cout << "Assigning window" << std::endl;
            this->window = window;
        }

        void Render(RenderObject & renderObject, const std::function<void(const Shader *)> & postShaderSetupFunc) {
            Shader * shader = renderObject.shader;

            shader->use();

            shader->setFloat("time", window->totalTime);
            shader->setVec2("resolution", window->getResolution());

            shader->setVec3("translation", renderObject.transform.position);
            shader->setVec3("scale", renderObject.transform.scale);
            shader->setVec3("rotation", renderObject.transform.rotation);

            shader->setMat4("projection", getProjectionMatrix());
            shader->setMat4("view", getViewMatrix());
            shader->setMat4("model", getModelMatrix());

            postShaderSetupFunc(shader);

            renderObject.Render();
        }

        virtual glm::mat4x4 getModelMatrix() = 0;
        virtual glm::mat4x4 getViewMatrix() = 0;
        virtual glm::mat4x4 getProjectionMatrix() = 0;
};

#endif //OPENGL_BASECAMERA_H
