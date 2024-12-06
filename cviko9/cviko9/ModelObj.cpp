#include "ModelObj.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>

ModelObj::ModelObj(const std::string& fileName) {
    loadModel(fileName);
}

ModelObj::~ModelObj() {
	glDeleteVertexArrays(1, &vao);
}

void ModelObj::loadModel(const std::string& filename) {

    struct Vertex {
        float Position[3];
        float Normal[3];
        float Texture[2];
        float Tangent[3];
    };

    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace;
    const aiScene* scene = importer.ReadFile(filename, importOptions);

    if (scene) {
        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[i];
            std::vector<Vertex> vertices(mesh->mNumVertices);
            std::vector<unsigned int> indices(mesh->mNumFaces * 3);

            for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
                if (mesh->HasPositions()) {
                    vertices[j].Position[0] = mesh->mVertices[j].x;
                    vertices[j].Position[1] = mesh->mVertices[j].y;
                    vertices[j].Position[2] = mesh->mVertices[j].z;
                }
                if (mesh->HasNormals()) {
                    vertices[j].Normal[0] = mesh->mNormals[j].x;
                    vertices[j].Normal[1] = mesh->mNormals[j].y;
                    vertices[j].Normal[2] = mesh->mNormals[j].z;
                }
                if (mesh->HasTextureCoords(0)) {
                    vertices[j].Texture[0] = mesh->mTextureCoords[0][j].x;
                    vertices[j].Texture[1] = mesh->mTextureCoords[0][j].y;
                }

                if (mesh->HasTangentsAndBitangents()) {
                    vertices[j].Tangent[0] = mesh->mTangents[j].x;
                    vertices[j].Tangent[1] = mesh->mTangents[j].y;
                    vertices[j].Tangent[2] = mesh->mTangents[j].z;
                }
            }

            for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
                indices[j * 3] = mesh->mFaces[j].mIndices[0];
                indices[j * 3 + 1] = mesh->mFaces[j].mIndices[1];
                indices[j * 3 + 2] = mesh->mFaces[j].mIndices[2];
            }

            glGenVertexArrays(1, &vao);
            GLuint VBO, IBO;
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &IBO);

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            indicesCount = indices.size();
        }
    }
    else {
        std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
    }
}

void ModelObj::draw() const {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
