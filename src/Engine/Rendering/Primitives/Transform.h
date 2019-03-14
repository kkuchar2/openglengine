#ifndef OPENGL_TRANSFORM_H
#define OPENGL_TRANSFORM_H

#include <glm/vec3.hpp>

struct Transform {
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 rotation =  glm::vec3(0.0f);
  glm::vec3 scale = glm::vec3(1.0f);
};

#endif //OPENGL_TRANSFORM_H