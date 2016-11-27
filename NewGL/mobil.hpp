class mobil:public object3
{
public:
	float currentSpeed = 0.0f;
	float acceleration = 8.0f;
	float maxSpeed = 3.0f;
	float turningSpeed = 75.0f;

	void update();
};