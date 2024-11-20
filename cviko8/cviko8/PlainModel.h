#pragma once
#include "Model.h"
#include "plain.h"

class PlainModel : public Model {
protected:
    const float* getVertexData() const {
        return plain;
    }


public:
    PlainModel() {
        // Vertex buffer object (VBO)
        glGenBuffers(1, &vbo); // Generate the VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(plain), plain, GL_STATIC_DRAW);

        // Vertex attribute object (VAO)
        glGenVertexArrays(1, &vao); // Generate the VAO
        glBindVertexArray(vao); // Bind the VAO
        glEnableVertexAttribArray(0); // Enable vertex attributes
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
    }

    ~PlainModel() {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    GLuint getVAO() const {
        return vao;
    }

    unsigned int getVertexCount() const {
        return 6;
    }

private:
    GLuint vbo, vao;
};
