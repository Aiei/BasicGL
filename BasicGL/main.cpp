#include <GL/freeglut.h>
//....

/*GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };*/

struct vertex
{
	GLfloat v[3];
};

vertex verts[16];
int faces[12];

void init()
{
	verts[0] = { 5, 1, 10 };//
	verts[1] = { 5, 1, -10 };
	verts[2] = { 5, 4, 10 };
	verts[3] = { 5, 4, -10 };
	verts[4] = { -5, 4, 10 };
	verts[5] = { -5, 4, -10 };//
	verts[6] = { -5, 1, 10 };
	verts[7] = { -5, 1, -10 };
	verts[8] = { 5, 4, 5 };
	verts[9] = { -5, 4, 5 };
	verts[10] = { 5, 4, -8 };//
	verts[11] = { -5, 4, -8 };
	verts[12] = { 4, 7, 3 };
	verts[13] = { -4, 7, 3 };
	verts[14] = { 4, 7, -7 };
	verts[15] = { -4, 7, -7 };//
}

void vert(int i)
{
	glVertex3fv(verts[i].v);
}

void vertLine(int i[], int size)
{
	for (int a = 0; a < size; a++)
	{
		vert(i[a]);
	}
}

void drawCarBody()
{
	

	/*glBegin(GL_POLYGON);
		glVertex3f(5, 1, 10);
		glVertex3f(5, 1, -10);
		glVertex3f(5, 4, -10);
		glVertex3f(5, 4, -10);
		glVertex3f(-5, 4, 10);

		glVertex3f(-5, 4, -10);
		glVertex3f(-5, 1, 10);
		glVertex3f(-5, 1, -10);
		glVertex3f(5, 4, 5);
		glVertex3f(-5, 4, 5);

		glVertex3f(5, 4, -8);
		glVertex3f(-5, 4, -8);
		glVertex3f(4, 7, 3);
		glVertex3f(-4, 7, 3);
		glVertex3f(4, 7, -7);

		glVertex3f(-4, 7, -7);
	glEnd();*/
	
	/*glBegin(GL_POLYGON);
	glVertex3f(5, 1, 10);
	glVertex3f(5, 1, -10);
	glVertex3f(5, 4, -10);
	glVertex3f(5, 4, -8);
	glVertex3f(5, 4, 5);
	glVertex3f(5, 4, -10);
	glEnd();*/
	glBegin(GL_LINES);
	glVertex3fv(verts[0].v);
	glVertex3fv(verts[1].v);
	glVertex3fv(verts[1].v);
	glVertex3fv(verts[3].v);
	glVertex3fv(verts[3].v);
	glVertex3fv(verts[10].v);
	glVertex3fv(verts[10].v);
	glVertex3fv(verts[8].v);
	glVertex3fv(verts[8].v);
	glVertex3fv(verts[2].v);
	glVertex3fv(verts[2].v);
	glVertex3fv(verts[0].v);
	glEnd();

	/*glBegin(GL_POLYGON);
	glVertex3f(5, 4, -10);
	glVertex3f(5, 4, 5);
	glVertex3f(-5, 4, 5);
	glVertex3f(-5, 4, 10);
	glEnd();*/
	glBegin(GL_LINES);
	glVertex3fv(verts[2].v);
	glVertex3fv(verts[8].v);
	glVertex3fv(verts[8].v);
	glVertex3fv(verts[9].v);
	glVertex3fv(verts[9].v);
	glVertex3fv(verts[4].v);
	glVertex3fv(verts[4].v);
	glVertex3fv(verts[2].v);
	glEnd();

	/*glBegin(GL_POLYGON);
	glVertex3f(-5, 4, 10);
	glVertex3f(-5, 4, 5);
	glVertex3f(-5, 4, -8);
	glVertex3f(-5, 4, -10);
	glVertex3f(-5, 1, -10);
	glVertex3f(-5, 1, 10);
	glEnd();*/
	glBegin(GL_LINES);
	vert(4);
	vert(9);
	vert(9);
	vert(11);
	vert(11);
	vert(5);
	vert(5);
	vert(7);
	vert(7);
	vert(6);
	vert(6);
	vert(4);
	glEnd();

	/*glBegin(GL_POLYGON);
	glVertex3f(-5, 1, 10);
	glVertex3f(-5, 1, -10);
	glVertex3f(5, 1, -10);
	glVertex3f(5, 1, 10);
	glEnd();*/
	glBegin(GL_LINES);
	int f4[] = { 6,7,7,1,1,0,0,6 };
	vertLine(f4, 8);
	glEnd();

	/*glBegin(GL_POLYGON);
	glVertex3f(5, 1, -10);
	glVertex3f(-5, 1, -10);
	glVertex3f(-5, 4, -10);
	glVertex3f(5, 4, -10);
	glEnd();*/
	glBegin(GL_LINES);
	int f5[] = { 1,7,7,5,5,3,3,1 };
	vertLine(f5, 8);
	glEnd();

	/*glBegin(GL_POLYGON);
	glVertex3f(-5, 1, 10);
	glVertex3f(5, 1, 10);
	glVertex3f(5, 4, -10);
	glVertex3f(-5, 4, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-4, 7, 3);
	glVertex3f(4, 7, 3);
	glVertex3f(4, 7, -7);
	glVertex3f(-4, 7, -7);	
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-5, 4, -8);
	glVertex3f(5, 4, -8);
	glVertex3f(5, 4, -10);
	glVertex3f(-5, 4, -10);
	glEnd();*/

	/*glBegin(GL_POLYGON);
	glVertex3f(-5, 4, 5);
	glVertex3f(5, 4, 5);
	glVertex3f(4, 7, 3);
	glVertex3f(-4, 7, 3);
	glEnd();*/
	glBegin(GL_LINES);
	glVertex3f(-5, 4, 5);
	glVertex3f(5, 4, 5);
	glVertex3f(5, 4, 5);
	glVertex3f(4, 7, 3);
	glVertex3f(4, 7, 3);
	glVertex3f(-4, 7, 3);
	glVertex3f(-4, 7, 3);
	glVertex3f(-5, 4, 5);
	glEnd();
	/*glBegin(GL_POLYGON);
	glVertex3f(5, 4, 5);
	glVertex3f(5, 4, -8);
	glVertex3f(4, 7, -7);
	glVertex3f(4, 7, 3);
	glEnd();*/
	glBegin(GL_LINES);
	glVertex3f(5, 4, 5);
	glVertex3f(5, 4, -8);
	glVertex3f(5, 4, -8);
	glVertex3f(4, 7, -7);
	glVertex3f(4, 7, -7);
	glVertex3f(4, 7, 3);
	glVertex3f(4, 7, 3);
	glVertex3f(5, 4, 5);
	glEnd();
	/*glBegin(GL_POLYGON);
	glVertex3f(5, 4, -8);
	glVertex3f(-5, 4, -8);
	glVertex3f(-4, 7, -7);
	glVertex3f(4, 7, -7);
	glEnd();*/
	glBegin(GL_LINES);
	glVertex3f(5, 4, -8);
	glVertex3f(-5, 4, -8);
	glVertex3f(-5, 4, -8);
	glVertex3f(-4, 7, -7);
	glVertex3f(-4, 7, -7);
	glVertex3f(4, 7, -7);
	glVertex3f(4, 7, -7);
	glVertex3f(5, 4, -8);
	glEnd();
	/*glBegin(GL_POLYGON);
	glVertex3f(-5, 4, -8);
	glVertex3f(-5, 4, 5);
	glVertex3f(-4, 7, 3);
	glVertex3f(-4, 7, -7);
	glEnd();*/
	glBegin(GL_LINES);
	glVertex3f(-5, 4, -8);
	glVertex3f(-5, 4, 5);
	glVertex3f(-5, 4, 5);
	glVertex3f(-4, 7, 3);
	glVertex3f(-4, 7, 3);
	glVertex3f(-4, 7, -7);
	glVertex3f(-4, 7, -7);
	glVertex3f(-5, 4, -8);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glRotatef(5, 1, 1, 1);

	glPushMatrix();
	//float size = 0.5;
	drawCarBody();
	/*
	// depan
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(size, size * 2, 0);
	glVertex3f(size * 2, 0, 0);
	glVertex3f(size * 2, -size * 3, 0);
	glVertex3f(size, -size * 5, 0);
	glVertex3f(-size, -size * 5, 0);
	glVertex3f(-size * 2, -size * 3, 0);
	glVertex3f(-size * 2, 0, 0);
	glVertex3f(-size, size * 2, 0);
	glEnd();
	// buntut
	glBegin(GL_POLYGON);
	glVertex3f(size*0.3, -size * 5, 0);
	glVertex3f(size*0.2, -size * 9, 0);
	glVertex3f(-size*0.2, -size * 9, 0);
	glVertex3f(-size*0.3, -size * 5, 0);
	glEnd();

	glRotated(30, 0, 0, 1);
	glColor3f(1, 1, 1);
	//balingV
	glBegin(GL_POLYGON);
	glVertex3f(0.2, 3, 0);
	glVertex3f(-0.2, 3, 0);
	glVertex3f(-0.2, -3, 0);
	glVertex3f(0.2, -3, 0);
	glEnd();
	//balingH
	glBegin(GL_POLYGON);
	glVertex3f(3, 0.2, 0);
	glVertex3f(-3, 0.2, 0);
	glVertex3f(-3, -0.2, 0);
	glVertex3f(3, -0.2, 0);
	glEnd();*/

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

	/*glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);               
	glDepthFunc(GL_LEQUAL);                       
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHTING);*/

	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}