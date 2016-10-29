#include <GL/freeglut.h>
//....

void display(void)
{
	
}

void idle(void)
{

}

void keyboard(unsigned char key, int x, int y)
{

}

void reshape(int w, int h)
{
	
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Window 1");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}