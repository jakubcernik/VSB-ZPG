#pragma once
#include "Observer.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "ShaderLoader.h"

class ShaderProgram : public Observer, public ShaderLoader {

private:
    unsigned int programID;

public:
    ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~ShaderProgram();

    void setUniform(const std::string& name, const glm::mat4& matrix);
    void setUniform(const std::string& name, const glm::vec3& vector);
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setLightingUniforms(const glm::vec3& lightPos, const glm::vec3& viewPos, const glm::vec3& lightColor, const glm::vec3& objectColor);
    void setMultipleLightingUniforms(const std::vector<glm::vec3>& lightPositions, const std::vector<glm::vec3>& lightColors, const glm::vec3& viewPos, const glm::vec3& objectColor);
    void use();
    void free();

    void onNotify(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
};
