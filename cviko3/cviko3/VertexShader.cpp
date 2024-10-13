#include "VertexShader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

VertexShader::VertexShader(const string& filePath) {
    // Naètení zdroje shaderu a kompilace
    ifstream shaderFile(filePath);
    stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    string code = shaderStream.str();
    compile(code);
}

void VertexShader::compile(const string& source) {
    shaderID = glCreateShader(GL_VERTEX_SHADER);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);

    // Kontrola úspìšnosti kompilace
    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "Error compiling vertex shader: " << infoLog << std::endl;
    }
}

unsigned int VertexShader::getID() const {
    return shaderID;
}
