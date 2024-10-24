//Shader.cpp
#include <GL/glew.h>
#include "Shader.h"
#include <iostream>

Shader::Shader(const std::string& filePath) : shaderID(0), path(filePath) {}

Shader::~Shader() {
    if (shaderID) {
        glDeleteShader(shaderID);
    }
}

unsigned int Shader::getShaderID() const {
    return shaderID;
}
