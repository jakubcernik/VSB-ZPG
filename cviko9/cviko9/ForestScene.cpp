#include "ForestScene.h"
#include "Transformation.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"
#include "Light.h"
#include "PlainModel.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <SOIL.h>
#include <glm/gtc/type_ptr.hpp>

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

using namespace std;

inline float generateRandomFloat(float min, float max) {
    static default_random_engine engine{ random_device{}() };
    uniform_real_distribution<float> distribution(min, max);
    return distribution(engine);
}

inline glm::vec3 generateRandomVec3(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
    static default_random_engine engine{ random_device{}() };
    uniform_real_distribution<float> distX(minX, maxX);
    uniform_real_distribution<float> distY(minY, maxY);
    uniform_real_distribution<float> distZ(minZ, maxZ);

    return glm::vec3(distX(engine), distY(engine), distZ(engine));
}

inline glm::vec3 generateAutumnColor() {
    static default_random_engine engine{ random_device{}() };
    uniform_real_distribution<float> redDistribution(0.7f, 1.0f);
    uniform_real_distribution<float> greenDistribution(0.6f, 1.0f);
    uniform_real_distribution<float> blueDistribution(0.0f, 0.2f);

    float red = redDistribution(engine);
    float green = greenDistribution(engine);
    float blue = blueDistribution(engine);

    return glm::vec3(red, green, blue);
}

ForestScene::ForestScene(int treeCount)
    : treeModel(),
    bushModel(),
    groundModel(),
    skyboxModel(),
    houseModel("house.obj"),
    treeShaderProgram("tree_vertex_shader.glsl", "tree_fragment_shader.glsl"),
    bushShaderProgram("bush_vertex_shader.glsl", "bush_fragment_shader.glsl"),
    groundShaderProgram("ground_vertex.glsl", "ground_fragment.glsl"),
    skyboxShaderProgram("skybox_vertex.glsl", "skybox_fragment.glsl"),
    lightShaderProgram("light_vertex.glsl", "light_fragment.glsl"),
    houseShaderProgram("house_vertex.glsl", "house_fragment.glsl"),
    camera(glm::vec3(0.0f, 50.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f),
    flashlight(camera.getPosition(), camera.getFront(), glm::vec3(0.3f, 0.5f, 1.0f), lightShaderProgram, 0.0f, 12.5f, 1),
    groundObject(groundModel, Transformation(), groundShaderProgram, false, glm::vec3(1.0f, 1.0f, 1.0f)),
    skyboxObject(skyboxModel, Transformation(), skyboxShaderProgram, false, glm::vec3(1.0f, 1.0f, 1.0f)),
    houseObject(houseModel, Transformation(), houseShaderProgram, false, glm::vec3(1.0f, 1.0f, 1.0f)),
    followSkybox(true)
{

    lights.push_back(Light(glm::vec3(-50.0f, 20.0f, 20.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.3f, 0.5f, 1.0f), lightShaderProgram, 1.0f, 0.0f, 0));
    lights.push_back(Light(glm::vec3(50.0f, 10.0f, 10.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.3f, 0.5f, 1.0f), lightShaderProgram, 1.0f, 20.0f, 1));

    initializeObservers();
    createForest(treeCount);

    // Load skybox texture
    skyboxTexture = loadSkyboxTexture({
		"posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg"
		});
    if (skyboxTexture == 0) {
		throw runtime_error("Failed to load skybox texture");
	}

    configureSkyboxShader();

    // Load ground texture
    groundTexture = loadGroundTexture("grass.png");
    if (groundTexture == 0) {
        throw runtime_error("Failed to load ground texture");
    }

    configureGroundShader();

    std::shared_ptr<Transformation> houseTransform = std::make_shared<Transformation>();
    houseTransform->addTransformation(std::make_shared<Scale>(glm::vec3(10.0f)));
    DrawableObject house(houseModel, *houseTransform, houseShaderProgram, false, glm::vec3(1.0f, 1.0f, 1.0f));
    addObject(house);

}

void ForestScene::initializeObservers() {
    for (auto& light : lights) {
        light.addObserver(&treeShaderProgram);
        light.addObserver(&bushShaderProgram);
        light.addObserver(&groundShaderProgram);
    }
    flashlight.addObserver(&treeShaderProgram);
    flashlight.addObserver(&bushShaderProgram);
    flashlight.addObserver(&groundShaderProgram);
    flashlight.addObserver(&houseShaderProgram);

    camera.addObserver(&treeShaderProgram);
    camera.addObserver(&bushShaderProgram);
    camera.addObserver(&lightShaderProgram);
    camera.addObserver(&groundShaderProgram);
    camera.addObserver(&houseShaderProgram);
}

GLuint ForestScene::loadGroundTexture(const std::string& filename) {
    GLuint textureID;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height;
    unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }
    if (image == 0) {
        std::cerr << "An error occurred while loading CubeMap." << std::endl;
        std::cerr << "SOIL error: " << SOIL_last_result() << std::endl;
        return 0;
    }

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

GLuint ForestScene::loadSkyboxTexture(const std::vector<std::string>& faces) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    if (faces.size() != 6) {
        std::cerr << "Error: Exactly 6 faces are required for a cubemap." << std::endl;
        return 0;
    }

    int width, height, channels;
    unsigned char* image;

    for (GLuint i = 0; i < faces.size(); i++) {
        image = SOIL_load_image(faces[i].c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
        if (image) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
            );
            SOIL_free_image_data(image);
        }
        else {
            std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            std::cerr << "SOIL error: " << SOIL_last_result() << std::endl;
            return 0;
        }
    }

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    return textureID;
}




