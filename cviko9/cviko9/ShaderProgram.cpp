#include "ShaderProgram.h"
#include "ShaderLoader.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

ShaderProgram::ShaderProgram(const string& vertexShaderPath, const string& fragmentShaderPath) {
    programID = loadShader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programID);
}

void ShaderProgram::use() {
    glUseProgram(programID);
}

void ShaderProgram::free() {
	glUseProgram(0);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix) {
    GLint location = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& vector) {
    GLint location = glGetUniformLocation(programID, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(vector));
}


void ShaderProgram::setUniform(const std::string& name, float value) {
    GLint location = glGetUniformLocation(programID, name.c_str());
    glUniform1f(location, value);
}

void ShaderProgram::setUniform(const std::string& name, int value) {
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location != -1) {
        glUniform1i(location, value);
    }
    else {
        fprintf(stderr, "Failed to get uniform location for %s\n", name.c_str());
    }
}

void ShaderProgram::setLightingUniforms(const glm::vec3& lightPos, const glm::vec3& viewPos, const glm::vec3& lightColor, const glm::vec3& objectColor) {
    setUniform("lightPos", lightPos);
    setUniform("viewPos", viewPos);
    setUniform("lightColor", lightColor);
    setUniform("objectColor", objectColor);
}

void ShaderProgram::setMultipleLightingUniforms(const std::vector<glm::vec3>& lightPositions, const std::vector<glm::vec3>& lightColors, const glm::vec3& viewPos, const glm::vec3& objectColor) {
    setUniform("viewPos", viewPos);
    setUniform("objectColor", objectColor);
    setUniform("numLights", static_cast<int>(lightPositions.size()));

    for (size_t i = 0; i < lightPositions.size(); ++i) {
        setUniform("lights[" + std::to_string(i) + "].position", lightPositions[i]);
        setUniform("lights[" + std::to_string(i) + "].color", lightColors[i]);
    }
}

void ShaderProgram::setMaterialUniforms(const Material& material) {
    setUniform("Ra", material.Ra);
    setUniform("Rd", material.Rd);
    setUniform("Rs", material.Rs);
}

void ShaderProgram::onNotify(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    use();
    setUniform("viewMatrix", viewMatrix);
    //printf("view uniform set\n");
    setUniform("projectionMatrix", projectionMatrix);
    //printf("projection uniform set\n");
    free();
}