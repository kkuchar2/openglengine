#pragma once

#include <Rose/Observable.h>
#include <glm/glm/vec3.hpp>

class Vec3Property : public Observable<glm::vec3> {
    public:
        explicit Vec3Property(glm::vec3 initValue) : Observable(initValue) {

        }
};