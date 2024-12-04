#include "MaterialScene.h"

MaterialScene::MaterialScene()
    : phongShader("phong_vertex.glsl", "phong_material_fragment.glsl"),
    camera(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f),
    sphereModel() {
    sceneLight = new Light(
        glm::vec3(2.5f, 10.0f, 5.0f),  // position
        glm::vec3(1.0f, -1.0f, 0.0f),  // direction
        glm::vec3(1.0f, 1.0f, 1.0f),   // color
        phongShader,                   // lightShader
        0.5f,                          // scale
        0,                             // angle
        0                              // type
    );

    sceneLight->addObserver(&phongShader);
    camera.addObserver(&phongShader);

    createMaterialShowcase();
}

MaterialScene::~MaterialScene() {
    delete sceneLight;
}

void MaterialScene::addObjectWithShader(const Model& model, const glm::vec3& position, ShaderProgram& shader, float scale, const Material& material) {
    Transformation* transform = new Transformation();
    transform->addTransformation(new Translation(position));
    transform->addTransformation(new Scale(glm::vec3(scale)));
    DrawableObject object(model, transform, shader, false, glm::vec3(1.0f, 1.0f, 1.0f));
    objects.push_back(object);
    materials.push_back(material);

}

void MaterialScene::createMaterialShowcase() {
    float offset = -5.0f;

    Material material1(0.1f, 0.5f, 0.9f);
    Material material2(0.5f, 0.6f, 0.5f);
    Material material3(0.9f, 0.7f, 0.1f);

    addObjectWithShader(sphereModel, glm::vec3(-5.0f, 0.0f, offset), phongShader, 1.0f, material1);
    addObjectWithShader(sphereModel, glm::vec3(0.0f, 0.0f, offset), phongShader, 1.0f, material2);
    addObjectWithShader(sphereModel, glm::vec3(5.0f, 0.0f, offset), phongShader, 1.0f, material3);
}

void MaterialScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 lightPos = sceneLight->getPosition();
    glm::vec3 lightColor = sceneLight->getColor();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    phongShader.use();

    for (size_t i = 0; i < objects.size(); ++i) {
        phongShader.setMaterialUniforms(materials[i]); // Material uniforms for each object
        phongShader.setUniform("objectColor", glm::vec3(0.0f, 0.0f, 1.0f)); // blue
        objects[i].draw();
    }

    phongShader.setLightingUniforms(lightPos, viewPos, lightColor, glm::vec3(1.0f, 1.0f, 1.0f)); // white
    sceneLight->draw();
}

Camera& MaterialScene::getCamera() {
    return camera;
}
