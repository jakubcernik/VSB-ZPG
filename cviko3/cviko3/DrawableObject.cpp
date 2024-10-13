#include "DrawableObject.h"
#include <stdlib.h>
#include <string>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

DrawableObject::DrawableObject(std::shared_ptr<Model> mod, const ShaderProgram& shader)
    : model(mod), shaderProgram(shader) {}

void DrawableObject::draw() {
    shaderProgram.useProgram();

    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    if (currentProgram != shaderProgram.getProgramId()) {
        std::cerr << "ERROR::DRAWABLEOBJECT::PROGRAM_NOT_ACTIVE\nShader program is not active!" << std::endl;
        return;  // Ukon�� metodu, pokud nen� program aktivn�
    }

    // Nastaven� uniformn� matice pro transformaci
    glm::mat4 modelMatrix = transform.getMatrix();
    GLint loc = glGetUniformLocation(shaderProgram.getProgramId(), "modelMatrix");
    if (loc == -1) {
        std::cerr << "Warning: 'modelMatrix' uniform location not found." << std::endl;
    }
    else {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &modelMatrix[0][0]);
    }

    model->bind();
    model->draw();
    model->unbind();
}




void DrawableObject::setTransformation(const Transformation& trans) {
    transform = trans;
}
