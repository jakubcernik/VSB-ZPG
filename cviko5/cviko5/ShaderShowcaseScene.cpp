// ShaderShowcaseScene.cpp

#include "ShaderShowcaseScene.h"
#include "Transformation.h"
#include "Light.h"

ShaderShowcaseScene::ShaderShowcaseScene()
    : constantShader("constant_vertex.glsl", "constant_fragment.glsl"),
    lambertShader("lambert_vertex.glsl", "lambert_fragment.glsl"),
    phongShader("phong_vertex.glsl", "phong_fragment.glsl"),
    blinnShader("blinn_vertex.glsl", "blinn_fragment.glsl"),
    camera(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f),
    treeModel(),
    bushModel(),
    sphereModel()
{
    sceneLight = new Light(glm::vec3(2.5f, 10.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f));


    sceneLight->addObserver(&constantShader);
    sceneLight->addObserver(&lambertShader);
    sceneLight->addObserver(&phongShader);
    sceneLight->addObserver(&blinnShader);

    camera.addObserver(&constantShader);
    camera.addObserver(&lambertShader);
    camera.addObserver(&phongShader);
    camera.addObserver(&blinnShader);

    createShaderShowcase();
}


ShaderShowcaseScene::~ShaderShowcaseScene() {
    delete sceneLight;
}


void ShaderShowcaseScene::createShaderShowcase() {
    float offset = -5.0f;

    // Trees
    addObjectWithShader(treeModel, glm::vec3(-5.0f, 0.0f, offset), constantShader,0.4f);
    addObjectWithShader(treeModel, glm::vec3(0.0f, 0.0f, offset), lambertShader,0.4f);
    addObjectWithShader(treeModel, glm::vec3(5.0f, 0.0f, offset), phongShader,0.4f);
    addObjectWithShader(treeModel, glm::vec3(10.0f, 0.0f, offset), blinnShader,0.4f);

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
    Transformation transform;
    transform.translate(position);
    transform.setScale(glm::vec3(scale));  // Scale to match the size of the objects
    DrawableObject object(model, transform, shader, false, glm::vec3(1.0f, 1.0f, 1.0f));
    addObject(object);
}


void ShaderShowcaseScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glm::vec3 lightPos = sceneLight->getPosition();
    glm::vec3 lightColor = sceneLight->getColor();
    glm::vec3 uniformColor = glm::vec3(0.5f, 0.8f, 0.3f); // Same color for all objects

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    constantShader.use();
    constantShader.setUniform("objectColor", uniformColor);
    objects[0].draw(projection, view);

    // Render with the Lambert shader
    lambertShader.use();
    lambertShader.setLightingUniforms(lightPos, viewPos, lightColor, uniformColor);
    objects[1].draw(projection, view);

    // Render with the Phong shader
    phongShader.use();
    phongShader.setLightingUniforms(lightPos, viewPos, lightColor, uniformColor);
    objects[2].draw(projection, view);

    // Render with the Blinn shader
    blinnShader.use();
    blinnShader.setLightingUniforms(lightPos, viewPos, lightColor, uniformColor);
    objects[3].draw(projection, view);
 
    for (int i = 4; i < objects.size(); i += 4) {
        constantShader.use();
        constantShader.setUniform("objectColor", uniformColor);
        objects[i].draw(projection, view);

        lambertShader.use();
        lambertShader.setLightingUniforms(lightPos, viewPos, lightColor, uniformColor);
        objects[i + 1].draw(projection, view);

        phongShader.use();
        phongShader.setLightingUniforms(lightPos, viewPos, lightColor, uniformColor);
        objects[i + 2].draw(projection, view);

        blinnShader.use();
        blinnShader.setLightingUniforms(lightPos, viewPos, lightColor, uniformColor);
        objects[i + 3].draw(projection, view);
    }
}


Camera& ShaderShowcaseScene::getCamera() {
    return camera;
}
