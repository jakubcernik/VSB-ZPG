#pragma once
#include "Scene.h"
#include "Light.h"
#include "Camera.h"
#include "SphereModel.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"

class SphereScene : public Scene {
public:
    SphereScene();
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) override;
    Camera& getCamera() override;
    void setCamera(Camera& camera);

private:
    SphereModel sphereModel;
    ShaderProgram shaderProgram;
    std::vector<DrawableObject> spheres;
    
    Camera camera;
    Light* sceneLight;
};
