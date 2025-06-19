
#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Game.h"

using namespace std;

/////////////////////////CONSTANTES/////////////////////////

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int WINDOW_POSITION_X = 300;
const int WINDOW_POSITION_Y = 400;
const char TITLE[] = "Locura en miniatura";
bool fullScreenMode = false;
const GLclampf RED = 0.1;
const GLclampf GREEN = 0.1;
const GLclampf BLUE = 0.1;
const GLclampf ALPHA = 1.0;

/////////////////////////FUNCIONES AUXILIARES/////////////////////////

void writeLine(string text)
{
	cout << text << endl;
}

/////////////////////////USANDO GAME/////////////////////////

Game game;

/////////////////////////////////////////////////////////////

/////////////////////////FUNCIONES OPENGL/////////////////////////

void initGraphics()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	GLfloat lightPos[] = { 2.0f, 25.0f, 2.0f, 1.0f };  // Posición de la luz
	GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

	glClearColor(RED, GREEN, BLUE, ALPHA);
	game.Init();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	game.Render();

	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
	if (height == 0) height = 1;
	GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, aspectRatio, 1.0f, 2000.0f);
	glMatrixMode(GL_MODELVIEW);
}

void idle()
{
	game.Update();
	glutPostRedisplay();
}

void keyPressed(unsigned char key, int px, int py)
{
	game.ProcessKeyPressed(key, px, py);
	glutPostRedisplay();
}

void mouseMoved(int x, int y)
{
	game.ProcessMouseMovement(x, y);
	glutPostRedisplay();
}

void mouseClicked(int button, int state, int x, int y)
{
	game.ProcessMouseClick(button, state, x, y);
	glutPostRedisplay();
}

void specialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F11:
		fullScreenMode = !fullScreenMode;
		if (fullScreenMode)
		{
			glutFullScreen();
		}
		else
		{
			glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
			glutPositionWindow(WINDOW_POSITION_X, WINDOW_POSITION_Y);
		}
		break;
	}
}
/////////////////////////NUEVAS FUNCIONES/////////////////////////

void keyReleased(unsigned char key, int x, int y) {
	game.ProcessKeyReleased(key, x, y); 
	glutPostRedisplay();
}

/////////////////////////MAIN/////////////////////////

int main(int argc, char** argv)
{
	writeLine("Hello world con OpenGL");
	writeLine("Generando ventana...");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow(TITLE);
	writeLine("Registrando funciones de tratamiento de eventos");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialKey);
	glutPassiveMotionFunc(mouseMoved);
	glutMouseFunc(mouseClicked);
	glutIdleFunc(idle);

	//AÑADIDO DESPUES
	
	glutMotionFunc(mouseMoved);
	glutKeyboardUpFunc(keyReleased); 
	//DETECTAR CUANDO UNA TECLA NO ESTA PRESIONADA
	//glutSetCursor(GLUT_CURSOR_NONE); //HACER EL CURSOR INVISIBLE
	glutSetCursor(GLUT_CURSOR_INFO); //HACER EL CURSOR INVISIBLE
	glEnable(GL_NORMALIZE);

	//

	writeLine("Iniciando graficos");
	initGraphics();

	writeLine("Iniciando bucle infinito");
	writeLine("Pulse F11 para activar/desactivar el modo pantalla completa");
	glutMainLoop();
}

