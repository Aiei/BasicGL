// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

						   // Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls2.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 controls2::getViewMatrix()
{
	return ViewMatrix;
}

glm::mat4 controls2::getProjectionMatrix()
{
	return ProjectionMatrix;
}

glm::vec3 position = glm::vec3(0, 5, 0);
glm::vec3 offset = glm::vec3(0, 3, 3);
float initialFoV = 45.0f;

void controls2::computeMatricesFromInputs(glm::vec3 targetPos, glm::vec3 targetRot)
{
	glm::mat4 m;
	m = glm::rotate(m, glm::radians(targetRot.y), glm::vec3(0, 1, 0);
	glm::vec3 newOffset = glm::vec3(m * glm::vec4(offset, 1));

	position = targetPos + newOffset;

	glm::vec3 direction = targetPos - position;

	float FoV = initialFoV;
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);

	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		targetPos, // and looks here : at the same position, plus "direction"
		glm::vec3(0,1,0)                  // Head is up (set to 0,-1,0 to look upside-down)
	);
}