// SphereScene.cpp

#include "SphereScene.h"
#include "Transformation.h"
#include "Translation.h"
#include "Light.h"

SphereScene::SphereScene()
    : shaderProgram("phong_vertex.glsl", "phong_fragment.glsl"),
    lightShaderProgram("light_vertex.glsl", "light_fragment.glsl"),
    //Camera(startPosition, startUp, startYaw, startPitch);
    camera(glm::vec3(0.0f, 2.0f, 8.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f) {

    float offset = 2.0f;
    glm::vec3 spherePositions[4] = {
        glm::vec3(-offset, 0.0f, -offset),
        glm::vec3(offset, 0.0f, -offset),
        glm::vec3(-offset, 0.0f, offset),
        glm::vec3(offset, 0.0f, offset)
    };

    for (const auto& pos : spherePositions) {
        std::shared_ptr<Transformation> sphereTransform = std::make_shared<Transformation>();
        sphereTransform->addTransformation(std::make_shared<Translation>(pos));
        spheres.emplace_back(sphereModel, *sphereTransform, shaderProgram, false, glm::vec3(0.63f, 0.31f, 0.72f));
    }

    sceneLight = new Light(
        glm::vec3(0.0f, 0.0f, 0.0f),  // position
        glm::vec3(1.0f, 0.0f, 1.0f),  // direction
        glm::vec3(1.0f, 1.0f, 1.0f),  // color
        lightShaderProgram,           // lightShader
        0.2f,                         // scale
        12.5f,                        // angle
        1                             // type
    );

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
    shaderProgram.free();
}

Camera& SphereScene::getCamera() {
    return camera;
}

void SphereScene::setCamera(Camera& camera) {
    camera.addObserver(&shaderProgram);
    camera.addObserver(&lightShaderProgram);
}
