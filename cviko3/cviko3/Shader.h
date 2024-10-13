#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
public:
    Shader(const std::string& filePath, unsigned int type);
    ~Shader();

    unsigned int getId() const;
    void attachToProgram(unsigned int programId) const;

private:
    unsigned int id;
    unsigned int shaderType;

    void compileShader(const std::string& source);
    std::string loadShaderSource(const std::string& filePath);
};

#endif // SHADER_H