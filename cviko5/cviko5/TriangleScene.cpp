#include "TriangleScene.h"
#include "ShaderLoader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

float points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

TriangleScene::TriangleScene() {
    ShaderLoader shaderLoader;
    shaderProgramID = shaderLoader.loadShader("triangle_vertex.glsl", "triangle_fragment.glsl");
    initialize();
}

TriangleScene::~TriangleScene() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void TriangleScene::initialize() {
    // Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TriangleScene::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& viewPos) {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgramID);  // Use the shader program directly
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}


Camera& TriangleScene::getCamera() {
    static Camera dummyCamera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    return dummyCamera;  // This dummyCamera is never used, only here to satisfy the compiler
}

