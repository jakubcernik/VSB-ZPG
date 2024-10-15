#include "Shader.h"
#include <iostream>

Shader::Shader() : shaderID(0) {}

Shader::~Shader() {}

unsigned int Shader::getShaderID() const {
    return shaderID;
}
