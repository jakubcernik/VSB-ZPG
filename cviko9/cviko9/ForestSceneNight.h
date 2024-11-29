#pragma once
#include "TreeModel.h"
#include "BushModel.h"
#include "Shader.h"  
#include "DrawableObject.h"
#include "Scene.h"
#include "ForestScene.h"
#include "Camera.h"
#include "Light.h"
#include <vector>

class ForestSceneNight : public Scene {
public:
    ForestSceneNight(int treeCount);
    void createForest(int treeCount);
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos);
    Camera& getCamera() override;
    void setCamera(Camera& camera);
    void updateFireflies(float deltaTime);

private:
    void initializeSceneLight();
    void initializeFireflies(int count);
    void initializeFlashlight();


    TreeModel treeModel;
    BushModel bushModel;
    ShaderProgram treeShaderProgram;
    ShaderProgram bushShaderProgram;
    ShaderProgram lightShaderProgram;
    ShaderProgram fireflyShaderProgram;

    Camera camera;
    Light* sceneLight;
    Light* flashlight;
    std::vector<Light*> fireflies;
};