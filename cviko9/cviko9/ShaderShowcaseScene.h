// ShaderShowcaseScene.h

#pragma once

#include "Scene.h"
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Light.h"
#include "Camera.h"
#include "TreeModel.h"
#include "BushModel.h"
#include "SphereModel.h"

class ShaderShowcaseScene : public Scene {

public:
    ShaderShowcaseScene();
    ~ShaderShowcaseScene();

    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) override;

    Camera& getCamera() override;

private:
    void createShaderShowcase();

    // Helper function to add an object with a specified shader at a position
    void addObjectWithShader(const Model& model, const glm::vec3& position, ShaderProgram& shader, float scale);

    TreeModel treeModel;
    BushModel bushModel;
    SphereModel sphereModel;

    ShaderProgram constantShader;
    ShaderProgram lambertShader;
    ShaderProgram phongShader;
    ShaderProgram blinnShader;
    ShaderProgram lightShaderProgram;

    Light* sceneLight;
    Camera camera;
};
