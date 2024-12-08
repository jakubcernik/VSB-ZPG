#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "Model.h"
#include "TreeModel.h"
#include "BushModel.h"
#include "DrawableObject.h"  // Include the DrawableObject header
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
    ~ForestScene();
    void initializeObservers();
    GLuint loadTexture(const std::string& filename);
    GLuint loadSkyboxTexture(const std::vector<std::string>& faces);
    void configureShader(ShaderProgram& shader, const std::string& textureUniform, int textureUnit);
    void createForest(int treeCount);
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos);
    void setLightingUniforms(ShaderProgram& shader, const glm::vec3& viewPos);
    Camera& getCamera() override;
    void rotateDynamicly(float deltaTime);

private:
    //std::vector<Transformation*> transformations;

    TreeModel treeModel;
    BushModel bushModel;
    PlainModel groundModel;
    SkyboxModel skyboxModel;
    ModelObj houseModel;
    ModelObj loginModel;
    GLuint groundTexture;
    GLuint skyboxTexture;
    GLuint houseTexture;
    ShaderProgram treeShaderProgram;
    ShaderProgram bushShaderProgram;
    ShaderProgram lightShaderProgram;
    ShaderProgram groundShaderProgram;
    ShaderProgram skyboxShaderProgram;
    ShaderProgram houseShaderProgram;

    Camera camera;
    Light* sceneLight;
    std::vector<DrawableObject> rotatingTrees;
    std::vector<float*> rotationAngles;
    std::vector<Light> lights;
    Light flashlight;
    DrawableObject groundObject;
    DrawableObject skyboxObject;
    DrawableObject* houseObject;
    DrawableObject* loginObject;
};


