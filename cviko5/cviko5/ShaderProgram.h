#pragma once
#include "Observer.h"
#include <glm/glm.hpp>
#include <string>

class ShaderProgram : public Observer {
private:
    unsigned int programID;

public:
    ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~ShaderProgram();

    void setUniform(const std::string& name, const glm::mat4& matrix);
    void use();

    void onNotify(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

};
