#include "Model.h"
#include <GL/glew.h>

Models::Models() : VAO_square(0), VAO_triangle(0) {}

Models::~Models() {
    glDeleteVertexArrays(1, &VAO_square);
    glDeleteVertexArrays(1, &VAO_triangle);
}

void Models::createModels()
{
    // �tverec (d�m)
    float pointsSquare[] = {
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    GLuint VBO_square;
    glGenBuffers(1, &VBO_square);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_square);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointsSquare), pointsSquare, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO_square);
    glBindVertexArray(VAO_square);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_square);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Troj�heln�k (st�echa)
    float pointsTriangle[] = {
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.0f,  1.0f, 0.0f
    };

    GLuint VBO_triangle;
    glGenBuffers(1, &VBO_triangle);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointsTriangle), pointsTriangle, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO_triangle);
    glBindVertexArray(VAO_triangle);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_triangle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Models::drawSquare()
{
    glBindVertexArray(VAO_square);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Models::drawTriangle()
{
    glBindVertexArray(VAO_triangle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}