#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using namespace std;

ShaderProgram::ShaderProgram(const string& vertexPath, const string& fragmentPath)
    : vertexShader(vertexPath), fragmentShader(fragmentPath) {
    compileAndLinkShaders();
}

void ShaderProgram::compileAndLinkShaders() {
    // Kompilace a propojen� shader�
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader.getID());
    glAttachShader(programID, fragmentShader.getID());
    glLinkProgram(programID);
    // Kontrola �sp�chu propojen�

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "Error linking shader program: " << infoLog << std::endl;
    }
}

void ShaderProgram::use() const {
    glUseProgram(programID);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix) const {
    GLuint loc = glGetUniformLocation(programID, name.c_str());
    if (loc == -1) {
        std::cerr << "Warning: uniform '" << name << "' not found in shader program." << std::endl;
        return; // Pokud uniform nen� nalezen, ukon��me metodu
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}