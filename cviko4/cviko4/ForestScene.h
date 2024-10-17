#pragma once
#include "TreeModel.h"
#include "Shader.h"  
#include "DrawableObject.h"
#include "Scene.h"
#include <vector>

class ForestScene : public Scene {
public:
    ForestScene(int treeCount);
    void createForest(int treeCount);
    void render(const glm::mat4& projection) override;

private:
    TreeModel treeModel;
    ShaderProgram shaderProgram;
    std::vector<DrawableObject> objects;  // Uchovávejte stromy v seznamu nebo vektoru

    void addObject(const DrawableObject& object);
};
