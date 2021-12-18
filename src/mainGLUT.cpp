/**
 * @file main.cpp
 * @author Javier Vela
 * @brief Main executable file updated by Andrew Laraw L.
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
#include "Particle2D.h"
#include "Box2D.h"

using namespace std;

const int INIT_WIN_X = 100,
		  INIT_WIN_Y = 40;
int gWidth = 800, gHeight = 800;
float gMaxX = 1.f,
	  gMinX = -1.f,
	  gMaxY = 1.f,
	  gMinY = -1.f;

float SCALE = 1;

std::vector<shapes2d::Particle2D *> particles2D;
std::vector<shapes2d::Circle2D *> ranges2D;
int n;
particle_t *particles;
double size_world;

shapes2d::Particle2D *circleAux;
shapes2d::Circle2D *rangeAux;
shapes2d::Box2D *box;

///-----------------------------------------------------------------
/// GUI
///-----------------------------------------------------------------

// Color Options for Menu
ColorIndex  gCurrentP_Color = kTRANSPARENT;
ColorIndex  gCurrentContourP_Color = kBLUE;
ColorIndex  gCurrentR_Color = kTRANSPARENT;
ColorIndex  gCurrentContourR_Color = kRED;
ColorIndex 	gPrimaryC = kWHITE;
ColorIndex	gMediumC = kORANGE;
ColorIndex	gFastC = kRED;

///-----------------------------------------------------------------
///  GUI constants
///-----------------------------------------------------------------
const int   QUIT_MENU = 0,
            CLEAR_MENU = 1,
            SEPARATOR = -1;

///-----------------------------------------------------------------
///  function prototypes
///-----------------------------------------------------------------
void pcontourColorSelection(ColorIndex colorCode);
void rcolorSelection(ColorIndex colorCode);
void rcontourColorSelection(ColorIndex colorCode);
void colorSelection(ColorIndex colorCode);
void pspeedColorSelection(ColorIndex colorCode);
void mspeedColorSelection(ColorIndex colorCode);
void fspeedColorSelection(ColorIndex colorCode);

void menuHandler(int value);
void pspeedMenuHandler(int value);
void mspeedMenuHandler(int value);
void fspeedMenuHandler(int value);

void display(void);
void pixelToWorld(int ix, int iy, float *x, float *y);
void myResize(int w, int h);
void myMouse(int b, int s, int x, int y);
void myKeyboard(unsigned char, int x, int y);
void myinit(void);

///-----------------------------------------------------------------


/**
 * @brief Create particles, simulate the particles movement.
 * @brief Draw the particles movement.
 * 
 */
void display(void)
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	simulateStep(particles, n);
	
	box = new shapes2d::Box2D(0.f, 0.f, sqrt(1.f / 2.f) * SCALE, kTRANSPARENT, kWHITE);

	particles2D.clear();
	ranges2D.clear();

	for (int p_i = 0; p_i < n; p_i++)
	{
		circleAux = new shapes2d::Particle2D((particles[p_i].x / size_world * SCALE - SCALE / 2.f), 
											(particles[p_i].y / size_world * SCALE - SCALE / 2.f),
											particles[p_i].vx, 
											particles[p_i].vy, 0.01, 
											gCurrentP_Color, gCurrentContourP_Color,
											gPrimaryC, gMediumC, gFastC);
		rangeAux = new shapes2d::Circle2D((particles[p_i].x / size_world * SCALE - SCALE / 2.f), 
										 (particles[p_i].y / size_world * SCALE - SCALE / 2.f), 
										 SCALE * cutoff / size_world, 
										 gCurrentR_Color, gCurrentContourR_Color);
		particles2D.push_back(circleAux);
		ranges2D.push_back(rangeAux);
	}

	for (auto range : ranges2D)
		range->draw();

	for (auto particle : particles2D)
		particle->draw();

	box->draw();

	glutSwapBuffers();
}

/**
 * @brief Create the Menu.
 * 
 */
