// ShaderShowcaseScene.cpp

#include "ShaderShowcaseScene.h"
#include "Transformation.h"
#include "Translation.h"
#include "Scale.h"
#include "Light.h"

ShaderShowcaseScene::ShaderShowcaseScene()
    : constantShader("constant_vertex.glsl", "constant_fragment.glsl"),
    lambertShader("lambert_vertex.glsl", "lambert_fragment.glsl"),
    phongShader("phong_vertex.glsl", "phong_fragment.glsl"),
    blinnShader("blinn_vertex.glsl", "blinn_fragment.glsl"),
    lightShaderProgram("light_vertex.glsl", "light_fragment.glsl"),
    //Camera(startPosition, startUp, startYaw, startPitch);
    camera(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f),
    treeModel(),
    bushModel(),
    sphereModel()
{
    sceneLight = new Light(
        glm::vec3(2.5f, 10.0f, 5.0f),  // position
        glm::vec3(1.0f, -1.0f, 0.0f),  // direction
        glm::vec3(1.0f, 1.0f, 1.0f),   // color
        lightShaderProgram,            // lightShader
        1.0f,                          // scale
        12.5f,                         // angle
        1                              // type
    );

    sceneLight->addObserver(&constantShader);
    sceneLight->addObserver(&lambertShader);
    sceneLight->addObserver(&phongShader);
    sceneLight->addObserver(&blinnShader);

    camera.addObserver(&constantShader);
    camera.addObserver(&lambertShader);
    camera.addObserver(&phongShader);
    camera.addObserver(&blinnShader);
    camera.addObserver(&lightShaderProgram);

    createShaderShowcase();
}

ShaderShowcaseScene::~ShaderShowcaseScene() {
    delete sceneLight;
}

void ShaderShowcaseScene::createShaderShowcase() {
    float offset = -5.0f;

    // Trees
    addObjectWithShader(treeModel, glm::vec3(-5.0f, 0.0f, offset), constantShader, 0.4f);
    addObjectWithShader(treeModel, glm::vec3(0.0f, 0.0f, offset), lambertShader, 0.4f);
    addObjectWithShader(treeModel, glm::vec3(5.0f, 0.0f, offset), phongShader, 0.4f);
    addObjectWithShader(treeModel, glm::vec3(10.0f, 0.0f, offset), blinnShader, 0.4f);

    // Bushes
    addObjectWithShader(bushModel, glm::vec3(-5.0f, -offset, offset), constantShader, 3.0f);
    addObjectWithShader(bushModel, glm::vec3(0.0f, -offset, offset), lambertShader, 3.0f);
    addObjectWithShader(bushModel, glm::vec3(5.0f, -offset, offset), phongShader, 3.0f);
    addObjectWithShader(bushModel, glm::vec3(10.0f, -offset, offset), blinnShader, 3.0f);

    // Spheres
    addObjectWithShader(sphereModel, glm::vec3(-5.0f, -2 * offset, offset), constantShader, 1.0f);
    addObjectWithShader(sphereModel, glm::vec3(0.0f, -2 * offset, offset), lambertShader, 1.0f);
    addObjectWithShader(sphereModel, glm::vec3(5.0f, -2 * offset, offset), phongShader, 1.0f);
    addObjectWithShader(sphereModel, glm::vec3(10.0f, -2 * offset, offset), blinnShader, 1.0f);
}

void ShaderShowcaseScene::addObjectWithShader(const Model& model, const glm::vec3& position, ShaderProgram& shader, float scale) {
    Transformation* transform = new Transformation();
    transform->addTransformation(new Translation(position));
    transform->addTransformation(new Scale(glm::vec3(scale)));  // Scale to match the size of the objects
    DrawableObject object(model, transform, shader, false, glm::vec3(1.0f, 1.0f, 1.0f));
    addObject(object);

    // Store the transformation for cleanup later
    transformations.push_back(transform);
}


void ShaderShowcaseScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 lightPos = sceneLight->getPosition();
    glm::vec3 lightColor = sceneLight->getColor();
    glm::vec3 uniformColor = glm::vec3(0.5f, 0.8f, 0.3f); // Same color for all objects

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    // 3 rows of objects, 4 shaders
    ShaderProgram* shaders[] = { &constantShader, &lambertShader, &phongShader, &blinnShader };

    for (int row = 0; row < 3; ++row) {
        for (int i = 0; i < 4; ++i) {
            int index = row * 4 + i; // index in objects array

            shaders[i]->use();
            shaders[i]->setLightingUniforms(lightPos, viewPos, lightColor, uniformColor);

            objects[index].draw();
        }
    }
    sceneLight->draw();
}

Camera& ShaderShowcaseScene::getCamera() {
    return camera;
}
