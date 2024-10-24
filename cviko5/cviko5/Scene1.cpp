#include "Scene1.h"
#include "Transformation.h"
#include "Light.h"

Scene1::Scene1()
    : sphereModel(),
    shaderProgram("sphere_vertex_shader.glsl", "sphere_fragment_shader.glsl"),
    sphereObject(sphereModel, Transformation(), shaderProgram, false, glm::vec3(1.0f, 1.0f, 1.0f)) {

    // Nastavení svìtla
    sceneLight = new Light(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(1.0f, 1.0f, 1.0f));  // Bílé svìtlo
    sceneLight->addObserver(&shaderProgram);
}

void Scene1::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glm::vec3 lightPos = sceneLight->getPosition();
    glm::vec3 lightColor = sceneLight->getColor();

    shaderProgram.use();
    shaderProgram.setLightingUniforms(lightPos, viewPos, lightColor, glm::vec3(1.0f, 1.0f, 1.0f));
    sphereObject.draw(projection, view);
}

void Scene1::setCamera(Camera& camera) {
    camera.addObserver(&shaderProgram);
}
