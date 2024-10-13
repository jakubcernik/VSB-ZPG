#include "VertexShader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>

VertexShader::VertexShader(const std::string& filePath) {
    // Naètení zdroje shaderu a kompilace
    std::ifstream shaderFile(filePath);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    std::string code = shaderStream.str();
    compile(code);
}

void VertexShader::compile(const std::string& source) {
    shaderID = glCreateShader(GL_VERTEX_SHADER);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);
    // Kontrola úspìchu kompilace
}

unsigned int VertexShader::getID() const {
    return shaderID;
}
