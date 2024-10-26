#include "Scene1.h"
#include "Transformation.h"
#include "Light.h"

Scene1::Scene1()
    : shaderProgram("sphere_vertex_shader.glsl", "sphere_fragment_shader.glsl"),
    camera(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -90.0f) { // Positioned above looking down

    // Positions of the four spheres in a square layout
    float offset = 2.0f; // Distance from center
    glm::vec3 spherePositions[4] = {
        glm::vec3(-offset, 0.0f, -offset),
        glm::vec3(offset, 0.0f, -offset),
        glm::vec3(-offset, 0.0f, offset),
        glm::vec3(offset, 0.0f, offset)
    };

    // Create and store each sphere at specified positions
    for (const auto& pos : spherePositions) {
        Transformation sphereTransform;
        sphereTransform.translate(pos);
        spheres.emplace_back(sphereModel, sphereTransform, shaderProgram, false, glm::vec3(0.2f, 0.2f, 0.8f)); // Example color
    }

    // Center the light between the spheres
    sceneLight = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)); // Light at center
    sceneLight->addObserver(&shaderProgram);
    camera.addObserver(&shaderProgram);
}

void Scene1::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glClearColor(0.3f, 0.0f, 0.3f, 1.0f);
    glm::vec3 lightPos = sceneLight->getPosition();
    glm::vec3 lightColor = sceneLight->getColor();

    shaderProgram.use();
    for (const auto& sphere : spheres) {
        shaderProgram.setLightingUniforms(lightPos, viewPos, lightColor, sphere.getColor());
        sphere.draw(projection, view);
    }
}

Camera& Scene1::getCamera() {
    return camera;
}

void Scene1::setCamera(Camera& camera) {
    camera.addObserver(&shaderProgram);
}
