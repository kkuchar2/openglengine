#include "OrtographicCamera.h"

OrtographicCamera::OrtographicCamera(int w, int h) : BaseCamera() {
    updateSize(w, h);
    projection = ORTOGRAPHIC;
}

void OrtographicCamera::updateSize(int w, int h) {
    width = static_cast<float>(w);
    height = static_cast<float>(h);
}

glm::mat4x4 OrtographicCamera::getViewMatrix()  {
    return glm::translate(glm::mat4(1.0), glm::vec3(-width / 2.0f, -height / 2.0f, 0.0f));
}

glm::mat4x4 OrtographicCamera::getProjectionMatrix()  {
    return glm::ortho(-width / 2.0f, width / 2.0f, height / 2.0f, -height / 2.0f, 0.0f, 0.3f);
}