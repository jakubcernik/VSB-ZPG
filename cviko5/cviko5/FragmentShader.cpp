//FragmentShader.cpp

#include "FragmentShader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

FragmentShader::FragmentShader(const string& filePath) : Shader(filePath) {
    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
}

FragmentShader::~FragmentShader() {}

void FragmentShader::compileShader() {
    ifstream shaderFile(path);
    stringstream shaderStream;

    if (shaderFile.is_open()) {
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
    }
    else {
        printf("Failed to open fragment shader file: %s", path.c_str());
        return;
    }

    string shaderCode = shaderStream.str();
    const char* shaderSource = shaderCode.c_str();
    glShaderSource(shaderID, 1, &shaderSource, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        printf("Fragment shader compilation failed\n");
    }
}

const char* FragmentShader::getShaderType() const {
    return "Fragment Shader";
}