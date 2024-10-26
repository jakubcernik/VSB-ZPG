#pragma once
#include "Scene.h"
#include "Light.h"
#include "Camera.h"
#include "SphereModel.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"

class Scene1 : public Scene {
public:
    Scene1();
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) override;
    Camera& getCamera() override;
    void setCamera(Camera& camera);

private:
    SphereModel sphereModel;
    ShaderProgram shaderProgram;
    DrawableObject sphereObject;
    
    Camera camera;
    Light* sceneLight;
};
