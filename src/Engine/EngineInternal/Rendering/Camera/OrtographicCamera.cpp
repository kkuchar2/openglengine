#include "OrtographicCamera.h"

OrtographicCamera::OrtographicCamera(const glm::vec2 & size) : BaseCamera() {
    updateSize(size);
    projection = ORTOGRAPHIC;
}

void OrtographicCamera::updateSize(const glm::vec2 & size) {
    width = size.x;
    height = size.y;
}

glm::mat4x4 OrtographicCamera::getViewMatrix()  {
    return glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 0.0f));
}

glm::mat4x4 OrtographicCamera::getProjectionMatrix()  {
    return glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.3f);
}