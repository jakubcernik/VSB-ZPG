#pragma once

#include "Scene.h"
#include "ShaderProgram.h"
#include "Camera.h"

class Camera;

class TriangleScene : public Scene {

public:
    TriangleScene();
    ~TriangleScene();
    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) override;
    void initialize();
    Camera& getCamera() override;

private:
    unsigned int shaderProgramID;
    unsigned int VAO, VBO;
};
