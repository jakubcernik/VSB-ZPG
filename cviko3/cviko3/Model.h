#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

class Model {
protected:
    unsigned int id; // OpenGL buffer ID

    virtual void setupModel() = 0; // Virtu�ln� metoda, kterou implementuje podt��da

public:
    Model();
    virtual ~Model();

    virtual void draw() const = 0; // Virtu�ln� metoda, kterou podt��da mus� definovat
    void bind() const;
    void unbind() const;
    GLuint getId() const;
};

#endif // MODEL_H
