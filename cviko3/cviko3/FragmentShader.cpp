#include "FragmentShader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>

FragmentShader::FragmentShader(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    std::string code = shaderStream.str();
    compile(code);
}

void FragmentShader::compile(const std::string& source) {
    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);
    // Kontrola úspìchu kompilace
}

unsigned int FragmentShader::getID() const {
    return shaderID;
}
