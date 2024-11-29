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
#include "SkyboxModel.h"
#include "ModelObj.h"

class ForestScene : public Scene {
public:
    ForestScene(int treeCount);
    void initializeObservers();
    GLuint loadGroundTexture(const std::string& filename);
    GLuint loadSkyboxTexture(const std::vector<std::string>& faces);
    void configureGroundShader();
    void configureSkyboxShader();
    void createForest(int treeCount);
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos);
    void setLightingUniforms(ShaderProgram& shader, const glm::vec3& viewPos);
    Camera& getCamera() override;

private:
    TreeModel treeModel;
    BushModel bushModel;
    PlainModel groundModel;
    SkyboxModel skyboxModel;
    ModelObj houseModel;
    GLuint groundTexture;
    GLuint skyboxTexture;
    ShaderProgram treeShaderProgram;
    ShaderProgram bushShaderProgram;
    ShaderProgram lightShaderProgram;
    ShaderProgram groundShaderProgram;
    ShaderProgram skyboxShaderProgram;
    ShaderProgram houseShaderProgram;

    Camera camera;
    Light* sceneLight;
    vector<DrawableObject> rotatingTrees;
    vector<Light> lights;
    Light flashlight;
    DrawableObject groundObject;
    DrawableObject skyboxObject;
    DrawableObject houseObject;

    bool followSkybox;
};
