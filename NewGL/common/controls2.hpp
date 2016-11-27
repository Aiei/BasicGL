#ifndef CONTROLS2_HPP
#define CONTROLS2_HPP
class controls2
{
	void computeMatricesFromInputs(glm::vec3 targetPos, glm::vec3 targetRot);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};
#endif