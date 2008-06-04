
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h> 
#include "Renderer.h"
#include "InputManager.h"
#include "GameApp.h"
#include <time.h>

//#define TRACK_MEMORY

#ifdef TRACK_MEMORY
#ifdef _DEBUG
#include <vld.h>
#endif
#endif



//--------------------------------------------------
/**
* Globals
*
**/
GameApp* g_pGame = 0;

//--------------------------------------------------
/**
* Initializes everything
*
**/
bool Init()
{
	g_pGame = GameApp::GetInstance();
	if (!g_pGame->Init())
	{
		return false;
	}

	return true;
}

//--------------------------------------------------
/**
* Calls the renderer to render scene
*
**/
void Render()
{
	if (g_pGame)
		g_pGame->GetRenderer()->Render();

	
}

//--------------------------------------------------
/**
* Calls the renderer to resize window
*
**/
void Resize(int w, int h)
{
	if (g_pGame)
		g_pGame->GetRenderer()->Resize(w, h);
	}


//--------------------------------------------------
/**
* Frees memory
*
**/
void Shutdown()
{
	GameApp::Destroy();
	g_pGame = 0;

}

//--------------------------------------------------
/**
* Handles key down
*
**/
void KeyDown(unsigned char key, int x, int y) {

	if (g_pGame)
		g_pGame->GetInputManager()->KeyDown(key);
}

//--------------------------------------------------
/**
* Handles key up
*
**/
void KeyUp(unsigned char key, int x, int y) {

	if (g_pGame)
		g_pGame->GetInputManager()->KeyUp(key);
}

//--------------------------------------------------
/**
* Handles passive mouse motion
*
**/

void processMousePassiveMotion(int x, int y) {

	if (g_pGame)
		g_pGame->GetInputManager()->MousePassiveMotion(x, y);
}

//--------------------------------------------------
/**
* Idle Func
*
**/
void Idle()
{
	if (g_pGame)
	{
		if (!g_pGame->Update())
		{
			exit(0);
		}

		glutPostRedisplay();
	}
}

//--------------------------------------------------
/**
* Main function
*
**/
void main(int argc, char **argv) {

	srand(unsigned int (time(0)));
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("Geometry Wars Reloaded");

	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutPassiveMotionFunc(processMousePassiveMotion);
	glutDisplayFunc(Render);

	// Here is our new entry in the main function 
	glutReshapeFunc(Resize);

	if (!Init())
	{
		return;
	}

	atexit(Shutdown);

	glutMainLoop();

	Shutdown();
}