void ForestScene::configureGroundShader() {
    groundShaderProgram.use();
    groundShaderProgram.setUniform("texture1", 0);
    groundShaderProgram.free();
}

void ForestScene::configureSkyboxShader() {
    skyboxShaderProgram.use();
    skyboxShaderProgram.setUniform("UISky", 0); // Texture unit 0
    skyboxShaderProgram.free();
}


void ForestScene::createForest(int treeCount) {
    float groundLevel = 0.0f;

    for (int i = 0; i < treeCount; ++i) {
        std::shared_ptr<Transformation> treeTransform = std::make_shared<Transformation>();
        std::shared_ptr<Transformation> bushTransform = std::make_shared<Transformation>();

        glm::vec3 treeRandomPosition = generateRandomVec3(-100.0f, 100.0f, groundLevel, groundLevel, -100.0f, 100.0f);
        glm::vec3 bushRandomPosition = generateRandomVec3(-100.0f, 100.0f, groundLevel, groundLevel, -100.0f, 100.0f);

        treeTransform->addTransformation(std::make_shared<Translation>(treeRandomPosition));
        bushTransform->addTransformation(std::make_shared<Translation>(bushRandomPosition));

        float randomRotationY = static_cast<float>(std::rand() % 360);
        treeTransform->addTransformation(std::make_shared<Rotation>(0, randomRotationY, 0));
        bushTransform->addTransformation(std::make_shared<Rotation>(0, randomRotationY, 0));

        treeTransform->addTransformation(std::make_shared<Scale>(glm::vec3(generateRandomFloat(1.5, 3.0))));
        bushTransform->addTransformation(std::make_shared<Scale>(glm::vec3(generateRandomFloat(15.0, 25.0))));

        glm::vec3 autumnColor = generateAutumnColor();

        DrawableObject tree(treeModel, *treeTransform, treeShaderProgram, true, autumnColor);
        DrawableObject bush(bushModel, *bushTransform, bushShaderProgram, false, glm::vec3(0.1f, 0.8f, 0.2f));

        addObject(tree);
        addObject(bush);
    }

    for (int i = 0; i < 5; ++i) {
        std::shared_ptr<Transformation> treeTransform = std::make_shared<Transformation>();
        treeTransform->addTransformation(std::make_shared<Translation>(glm::vec3(i * 10.0f, groundLevel, 0.0f)));
        treeTransform->addTransformation(std::make_shared<Scale>(glm::vec3(2.0f)));
        glm::vec3 autumnColor = generateAutumnColor();
        DrawableObject tree(treeModel, *treeTransform, treeShaderProgram, true, autumnColor);
        rotatingTrees.push_back(tree);
    }
}

void ForestScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw ground
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    groundShaderProgram.use();
    setLightingUniforms(groundShaderProgram, viewPos);
    groundObject.draw();
    groundShaderProgram.free();

    // Draw other objects
    for (size_t i = 0; i < objects.size(); ++i) {
        const auto& object = objects[i];

        if (object.isTree()) {
            treeShaderProgram.use();
            treeShaderProgram.setUniform("objectColor", object.getColor());
            setLightingUniforms(treeShaderProgram, viewPos);
            object.draw();
            treeShaderProgram.free();
        }
        else if (i == objects.size() - 1) { // Pokud jde o poslední prvek (dùm)
            houseShaderProgram.use();
            setLightingUniforms(houseShaderProgram, viewPos);
            object.draw();
            houseShaderProgram.free();
        }
        else {
            bushShaderProgram.use();
            bushShaderProgram.setUniform("objectColor", object.getColor());
            setLightingUniforms(bushShaderProgram, viewPos);
            object.draw();
            bushShaderProgram.free();
        }
    }


    // Draw lights
    for (auto& light : lights) {
        light.draw();
    }

    flashlight.draw();

    // Draw the skybox last
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);


    skyboxShaderProgram.use();

    // Remove translation from the view matrix if followSkybox is true
    glm::mat4 viewMatrix = followSkybox ? glm::mat4(glm::mat3(view)) : view;


    skyboxShaderProgram.setUniform("modelMatrix", glm::mat4(1.0f));
    skyboxShaderProgram.setUniform("viewMatrix", viewMatrix);
    skyboxShaderProgram.setUniform("projectionMatrix", projection);

    // Bind the cubemap texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

    skyboxObject.draw();

    skyboxShaderProgram.free();

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}




void ForestScene::setLightingUniforms(ShaderProgram& shader, const glm::vec3& viewPos) {
    shader.use();
    shader.setUniform("viewPos", viewPos);
    shader.setUniform("numLights", static_cast<int>(lights.size() + 1));

    for (int i = 0; i < lights.size(); ++i) {
        std::string baseName = "lights[" + std::to_string(i) + "]";
        shader.setUniform((baseName + ".position").c_str(), lights[i].getPosition());
        shader.setUniform((baseName + ".direction").c_str(), lights[i].getDirection());
        shader.setUniform((baseName + ".color").c_str(), lights[i].getColor());
        shader.setUniform((baseName + ".angle").c_str(), lights[i].getAngle());
        shader.setUniform((baseName + ".type").c_str(), lights[i].getType());
    }

    std::string baseName = "lights[" + std::to_string(lights.size()) + "]";
    shader.setUniform((baseName + ".position").c_str(), camera.getPosition());
    shader.setUniform((baseName + ".direction").c_str(), camera.getFront());
    shader.setUniform((baseName + ".color").c_str(), flashlight.getColor());
    shader.setUniform((baseName + ".angle").c_str(), flashlight.getAngle());
    shader.setUniform((baseName + ".type").c_str(), flashlight.getType());
}

Camera& ForestScene::getCamera() {
    return camera;
}
