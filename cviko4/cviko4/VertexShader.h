#pragma once
#include "Shader.h"

class VertexShader : public Shader {
public:
    VertexShader(const std::string& filePath);
    ~VertexShader();

    void compileShader() override;
    const char* getShaderType() const override;
};
