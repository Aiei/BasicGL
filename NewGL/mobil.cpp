#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "object3.hpp"
#include "mobil.hpp"

void mobil::update()
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		currentSpeed += acceleration * deltaTime;
		if (currentSpeed > maxSpeed)
			currentSpeed = maxSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		currentSpeed -= acceleration * deltaTime;
		if (currentSpeed < -maxSpeed)
			currentSpeed = -maxSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		object3::rotate(turningSpeed * deltaTime, glm::vec3(0, 1, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		object3::rotate(turningSpeed * deltaTime * -1, glm::vec3(0, 1, 0));
	}

	object3::moveForward(currentSpeed * deltaTime);

	lastTime = currentTime;
}