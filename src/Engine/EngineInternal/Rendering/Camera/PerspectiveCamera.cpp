#include "PerspectiveCamera.h"

glm::vec3 PerspectiveCamera::getPosition() {
    return position;
}

glm::mat4x4 PerspectiveCamera::getModelMatrix() {
    return glm::mat4(1.0);
}

glm::mat4x4 PerspectiveCamera::getViewMatrix() {
    return glm::lookAt(position, position + lookDirectionVector, upVector);
}

glm::mat4x4 PerspectiveCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(fovy), aspectRatio, 0.1f, 1000.0f);
}