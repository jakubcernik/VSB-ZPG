// Observer.h
#pragma once
#include <glm/glm.hpp>

class Observer {

public:
    virtual ~Observer() {}
    virtual void onNotify(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
};