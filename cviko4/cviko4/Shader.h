#pragma once

class Shader {
protected:
	unsigned int shaderID;

public:
	Shader();
    virtual ~Shader();

    virtual void compileShader(const char* source) = 0;
    unsigned int getShaderID() const;
    virtual const char* getShaderType() const = 0;
};