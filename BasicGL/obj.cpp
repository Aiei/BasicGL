#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/freeglut.h>
#include <GL/GL.h>

#define STUFF_IS_MOVING 0

#if STUFF_IS_MOVING
	#include <unistd.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

struct vertex
{
	float x, y, z;
};

struct coord
{
	float x, y;
};

struct face
{
	int v[3];
	int vt[3];
};

vertex* v;
coord* vt;
face* f;

// count amount of vertices and texture coords
int vCount, vtCount, fCount;

string carObj = "car.obj";
string carTex = "car_texture.png";

static GLuint texture;

void initObj(string objName)
{
	vCount = vtCount = fCount = 0;

	string line;
	ifstream infile(objName);

	while (getline(infile, line))
	{
		if (line.find("v ") != string::npos)
			vCount++;
		else if (line.find("vt ") != string::npos)
			vtCount++;
		else if (line.find("f ") != string::npos)
			fCount++;
	}

	v = new vertex[vCount];
	vt = new coord[vtCount];
	f = new face[fCount];
}

void loadObj(string objName)
{
	initObj(objName);

	int vi, vti, fi;
	vi = vti = fi = 0;
	string line, param;
	float x, y, z;
	ifstream infile(objName);
	while (getline(infile, line))
	{
		istringstream iss(line);
		if (line.find("v ") != string::npos)
		{
			iss >> param >> x >> y >> z;
			v[vi].x = x;
			v[vi].y = y;
			v[vi].z = z;
			vi++;
			//cout << "v " << x << ", " << y << ", " << z << "\n";
		}
		else if (line.find("vt ") != string::npos)
		{
			iss >> param >> x >> y;
			vt[vti].x = x;
			vt[vti].y = y;
			vti++;
			//cout << "vt " << x << ", " << y << "\n";
		}
		else if (line.find("f ") != string::npos)
		{
			string a, b, c;
			iss >> param >> a >> b >> c;

			int pos = a.find("/");
			string va = a.substr(0, pos);
			string vta = a.substr(pos + 1);

			f[fi].v[0] = stoi(va);
			f[fi].vt[0] = stoi(vta);

			pos = b.find("/");
			va = b.substr(0, pos);
			vta = b.substr(pos + 1);

			f[fi].v[1] = stoi(va);
			f[fi].vt[1] = stoi(vta);

			pos = c.find("/");
			va = c.substr(0, pos);
			vta = c.substr(pos + 1);

			f[fi].v[2] = stoi(va);
			f[fi].vt[2] = stoi(vta);

			fi++;
		}
	}
}

void drawObj()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < fCount; i++)
	{
		for (int j = 0; i < 3; i++)
		{
			glTexCoord2f(vt[f[i].vt[j]].x, vt[f[i].vt[j]].y);
			glVertex3f(v[f[i].v[j]].x, v[f[i].v[j]].y, v[f[i].v[j]].z);
		}
	}

	glEnd();
}

void drawWire()
{
	glBegin(GL_LINES);
	for (int i = 0; i < fCount; i++)
	{
		glVertex3f(v[f[i].v[0]].x, v[f[i].v[0]].y, v[f[i].v[0]].z);
		glVertex3f(v[f[i].v[1]].x, v[f[i].v[1]].y, v[f[i].v[1]].z);
		glVertex3f(v[f[i].v[1]].x, v[f[i].v[1]].y, v[f[i].v[1]].z);
		glVertex3f(v[f[i].v[2]].x, v[f[i].v[2]].y, v[f[i].v[2]].z);
		glVertex3f(v[f[i].v[2]].x, v[f[i].v[2]].y, v[f[i].v[2]].z);
		glVertex3f(v[f[i].v[0]].x, v[f[i].v[0]].y, v[f[i].v[0]].z);
	}
	glEnd();
}

GLuint raw_texture_load(const char *filename, int width, int height)
{
	GLuint texture;
	unsigned char *data;
	FILE *file;
	errno_t err;

	// open texture data
	err = fopen_s(&file, filename, "rb");
	if (file == NULL) return 0;

	// allocate buffer
	data = (unsigned char*)malloc(width * height * 4);

	// read texture data
	fread(data, width * height * 4, 1, file);
	fclose(file);

	// allocate a texture name
	glGenTextures(1, &texture);

	// select our current texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// free buffer
	free(data);

	return texture;
}

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* fov, aspect, near, far */
	gluPerspective(60, 1, 1, 10);
	gluLookAt(0, 0, -2, /* eye */
		0, 0, 2, /* center */
		0, 1, 0); /* up */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	/* create a square on the XY
	note that OpenGL origin is at the lower left
	but texture origin is at upper left
	=> it has to be mirrored
	(gasman knows why i have to mirror X as well) */
	/*glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(1, 1); glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2d(1, 0); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2d(0, 0); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2d(0, 1); glVertex3f(1.0, 0.0, 0.0);
	glEnd();*/

	//drawObj();
	glScalef(0.3f, 0.3f, 0.3f);
	glRotatef(60, 1, 0, 0);
	drawWire();

	glDisable(GL_TEXTURE_2D);
	glPopAttrib();

	glFlush();

	glutSwapBuffers();
}

void idle(void)
{
	display();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q') exit(0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void init()
{
	GLfloat glpos[4] = { 2.0, 2.0, 2.0, 0.0 };
	GLfloat glamb[4] = { 1.0, 1.0, 1.0, 0.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_POSITION, glpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, glamb);

	texture = raw_texture_load("raw.raw", 256, 256);
	loadObj(carObj);
}

int main(int argc, char **argv)
{
	/*loadObj(carObj);

	for (int i = 0; i < vCount; i++)
	{
		cout << "v" << i << " " << v[i].x << ", " << v[i].y << ", " << v[i].z << "\n";
	}

	for (int i = 0; i < vtCount; i++)
	{
		cout << "vt" << i << " " << vt[i].x << ", " << vt[i].y << "\n";
	}

	for (int i = 0; i < fCount; i++)
	{
		cout << "f" << i << " ";
		cout << f[i].v[0] << " / " << f[i].vt[0] << " ";
		cout << f[i].v[1] << " / " << f[i].vt[1] << " ";
		cout << f[i].v[2] << " / " << f[i].vt[2] << "\n";
	}

	string c;
	cin >> c;*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Race");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
#if STUFF_IS_MOVING
	glutIdleFunc(idle);
#endif
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}