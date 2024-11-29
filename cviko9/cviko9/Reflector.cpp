
/**
 * @file main.cpp
 *
 * @brief Main function, Fundamentals of Computer Graphics
 *
 * @author Martin Nemec
 **/

#pragma once
 //Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

#include "plain.h"

const char* vertex_shader =
"#version 330\n"
"uniform mat4 modelMatrix;"
"uniform mat4 projectMatrix;"
"uniform mat4 viewMatrix;"
"out vec3 worldNormal;"
"out vec3 worldPosition;"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vn;"
"void main () {"
"   worldNormal = transpose(inverse(mat3(modelMatrix))) * vn;"
"   vec4 position = modelMatrix * vec4(vp, 1.0); "
"   worldPosition =  position.xyz / position.w;"
"   gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"in vec3 worldNormal;"
"uniform vec3 spotDir;"
"in vec3 worldPosition;"
"void main () {"
"    vec3 lightPosition = vec3(0,5,0);"
"    vec3 camVector = normalize(vec3(5,5,0) - worldPosition);"
"    vec3 lightVector = normalize(lightPosition - worldPosition);"
"    vec3 reflectVector = normalize(reflect(-lightVector, normalize(worldNormal)));"
"    float diff = max(dot(normalize(lightVector), normalize(worldNormal)), 0.0);"
"    float spec = pow(max(dot(reflectVector, camVector), 0.0), 32);"
"    float spot = dot(normalize(spotDir), -lightVector);"
"    if (spot < 0.99) {"
"       spec = 0; diff = 0;"
"	 }"
"    spot=(spot-0.99)/(1-0.99);"
"    gl_FragColor = (0.01 +(diff+spec)*spot) * vec4(0.385, 0.647, 0.812, 1.0);"
"}";
/*
int main(void)
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	//create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	GLuint VBO, VAO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plain), plain, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glm::mat4 M = glm::mat4(1.0f);

	GLint varLocation;
	float alpha = 0;
	glEnable(GL_DEPTH_TEST); //z-buffer

	while (!glfwWindowShouldClose(window))
	{
		alpha += 0.01;
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glm::vec3 dir = glm::vec3(glm::cos(alpha) * 0.4, -1, glm::sin(alpha) * 0.4);
		varLocation = glGetUniformLocation(shaderProgram, "spotDir");
		glUniform3f(varLocation, dir.x, dir.y, dir.z);

		M = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f));
		varLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
		glUniformMatrix4fv(varLocation, 1, GL_FALSE, glm::value_ptr(M));

		M = glm::lookAt(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
		varLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
		glUniformMatrix4fv(varLocation, 1, GL_FALSE, glm::value_ptr(M));

		M = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);
		varLocation = glGetUniformLocation(shaderProgram, "projectMatrix");
		glUniformMatrix4fv(varLocation, 1, GL_FALSE, glm::value_ptr(M));

		// draw plain
		glDrawArrays(GL_TRIANGLES, 0, 6); //mode,first,count

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
*/