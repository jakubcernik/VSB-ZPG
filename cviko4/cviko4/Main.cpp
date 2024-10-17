#define GLM_ENABLE_EXPERIMENTAL
#include "Application.h"
#include "ForestScene.h"

int main() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    Application app(windowWidth, windowHeight);

    ForestScene forestScene(50);

    app.setScene(&forestScene);

    app.run();

    return 0;
}

