// ForestScene.h
#pragma once
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"

class ForestScene : public Scene {
public:
    ForestScene(const std::string& modelPath, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, int treeCount);

private:
    Model treeModel;         // P�idej �len treeModel
    ShaderProgram shader;    // P�idej �len shader
    void createForest(int treeCount); // Metoda createForest m� jeden parametr
};
