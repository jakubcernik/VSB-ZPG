#include "Application.h"

int main() {
    // Nastavení šířky a výšky okna
    const int windowWidth = 800;
    const int windowHeight = 600;

    // Vytvoření aplikace
    Application app(windowWidth, windowHeight);

    // Spuštění aplikace
    app.run();

    return 0;
}
