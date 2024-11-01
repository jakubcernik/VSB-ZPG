#include "SphereScene.h"
#include "Transformation.h"
#include "Light.h"

SphereScene::SphereScene()
    : shaderProgram("phong_vertex.glsl", "phong_fragment.glsl"),
    lightShaderProgram("light_vertex.glsl", "light_fragment.glsl"),
    camera(glm::vec3(0.0f, 2.0f, 8.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f) { // Positioned horizontally looking forward

    float offset = 2.0f;
    glm::vec3 spherePositions[4] = {
        glm::vec3(-offset, 0.0f, -offset),
        glm::vec3(offset, 0.0f, -offset),
        glm::vec3(-offset, 0.0f, offset),
        glm::vec3(offset, 0.0f, offset)
    };

    for (const auto& pos : spherePositions) {
        Transformation sphereTransform;
        sphereTransform.translate(pos);
        spheres.emplace_back(sphereModel, sphereTransform, shaderProgram, false, glm::vec3(0.63f, 0.31f, 0.72f));
    }

    sceneLight = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), lightShaderProgram, 0.2); // Light slightly above the center
    sceneLight->addObserver(&shaderProgram);
    camera.addObserver(&shaderProgram);
    camera.addObserver(&lightShaderProgram);
}

void SphereScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glm::vec3 lightPos = sceneLight->getPosition();
    glm::vec3 lightColor = sceneLight->getColor();

    shaderProgram.use();
    for (const auto& sphere : spheres) {
        shaderProgram.setLightingUniforms(lightPos, viewPos, lightColor, sphere.getColor());
        sphere.draw();
    }
    sceneLight->draw();
}

Camera& SphereScene::getCamera() {
    return camera;
}

void SphereScene::setCamera(Camera& camera) {
    camera.addObserver(&shaderProgram);
    camera.addObserver(&lightShaderProgram);
}
