#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "object3.hpp"

void object3::rotate(float degree, glm::vec3 axis)
{
	rot += axis * degree;

	glm::mat4 m;
	m = glm::rotate(m, glm::radians(rot.y), glm::vec3(0, 1, 0));
	forward = glm::vec3(m * glm::vec4(0,0,1,1));
	forward = glm::normalize(forward);
}

void object3::move(glm::vec3 direction, float speed)
{
	pos += speed * direction;
}

void object3::moveForward(float speed)
{
	pos += speed * forward;
}