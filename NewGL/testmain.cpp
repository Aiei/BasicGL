// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;

#include "common\shader.hpp"
#include "common\texture.hpp"
#include "common\controls.hpp"
#include "common\objloader.hpp"
#include "common\vboindexer.hpp"

#include "object3.hpp"
#include "mobil.hpp"
#include "controls2.hpp"

int main(void)
{
	mobil mobil1;
	controls2 tpv;
	bool usingTpv = false;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Car n Circuit", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwPollEvents();
	glfwSetCursorPos(window, 800 / 2, 600 / 2);

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");
	
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	GLuint Texture = loadDDS("objs/cartex.DDS");
	GLuint Texture2 = loadDDS("objs/circuittex.DDS");

	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("objs/car.obj", vertices, uvs, normals);

	std::vector<glm::vec3> vertices2;
	std::vector<glm::vec2> uvs2;
	std::vector<glm::vec3> normals2;
	bool res2 = loadOBJ("objs/circuit.obj", vertices2, uvs2, normals2);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	GLuint vertexbuffer2;
	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);
	GLuint uvbuffer2;
	glGenBuffers(1, &uvbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
	glBufferData(GL_ARRAY_BUFFER, uvs2.size() * sizeof(glm::vec2), &uvs2[0], GL_STATIC_DRAW);
	GLuint normalbuffer2;
	glGenBuffers(1, &normalbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
	glBufferData(GL_ARRAY_BUFFER, normals2.size() * sizeof(glm::vec3), &normals2[0], GL_STATIC_DRAW);

	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	do {
		mobil1.update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			usingTpv = true;
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			usingTpv = false;
		}

		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		if (usingTpv)
		{
			tpv.computeMatricesFromInputs(mobil1.pos, mobil1.rot);
			ProjectionMatrix = tpv.getProjectionMatrix();
			ViewMatrix = tpv.getViewMatrix();
		}
		else
		{
			computeMatricesFromInputs();
			ProjectionMatrix = getProjectionMatrix();
			ViewMatrix = getViewMatrix();
		}

		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		MVP = glm::translate(MVP, mobil1.pos);
		MVP = glm::rotate(MVP, glm::radians(mobil1.rot.y), glm::vec3(0, 1, 0));

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = glm::vec3(0, 10, 0);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);

		glUniform1i(TextureID, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		/* Draw circuit */
		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glBindTexture(GL_TEXTURE_2D, Texture2);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, vertices2.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &vertexbuffer2);
	glDeleteBuffers(1, &uvbuffer2);
	glDeleteBuffers(1, &normalbuffer2);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	
	glfwTerminate();

	return 0;
}