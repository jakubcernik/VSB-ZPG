//Shader.cpp

#include "Shader.h"
#include <GL/glew.h>
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
