class object3
{
public:
	glm::vec3 pos = glm::vec3(0, 0, 0);
	glm::vec3 rot = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::vec3 forward = glm::vec3(0, 0, 1);

	void rotate(float degree, glm::vec3 axis);
	void move(glm::vec3 direction, float speed);
	void moveForward(float speed);
};