class mobil:public object3
{
public:
	float currentSpeed = 0.0f;
	float acceleration = 10.01f;
	float maxSpeed = 2.0f;
	float turningSpeed = 100.0f;

	void update();
};