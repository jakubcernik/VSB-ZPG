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

    // Renders the scene
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) override;

    // Accessor for the camera
    Camera& getCamera() override;

private:
    // Creates rows of objects with different shaders for comparison
    void createShaderShowcase();

    // Helper function to add an object with a specified shader at a position
    void addObjectWithShader(const Model& model, const glm::vec3& position, ShaderProgram& shader, float scale);

    TreeModel treeModel;
    BushModel bushModel;
    SphereModel sphereModel;

    // Shaders for different shading techniques
    ShaderProgram constantShader;
    ShaderProgram lambertShader;
    ShaderProgram phongShader;
    ShaderProgram blinnShader;

    // Scene light and camera
    Light* sceneLight;
    Camera camera;
};
