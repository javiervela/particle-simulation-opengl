/*-------------------------------------------------------------------------+
 |	This is code that I shamelessly stole from one of you.					|
 |	I just removed some unused code and replaced idleFunc by timerFunc.		|		
 |	All in all it was pretty good, so if it's your code don't feel that		|
 |	I am picking on you when I point out ways to improve parts of the code.	|
 |																			|
 |	jyh. October 5th, 2021													|
 +-------------------------------------------------------------------------*/

#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include "common.h"
#include "serial.h"
#include "glPlatform.h"
#include "ApplConstants.h"
#include "Circle2D.h"

using namespace std;

std::vector<shapes2d::Circle2D *> particles2D;

//--------------------------------------
//  Function prototypes
//--------------------------------------
void myDisplayFunc(void);
void myResizeFunc(int w, int h);
void myMouseFunc(int b, int s, int x, int y);
void myKeyboard(unsigned char c, int x, int y);
void myTimerFunc(int val);

//--------------------------------------
//  Interface constants
//--------------------------------------

const int INIT_WIN_X = 100,
		  INIT_WIN_Y = 40;

//--------------------------------------
//  File-level global variables
//--------------------------------------

int winWidth = 500,
	winHeight = 500;

//	This is the function that does the actual scene drawing
//	Typically, you shold almost never have to call this function directly yourself.
//	It will be called automatically by glut, the way in Java the JRE invokes the paint
//	method of a frame.  Simply, because there is no inheritance/overriding mechanism, we
//	need to set up this function as a "callback function."  In this demo I do it in the
//	main function.  A plus side of this way of doing is that the function can be named any way
//	we want, and that in fact we can have different display functions and change during
//	the execution of the program the current display function used by glut.
//
void myDisplayFunc(void)
{
	//	This clears the buffer(s) we draw into.  We will see later this
	//	semester what this really means
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	There are two "matrix modes" in OpenGL: "projection", which sets up the
	//	camera, and "model view" which we have to be in to do any drawing
	glMatrixMode(GL_MODELVIEW);

	//	This says that we start from the lower-left corner of the screen
	glLoadIdentity();

	/* // Create a square obj     x  ,   y  , scale, color, color
	shapes2d::Square2D square1(1.3f, -3.7f, 1.5f, kRED, kYELLOW);

	// Create a square obj     x  ,   y  , scale, color, color
	shapes2d::Square2D square2(2.5f, 2.5f, 2.f, kPURPLE, kYELLOW);

	// Create a square obj     x  ,   y  , scale, color, color
	shapes2d::Square2D square3(-2.5f, 1.5f, 3.2f, kWHITE, kYELLOW);

	// Create a polygon with n sides   n, x, y, scale, color, color
	shapes2d::RegularPolygon2D regularpoly1(5, -2.5f, -1.75f, 2.5f, kRED, kYELLOW);

	// Call draw functions
	square1.draw();
	square2.draw();
	square3.draw();
	regularpoly1.draw(); */

	for (auto particle : particles2D)
		particle->draw();

	//	We were drawing into the back buffer, now it should be brought
	//	to the forefront.
	glutSwapBuffers();
}

//	This callback function is called when the window is resized
//	(generally by the user of the application).
//	It is also called when the window is created, why I placed there the
//	code to set up the virtual camera for this application.
//
void myResizeFunc(int w, int h)
{
	//	This calls says that I want to use the entire dimension of the window for my drawing.
	glViewport(0, 0, w, h);
	winWidth = w;
	winHeight = h;

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

int main(int argc, char **argv)
{

	int n = parseArgs(argc, argv);

	particle_t *particles = (particle_t *)malloc(n * sizeof(particle_t));
	double size = set_size(n);
	init_particles(n, particles);

	init(n);
	for (int i = 0; i < 10; i++)
	{
		simulateStep(particles, n);
	}

	cout << "Size: " << size << endl;
	particles2D.clear();
	shapes2d::Circle2D *circleAux;
	for (int p_i = 0; p_i < n; p_i++)
	{
		circleAux = new shapes2d::Circle2D((particles[p_i].x / size * 100 - 50), (particles[p_i].y / size * 100 - 50), 0.1, kRED, kBLUE);
		particles2D.push_back(circleAux);
		cout << "p" << p_i << " x: " << particles[p_i].x << " y: " << particles[p_i].y << endl;
	}

	//	Initialize glut and create a new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
	glutCreateWindow("Animated Squares");

	//	set up the callbacks
	glutDisplayFunc(myDisplayFunc);
	glutReshapeFunc(myResizeFunc);
	glutMouseFunc(myMouseFunc);
	glutKeyboardFunc(myKeyboardFunc);

	glutTimerFunc(15, myTimerFunc, 0);

	//	Now we enter the main loop of the program and to a large extend
	//	"lose control" over its execution.  The callback functions that
	//	we set up earlier will be called when the corresponding event
	//	occurs
	glutMainLoop();

	//	This will never be executed (the exit point will be in one of the
	//	call back functions).
	return 0;
}
