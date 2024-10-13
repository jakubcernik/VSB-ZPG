#include "Application.h"
#include "ForestScene.h"

int main() {
    Application app;

    if (!app.initialize()) {
        return -1;
    }

    ForestScene forestScene;
    app.addScene(forestScene);

    while (!app.shouldClose()) {
        app.renderScene();
        app.pollEvents();
    }

    app.terminate();
    return 0;
}