void myinit(void)
{
	// Make background WHITE
	glClearColor(COLOR[ColorIndex::kBLACK][0], 
				COLOR[ColorIndex::kBLACK][1], 
				COLOR[ColorIndex::kBLACK][2], 
				COLOR[ColorIndex::kBLACK][3]);

	// Enable transparency
	// https://www.opengl.org/archives/resources/faq/technical/transparency.htm
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(gMinX, gMaxX, gMinY, gMaxY);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(gMinX, gMaxX, gMinY, gMaxY);

    /// Create Menus
    int menu, pcolorSubMenu, mspeedColorSubMenu, fspeedSubMenu;

    /// submenu for color selection choices
    ///  Note how I use my arrays defined in ApplConstants.h to automatically generate my menus
    pcolorSubMenu = glutCreateMenu(pspeedMenuHandler);
	for (int k=0; k<kNB_COLORS; k++)
   		glutAddMenuEntry(colorMenuStr[k].c_str(), colorMenuCode[k] );

    mspeedColorSubMenu = glutCreateMenu(mspeedMenuHandler);
    for (int k=0; k<kNB_COLORS; k++)
   		glutAddMenuEntry(colorMenuStr[k].c_str(), colorMenuCode[k] );

	fspeedSubMenu = glutCreateMenu(fspeedMenuHandler);
    for (int k=0; k<kNB_COLORS; k++)
   		glutAddMenuEntry(colorMenuStr[k].c_str(), colorMenuCode[k] );

    /// Main menu that the submenus are connected to
    menu = glutCreateMenu(menuHandler);
    glutAddMenuEntry("Clear Screen", CLEAR_MENU);
    glutAddSubMenu("Particle Color", pcolorSubMenu);
    glutAddSubMenu("Medium Speed Color", mspeedColorSubMenu);
	glutAddSubMenu("Fast Speed Color", fspeedSubMenu);
    glutAddMenuEntry("-", SEPARATOR);
    glutAddMenuEntry("Exit", QUIT_MENU);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * @brief This resize function overrides the user's settings by *forcing*
 * @brief the window to keep pre-defined proportions
 * 
 * @param w 
 * @param h 
 */
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

/**
 * @brief This function is called when a mouse event occurs.  
 * @brief This event, of type (up, down, dragged, etc.), occurs on a particular button of the mouse.
 * 
 * @param button 
 * @param state 
 * @param x 
 * @param y 
 */
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

/**
 * @brief This callback function is called when a keyboard event occurs.
 * @brief It is not functional yet. It is only set up for future development.
 * 
 * @param c 
 * @param x 
 * @param y 
 */
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

/**
 * @brief Set timer function for glut
 * 
 * @param val 
 */
void myTimerFunc(int val)
{
	// re-prime the timer
	glutTimerFunc(15, myTimerFunc, val);

	//	And finally I perform the rendering
	glutPostRedisplay();
}

/**
 * @brief Check the parameters of the initial program launch
 * 
 * @param argc 3
 * @param argv -n <NUMBER PARTICLES>
 * @return int 
 */
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

/**
 * @brief Set Idle function of glut
 * 
 */
void myIdleFunc(void)
{
	display();
}

/**
 * @brief set the color of the particles. 
 * @brief This function has the same effect as `pspeedColorSelection()`
 */
void pcolorSelection(ColorIndex colorCode)
{
    gCurrentP_Color = colorCode;
}

/**
 * @brief Set the contour color of the particles 
 */
void pcontourColorSelection(ColorIndex colorCode){
    gCurrentContourP_Color = colorCode;
}

/**
 * @brief Set the ring color of the particles 
 */
void rcolorSelection(ColorIndex colorCode)
{
    gCurrentR_Color = colorCode;
}

/**
 * @brief Set the ring contour color of the particles 
 */
void rcontourColorSelection(ColorIndex colorCode){
    gCurrentContourR_Color = colorCode;
}

/**
 * @brief Set medium speed color of the particles
 */
void mspeedColorSelection(ColorIndex colorCode){
	gMediumC = colorCode;
}

/**
 * @brief Set fast speed color of the particles
 */
void fspeedColorSelection(ColorIndex colorCode){
	gFastC = colorCode;
}

/**
 * @brief Set primary speed color of the particles
 */
void pspeedColorSelection(ColorIndex colorCode){
	gPrimaryC = colorCode;
}

/** 
 *	@brief Menu event handling
 */
void menuHandler(int value)
{
    switch (value)
    {
        case QUIT_MENU:
			exit(0);
            break;

        // case CLEAR_MENU:
        //     ///  do something
        //     break;

        default:
            break;

    }
}

/**
 * @brief Menu event handling for primary speed color
 */
void pspeedMenuHandler(int value)
{
    switch (value)
    {
        ///set color to WHITE
        case kWHITE:
            pspeedColorSelection(kWHITE);
            break;

		///set color to BLACK
		case kBLACK:
			pspeedColorSelection(kBLACK);
			break;

        ///set color to RED
        case kRED:
            pspeedColorSelection(kRED);
            break;

        ///set color to GREEN
        case kGREEN:
            pspeedColorSelection(kGREEN);
            break;

        ///set color to BLUE
        case kBLUE:
            pspeedColorSelection(kBLUE);
            break;

        ///set color to YELLOW
        case kYELLOW:
            pspeedColorSelection(kYELLOW);
            break;

        ///set color to PURPLE
        case kPURPLE:
            pspeedColorSelection(kPURPLE);
            break;

        ///set color to ORANGE
        case kORANGE:
            pspeedColorSelection(kORANGE);
            break;

        ///set color to PINK
        case kPINK:
            pspeedColorSelection(kPINK);
            break;

        ///set color to BROWN
        case kBROWN:
            pspeedColorSelection(kBROWN);
            break;

		case kGREY:
			pspeedColorSelection(kGREY);
			break;

		///set color to TRANSPARENT
		case kTRANSPARENT:
			pspeedColorSelection(kTRANSPARENT);
			break;

        default:
            break;

    }
}

/**
 * @brief Menu event handling for medium speed color
 */
void mspeedMenuHandler(int value)
{
    switch (value)
    {
        ///set color to WHITE
        case kWHITE:
            mspeedColorSelection(kWHITE);
            break;

		///set color to BLACK
		case kBLACK:
			mspeedColorSelection(kBLACK);
			break;

        ///set color to RED
        case kRED:
            mspeedColorSelection(kRED);
            break;

        ///set color to GREEN
        case kGREEN:
            mspeedColorSelection(kGREEN);
            break;

		///set color to BLUE
        case kBLUE:
            mspeedColorSelection(kBLUE);
            break;

        ///set color to YELLOW
        case kYELLOW:
            mspeedColorSelection(kYELLOW);
            break;

        ///set color to PURPLE
		case kPURPLE:
			mspeedColorSelection(kPURPLE);
			break;

        ///set color to ORANGE
        case kORANGE:
            mspeedColorSelection(kORANGE);
            break;

        ///set color to PINK
        case kPINK:
            mspeedColorSelection(kPINK);
            break;

        ///set color to BROWN
        case kBROWN:
            mspeedColorSelection(kBROWN);
            break;

        ///set color to GREY
        case kGREY:
            mspeedColorSelection(kGREY);
            break;

		///set color to TRANSPARENT
		case kTRANSPARENT:
			mspeedColorSelection(kTRANSPARENT);
			break;

        default:
            break;

    }
}

/**
 * @brief Menu event handling for fast speed color
 */
void fspeedMenuHandler(int value ){
	switch (value)
    {
        ///set color to WHITE
        case kWHITE:
            fspeedColorSelection(kWHITE);
            break;

		///set color to BLACK
		case kBLACK:
			fspeedColorSelection(kBLACK);
			break;

        ///set color to RED
        case kRED:
            fspeedColorSelection(kRED);
            break;

        ///set color to GREEN
        case kGREEN:
            fspeedColorSelection(kGREEN);
            break;

		///set color to BLUE
        case kBLUE:
            fspeedColorSelection(kBLUE);
            break;

        ///set color to YELLOW
        case kYELLOW:
            fspeedColorSelection(kYELLOW);
            break;

        ///set color to PURPLE
		case kPURPLE:
			fspeedColorSelection(kPURPLE);
			break;

        ///set color to ORANGE
        case kORANGE:
            fspeedColorSelection(kORANGE);
            break;

        ///set color to PINK
        case kPINK:
            fspeedColorSelection(kPINK);
            break;

        ///set color to BROWN
        case kBROWN:
            fspeedColorSelection(kBROWN);
            break;

        ///set color to GREY
        case kGREY:
            fspeedColorSelection(kGREY);
            break;

		///set color to TRANSPARENT
		case kTRANSPARENT:
			fspeedColorSelection(kTRANSPARENT);
			break;

        default:
            break;
	}
}

/**
 *  @brief This script will create a window and dreaw multiple dots and rings around the dots.
 *  @brief It is a representation of particles simulations.
 *  @brief These particles move around and repel each other and apply forces on each other.
 * 
 *  @brief User can choose the primary color of the particle,
 * 	@brief 			   the medium speed color of the particle and 
 * 	@brief 			   the fast speed color of the particle edge.
 * 
 *  @brief To exit the program, press q or right click and select exit
 * 
 *  @param -n flags for number of particles
 *  @param <integer> number of particles
 */
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
