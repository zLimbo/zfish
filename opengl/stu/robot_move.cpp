#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>

#define WINDOW_WIDTH 600
#define WINDOW_HIGHT 500

int D = 0;
GLfloat Left = 0.15, Right = -0.15, Top = -0.25, Bottom = -1.0;
GLfloat Move = 0.001;

void myInit() {
	Left = 0.15, Right = -0.15, Top = -0.25, Bottom = -1.0;
	D = 0;
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void robotDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	// ͷ
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(-0.05, -0.25);
		glVertex2f(-0.05, -0.35);
		glVertex2f(0.05, -0.35);
		glVertex2f(0.05, -0.25);
	glEnd();
	// ��
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(-0.025, -0.35);
		glVertex2f(-0.025, -0.4);
		glVertex2f(0.025, -0.4);
		glVertex2f(0.025, -0.35);
	glEnd();
	// ����
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2f(-0.1, -0.4);
		glVertex2f(-0.1, -0.7);
		glVertex2f(0.1, -0.7);
		glVertex2f(0.1, -0.4);
	glEnd();
	// �ֱ�
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(-0.15, -0.45);
		glVertex2f(-0.15, -0.7);
		glVertex2f(-0.1, -0.7);
		glVertex2f(-0.1, -0.45);
		
		glVertex2f(0.15, -0.45);
		glVertex2f(0.15, -0.7);
		glVertex2f(0.1, -0.7);
		glVertex2f(0.1, -0.45);
	glEnd();
	// ��
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(-0.075, -0.7);
		glVertex2f(-0.075, -0.9);
		glVertex2f(-0.025, -0.9);
		glVertex2f(-0.025, -0.7);

		glVertex2f(0.075, -0.7);
		glVertex2f(0.075, -0.9);
		glVertex2f(0.025, -0.9);
		glVertex2f(0.025, -0.7);
	glEnd();
	// ��
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2f(-0.085, -0.9);
		glVertex2f(-0.085, -1.0);
		glVertex2f(-0.015, -1.0);
		glVertex2f(-0.015, -0.9);
		
		glVertex2f(0.085, -0.9);
		glVertex2f(0.085, -1.0);
		glVertex2f(0.015, -1.0);
		glVertex2f(0.015, -0.9);
	glEnd();

	glutSwapBuffers();
}

void moveKey(unsigned char key, int x, int y) {
	if ((key == 'd' || key == 'D')) {
		D = 1;
	}
	if (key == 'a' || key == 'A') {
		D = 2;
	}
	if (key == 'w' || key == 'W') {
		D = 3;
	}
	if (key == 's' || key == 'S') {
		D = 4;
	}
	if (key == 'e' || key == 'E') {
		myInit();
		glLoadIdentity();
		D = 5;
	}
	if (key == 'q' || key == 'Q') {
		myInit();
		glLoadIdentity();
		D = 6;
	}
	if (key == 'r' || key == 'R') {
		myInit();
		glLoadIdentity();
		D = 7;
	}
	if (key == ' ') {
		myInit();
		glLoadIdentity();
	}

	glutPostRedisplay();
}

void idle() {
	if (D == 1) {
		if (Left >= 1.00) {
			D = 2;
			return;
		}
		Left += Move;
		Right += Move;
		glTranslatef(Move, 0.0, 0.0);
	}
	if (D == 2) {
		if (Right <= -1.00) {
			D = 1;
			return;
		}
		Right -= Move;
		Left -= Move;
		glTranslatef(-Move, 0.0, 0.0);
	}
	if (D == 3) {
		if (Top >= 1.00) {
			D = 4;
			return;
		}
		Top += Move;
		Bottom += Move;
		glTranslatef(0.0, Move, 0.0);
	}
	if (D == 4) {
		if (Bottom <= -1.00) {
			D = 3;
			return;
		}
		Top -= Move;
		Bottom -= Move;
		glTranslatef(0.0, -Move, 0.0);
	}
	if (D == 5) {
		glRotatef(0.1, 0.0, -1.0, 0.0);
	}
	if (D == 6) {
		glRotatef(0.1, -1.0, 0.0, 0.0);
	}
	if (D == 7) {
		glRotatef(0.1, 0.0, 0.0, -1.0);
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HIGHT);
	glutCreateWindow("Robot");

	glutDisplayFunc(robotDisplay);
	glutKeyboardFunc(moveKey);
	glutIdleFunc(idle);
	myInit();
	glutMainLoop();

	return 0;
}