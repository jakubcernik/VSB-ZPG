#pragma once
#include <string>
#include "Shader.h"

class FragmentShader : public Shader
{

public:
    FragmentShader(const std::string& filePath);
    unsigned int getID() const;

private:
    unsigned int shaderID;
    void compile(const std::string& source);

};
