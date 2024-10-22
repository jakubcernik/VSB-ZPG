#pragma once
#include "Shader.h"

class FragmentShader : public Shader {
public:
    FragmentShader(const std::string& filePath);
    ~FragmentShader();

    void compileShader() override;
    const char* getShaderType() const override;
};
