// ForestScene.h
#pragma once
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"

class ForestScene : public Scene {
public:
    ForestScene(const std::string& modelPath, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, int treeCount);

private:
    Model treeModel;         // Pøidej èlen treeModel
    ShaderProgram shader;    // Pøidej èlen shader
    void createForest(int treeCount); // Metoda createForest má jeden parametr
};
