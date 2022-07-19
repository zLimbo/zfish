//
// main.cpp
// SolorSystem
//

#include <GL/glut.h>
#include "SolarSystem.hpp"

#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

SolarSystem solarsystem;

void onDisplay() {
	solarsystem.onDisplay();
}

void onUpdate() {
	solarsystem.onUpdate();
}

void onKeyboard(unsigned char key, int x, int y) {
	solarsystem.onKeyboard(key, x, y);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//window-position
	glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
	//window-size 
	glutInitWindowSize(WIDTH, HEIGHT);
	//window-create
	glutCreateWindow("SolarSystem at Limbo");
	//window-display
	glutDisplayFunc(onDisplay);
	//refresh-free
	glutIdleFunc(onUpdate);
	//keyboard
	glutKeyboardFunc(onKeyboard);
	//loop
	glutMainLoop();

	return 0;
}
