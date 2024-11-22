#define GLM_ENABLE_EXPERIMENTAL
#pragma once
#include "TreeModel.h"
#include "BushModel.h"
#include "Shader.h"  
#include "DrawableObject.h"
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include <vector>
#include <SOIL.h>
#include "PlainModel.h"

class ForestScene : public Scene {
public:
    ForestScene(int treeCount);
    void initializeObservers();
    GLuint loadTexture(const std::string& filename);
    void configureGroundShader();
    void createForest(int treeCount);
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos);
    void setLightingUniforms(ShaderProgram& shader, const glm::vec3& viewPos);
    Camera& getCamera() override;
    void setCamera(Camera& camera);

private:
    TreeModel treeModel;
    BushModel bushModel;
    PlainModel groundModel;
    GLuint groundTexture;
    ShaderProgram treeShaderProgram;
    ShaderProgram bushShaderProgram;
    ShaderProgram lightShaderProgram;
    ShaderProgram groundShaderProgram;

    Camera camera;
    Light* sceneLight;
    vector<DrawableObject> rotatingTrees;
    vector<Light> lights;
    Light flashlight;
    DrawableObject groundObject;
};
