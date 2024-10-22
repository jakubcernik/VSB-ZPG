#include "ShaderProgram.h"
#include "ShaderLoader.h"  // Pøidání nového souboru ShaderLoader
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const string& vertexShaderPath, const string& fragmentShaderPath) {
    ShaderLoader shaderLoader;
    programID = shaderLoader.loadShader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programID);
}

void ShaderProgram::use() {
    glUseProgram(programID); // Nastavení programu jako aktivního
}

void ShaderProgram::setUniform(const string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

// Nastavení uniformních promìnných pro osvìtlení
void ShaderProgram::setLightingUniforms(const glm::vec3& lightPos, const glm::vec3& viewPos, const glm::vec3& lightColor, const glm::vec3& objectColor) {
    glUniform3fv(glGetUniformLocation(programID, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(programID, "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform3fv(glGetUniformLocation(programID, "lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(glGetUniformLocation(programID, "objectColor"), 1, glm::value_ptr(objectColor));
}


void ShaderProgram::onNotify(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    use();
    setUniform("view", viewMatrix);
    printf("view uniform set\n");
    setUniform("projection", projectionMatrix);
    printf("projection uniform set\n");
}
