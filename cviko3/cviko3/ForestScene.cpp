#include "ForestScene.h"
#include "TreeModel.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


ForestScene::ForestScene() {
    setupScene();
}

void ForestScene::setupScene() {
    Shader vertexShader("forest_vshader.glsl", GL_VERTEX_SHADER);
    Shader fragmentShader("forest_fshader.glsl", GL_FRAGMENT_SHADER);
    ShaderProgram shaderProgram(vertexShader, fragmentShader);

    for (int i = 0; i < 10; ++i) {
        auto treeModel = std::make_shared<TreeModel>();
        auto treeObject = std::make_shared<DrawableObject>(treeModel, shaderProgram);

        Transformation transform;
        transform.translate(i * 3.0f, 0.0f, i * 2.0f);
        transform.scale(1.0f + 0.2f * i, 1.0f, 1.0f);
        transform.rotate(15.0f * i, 0.0f, 1.0f, 0.0f);

        treeObject->setTransformation(transform);

        // Debug v�stup, abychom vid�li, zda je ka�d� strom jinak transformov�n
        glm::mat4 modelMatrix = transform.getMatrix();
        std::cout << "Tree " << i << " modelMatrix: " << glm::to_string(modelMatrix) << std::endl;

        objects.push_back(treeObject);
    }
}

void ForestScene::render() {
    // Vykresli v�echny objekty ve sc�n�
    for (const auto& object : objects) {
        object->draw();
    }
}
