#pragma once
#include "TreeModel.h"
#include "BushModel.h"
#include "Shader.h"  
#include "DrawableObject.h"
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include <vector>

class ForestScene : public Scene {
public:
    ForestScene(int treeCount);
    void createForest(int treeCount);
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos);
    void setCamera(Camera& camera);

private:
    TreeModel treeModel;
    BushModel bushModel;
    ShaderProgram treeShaderProgram;
    ShaderProgram bushShaderProgram;
    std::vector<DrawableObject> objects;

    void addObject(const DrawableObject& object);

    Light* sceneLight;
};