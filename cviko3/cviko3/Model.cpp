#include "Model.h"
#include <GL/glew.h>
using namespace std;

Model::Model(const string& path) {
    loadModel(path);
}

void Model::loadModel(const string& path) {
    // Načítání modelových dat
}

void Model::draw() const {
    // Vykreslování modelu
}
