#pragma once
#include "TreeModel.h"
#include "BushModel.h"
#include "Shader.h"  
#include "DrawableObject.h"
#include "Scene.h"
#include <vector>

class ForestScene : public Scene {
public:
    ForestScene(int treeCount);
    void createForest(int treeCount);
    void render() override;

private:
    TreeModel treeModel;
    BushModel bushModel;
    ShaderProgram treeShaderProgram;
    ShaderProgram bushShaderProgram;
    std::vector<DrawableObject> objects;  // Uchovávejte stromy v seznamu nebo vektoru

    void addObject(const DrawableObject& object);
};
