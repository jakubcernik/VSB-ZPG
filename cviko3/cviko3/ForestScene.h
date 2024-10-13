#pragma once
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"
#include <string>

class ForestScene : public Scene {
public:
    ForestScene(const std::string& modelPath, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, int treeCount);

private:
    void createForest(const std::string& modelPath, const ShaderProgram& shader, int treeCount);
};
