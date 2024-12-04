#pragma once
#include "Model.h"
#include <SOIL.h>

class ModelObj : public Model {
private:

	GLuint textureID;

	int indicesCount;

	const float* getVertexData() const { return 0; }

	unsigned int getVertexCount() const { return 0; }
public:
	void draw() const override;
	void loadModel(const std::string& filename);
	void loadTexture(const std::string& filename);
	ModelObj(const std::string& fileName);
	~ModelObj();
};