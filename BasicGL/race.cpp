#include <GL/freeglut.h>
#include "obj.cpp"

string carObj = "car.obj";

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glRotatef(5, 1, 1, 1);

	glPushMatrix();
	drawObj();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void idle(void)
{

}

void keyboard(unsigned char key, int x, int y)
{

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-15, 15, -15 * (GLfloat)h / (GLfloat)w,
			15 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-15 * (GLfloat)w / (GLfloat)h,
			15 * (GLfloat)w / (GLfloat)h, -15, 15, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Window 1");

	loadObj(carObj);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}