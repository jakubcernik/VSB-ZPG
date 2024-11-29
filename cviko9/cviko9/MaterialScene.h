
#pragma once

#include <vector>
#include "Material.h"
#include "Scene.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Translation.h"
#include "Scale.h"
#include "Light.h"
#include "Model.h"
#include "DrawableObject.h"
#include "Camera.h"

class MaterialScene : public Scene{
public:
    MaterialScene();
    ~MaterialScene();
    void createMaterialShowcase();
    void addObjectWithShader(const Model& model, const glm::vec3& position, ShaderProgram& shader, float scale, const Material& material);
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos);
    Camera& getCamera();

private:
    ShaderProgram phongShader;
    Light* sceneLight;
    Camera camera;
    SphereModel sphereModel;
    std::vector<DrawableObject> objects;
    std::vector<Material> materials;
};
