/*
#include "MaterialScene.h"

MaterialScene::MaterialScene()
    : phongShader("phong_vertex.glsl", "phong_fragment.glsl"),
    camera(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f),
    sphereModel() { // Adjust the path to your sphere model
    sceneLight = new Light(
        glm::vec3(2.5f, 10.0f, 5.0f),  // position
        glm::vec3(1.0f, -1.0f, 0.0f),  // direction
        glm::vec3(1.0f, 1.0f, 1.0f),   // color
        phongShader,                   // lightShader
        1.0f,                          // scale
        12.5f,                         // angle
        1                              // type
    );

    sceneLight->addObserver(&phongShader);
    camera.addObserver(&phongShader);

    createMaterialShowcase();
}

MaterialScene::~MaterialScene() {
    delete sceneLight;
}

void MaterialScene::createMaterialShowcase() {
    float offset = -5.0f;

    Material material1(0.1f, 0.5f, 0.9f);
    Material material2(0.2f, 0.6f, 0.8f);
    Material material3(0.3f, 0.7f, 0.7f);

    addObjectWithShader(sphereModel, glm::vec3(-5.0f, 0.0f, offset), phongShader, 1.0f, material1);
    addObjectWithShader(sphereModel, glm::vec3(0.0f, 0.0f, offset), phongShader, 1.0f, material2);
    addObjectWithShader(sphereModel, glm::vec3(5.0f, 0.0f, offset), phongShader, 1.0f, material3);
}

void MaterialScene::addObjectWithShader(const Model& model, const glm::vec3& position, ShaderProgram& shader, float scale, const Material& material) {
    std::shared_ptr<Transformation> transform = std::make_shared<Transformation>();
    transform->addTransformation(std::make_shared<Translation>(position));
    transform->addTransformation(std::make_shared<Scale>(glm::vec3(scale)));  // Scale to match the size of the objects
    DrawableObject object(model, *transform, shader, false, glm::vec3(1.0f, 1.0f, 1.0f));
    object.setMaterial(material);
    objects.push_back(object);
}

void MaterialScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 lightPos = sceneLight->getPosition();
    glm::vec3 lightColor = sceneLight->getColor();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    phongShader.use();
    phongShader.setLightingUniforms(lightPos, viewPos, lightColor, glm::vec3(1.0f, 0.0f, 0.8f));

    for (auto& object : objects) {
        phongShader.setMaterialUniforms(object.getMaterial());
        object.draw();
    }

    sceneLight->draw();
}

Camera& MaterialScene::getCamera() {
    return camera;
}
*/