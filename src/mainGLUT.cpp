/**
 * @file main.cpp
 * @author Javier Vela
 * @brief Main executable file
 * @date 2021-10-12
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include "common.h"
#include "serial.h"
#include "glPlatform.h"
#include "ApplConstants.h"
#include "Circle2D.h"
#include "Box2D.h"

using namespace std;

std::vector<shapes2d::Circle2D *> particles2D;
std::vector<shapes2d::Circle2D *> ranges2D;
int n;
particle_t *particles;
double size_world;

const int INIT_WIN_X = 100,
		  INIT_WIN_Y = 40;
int gWidth = 800, gHeight = 800;
float gMaxX = 1.f,
	  gMinX = -1.f,
	  gMaxY = 1.f,
	  gMinY = -1.f;

float SCALE = 1.5;

void display(void)
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	simulateStep(particles, n);

	shapes2d::Box2D box(0.f, 0.f, sqrt(1.f / 2.f) * SCALE, kTRANSPARENT, kWHITE);

	particles2D.clear();
	ranges2D.clear();
	shapes2d::Circle2D *circleAux;
	shapes2d::Circle2D *rangeAux;
	for (int p_i = 0; p_i < n; p_i++)
	{
		circleAux = new shapes2d::Circle2D((particles[p_i].x / size_world * SCALE - SCALE / 2.f), (particles[p_i].y / size_world * SCALE - SCALE / 2.f), 0.01, kRED, kBLUE);
		rangeAux = new shapes2d::Circle2D((particles[p_i].x / size_world * SCALE - SCALE / 2.f), (particles[p_i].y / size_world * SCALE - SCALE / 2.f), 2 * cutoff / size_world, kTRANSPARENT, kRED);
		particles2D.push_back(circleAux);
		ranges2D.push_back(rangeAux);
	}

	for (auto range : ranges2D)
		range->draw();

	for (auto particle : particles2D)
		particle->draw();

	box.draw();

	glutSwapBuffers();
}

void myinit(void)
{
	// Make background WHITE
	glClearColor(COLOR[ColorIndex::kBLACK][0], COLOR[ColorIndex::kBLACK][1], COLOR[ColorIndex::kBLACK][2], COLOR[ColorIndex::kBLACK][3]);

	// Enable transparency
	// https://www.opengl.org/archives/resources/faq/technical/transparency.htm
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(gMinX, gMaxX, gMinY, gMaxY);
}

void myResizeFunc(int w, int h)
{
	//	This calls says that I want to use the entire dimension of the window for my drawing.
	glViewport(0, 0, w, h);
	gWidth = w;
	gHeight = h;

	//	Here I create my virtual camera.  We are going to do 2D drawing for a while, so what this
	//	does is define the dimensions (origin and units) of the "virtual world that my viewport
	//	maps to.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//	Virtual world is 10x10, with origin in the center
	gluOrtho2D(-5.f, 5.f, -5.f, 5.f);

	//	When it's done, request a refresh of the display
	glutPostRedisplay();
}

//	This function is called when a mouse event occurs.  This event, of type s
//	(up, down, dragged, etc.), occurs on a particular button of the mouse.
//
void myMouseFunc(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			//	do something
		}
		else if (state == GLUT_UP)
		{
			exit(0);
		}
		break;

	default:
		break;
	}
}

//	This callback function is called when a keyboard event occurs
//
void myKeyboardFunc(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 27:
		exit(0);
		break;

	default:
		break;
	}
}

void myTimerFunc(int val)
{
	// re-prime the timer
	glutTimerFunc(15, myTimerFunc, val);

	//	And finally I perform the rendering
	glutPostRedisplay();
}

int parseArgs(int argc, char **argv)
{
	if (argc < 3)
	{
		cout << "USAGE:" << endl
			 << argv[0] << " -n <NUMBER PARTICLES>" << endl;
		exit(-1);
	}
	if (strcmp(argv[1], "-n") != 0)
	{
		cout << "USAGE:" << endl
			 << argv[0] << " -n <NUMBER PARTICLES>" << endl;
		exit(-1);
	}

	int n = atoi(argv[2]);

	return n;
}

void myIdleFunc(void)
{
	display();
}

int main(int argc, char **argv)
{
	// Initialize glut and create a new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(gWidth, gHeight);
	glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
	glutCreateWindow("Animated Squares");

	n = parseArgs(argc, argv);

	particles = (particle_t *)malloc(n * sizeof(particle_t));
	size_world = set_size(n);
	init_particles(n, particles);
	init(n);

	// Setup display function
	glutDisplayFunc(display);

	// Setup the callbacks
	// glutReshapeFunc(myResizeFunc);
	glutMouseFunc(myMouseFunc);
	glutKeyboardFunc(myKeyboardFunc);
	glutIdleFunc(myIdleFunc);
	glutTimerFunc(15, myTimerFunc, 0);

	myinit();

	glutMainLoop();

	exit(0);
}
