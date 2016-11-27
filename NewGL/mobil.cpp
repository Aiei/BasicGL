#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "object3.hpp"
#include "mobil.hpp"

float levelW = 9.0f;
float levelL = 9.0f;
float levelWm = -18.0f;
float levelLm = -9.0f;

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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE
		&& glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
	{
		if (currentSpeed > 0)
		{
			currentSpeed -= acceleration * 0.5f * deltaTime;
			if (currentSpeed < 0)
				currentSpeed = 0;
		}
		if (currentSpeed < 0)
		{
			currentSpeed += acceleration * 0.5f * deltaTime;
			if (currentSpeed > 0)
				currentSpeed = 0;
		}
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

	if (pos.x > levelW)
		pos.x = levelW;
	if (pos.x < levelWm)
		pos.x = levelWm;
	if (pos.z > levelL)
		pos.z = levelL;
	if (pos.z < levelLm)
		pos.z = levelLm;

	object3::moveForward(currentSpeed * deltaTime);

	lastTime = currentTime;
}