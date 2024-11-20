#pragma once

#include <string>

class Shader {
protected:

    unsigned int shaderID;
    std::string path;

public:
    
    Shader(const std::string& filePath);
    virtual ~Shader();

    virtual void compileShader() = 0;
    virtual const char* getShaderType() const = 0;
};
