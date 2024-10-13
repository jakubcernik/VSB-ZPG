#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
private:
    unsigned int id; // Unique private ID for the shader
    unsigned int shaderType; // GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc.

    std::string loadShaderSource(const std::string& filePath);
    void compileShader(const std::string& source);

public:
    Shader(const std::string& filePath, unsigned int type); // Konstruktor naète shader ze souboru
    ~Shader();

    unsigned int getId() const;
    void attachToProgram(unsigned int programId) const;
};

#endif // SHADER_H
