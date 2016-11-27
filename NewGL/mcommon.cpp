#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
using namespace glm;

#include "common\objloader.hpp"
#include "common\texture.hpp"

std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;

bool res;

GLuint texture;

GLuint vertexbuffer;
GLuint uvbuffer;
GLuint normalbuffer;

glm::mat4 MVP;

void DrawObject()
{
    //MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void LoadVBO()
{
    glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

void ReadOBJ(char* spath)
{
    res = loadOBJ(spath, vertices, uvs, normals);
}

void ReadTexture(char* spath)
{
    texture = loadDDS(spath);
}

void DeleteBuffers()
{
    glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
}