// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

						   // Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls2.hpp"

glm::mat4 cViewMatrix;
glm::mat4 cProjectionMatrix;

glm::mat4 controls2::getViewMatrix()
{
	return cViewMatrix;
}

glm::mat4 controls2::getProjectionMatrix()
{
	return cProjectionMatrix;
}

glm::vec3 cameraPosition = glm::vec3(0, 5, 0);
glm::vec3 cameraOffset = glm::vec3(0, 3, -5);
float cameraInitialFoV = 45.0f;

void controls2::computeMatricesFromInputs(glm::vec3 targetPos, glm::vec3 targetRot)
{
	glm::mat4 m;
	m = glm::rotate(m, glm::radians(targetRot.y), glm::vec3(0, 1, 0));
	glm::vec3 newOffset = glm::vec3(m * glm::vec4(cameraOffset, 1));

	cameraPosition = targetPos + newOffset;

	glm::vec3 direction = targetPos - cameraPosition;

	float FoV = cameraInitialFoV;
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	cProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);

	cViewMatrix = glm::lookAt(
		cameraPosition,           // Camera is here
		targetPos, // and looks here : at the same position, plus "direction"
		glm::vec3(0,1,0)                  // Head is up (set to 0,-1,0 to look upside-down)
	);
}