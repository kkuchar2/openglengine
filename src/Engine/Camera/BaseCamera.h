#ifndef OPENGL_BASECAMERA_H
#define OPENGL_BASECAMERA_H

#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>

#include "../Window.h"
#include "../Primitives/RenderObject.h"
#include "../Shader.h"

class BaseCamera {

    protected:
        std::shared_ptr<Window> window;

    public:
        explicit BaseCamera(std::shared_ptr<Window> & window)   {
            this->window = window;
        }

        void Render(std::shared_ptr<RenderObject> & renderObject) {
            std::shared_ptr<Shader> shader = renderObject->shader;

            shader->use();

            shader->setFloat("time", window->totalTime);
            shader->setVec2("resolution", window->getResolution());

            shader->setVec3("translation", renderObject->transform.position);
            shader->setVec3("scale", renderObject->transform.scale);
            shader->setVec3("rotation", renderObject->transform.rotation);

            shader->setMat4("projection", getProjectionMatrix());
            shader->setMat4("view", getViewMatrix());
            shader->setMat4("model", getModelMatrix());

            renderObject->Render();
        }

        virtual glm::mat4x4 getModelMatrix() = 0;
        virtual glm::mat4x4 getViewMatrix() = 0;
        virtual glm::mat4x4 getProjectionMatrix() = 0;
};

#endif //OPENGL_BASECAMERA_H
