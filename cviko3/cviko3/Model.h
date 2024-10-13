#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

class Model {
private:
    unsigned int id;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void loadModel(const std::string& filePath);

public:
    Model(const std::string& filePath);
    ~Model();
    unsigned int getId() const;
    void draw() const;
};

#endif // MODEL_H
