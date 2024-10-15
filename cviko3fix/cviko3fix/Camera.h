#pragma once
class Shader; // dopredna deklarace (z duvodu krizoveho odkazu)
class Camera {
private:
    Shader* m_shader;
public:
    Camera(Shader* shader);
    void metoda();
};