#include <iostream>
#include <math.h>
#include <GL/freeglut.h>
using namespace std;

float length = 0.0;

void drawCircle(int radius) {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 720; i++) {
		glVertex2f(sin(i) * radius + 50, cos(i) * radius + 50);
		glRotatef(45.0 + i, 0.0, 0.0, 0.0);
	}
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(50.0, 50.0);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(sin(length * 2) * 10 + 50, cos(length * 2) * 10 + 50);

	glVertex2f(sin(length) * 30 + 50, cos(length) * 30 + 50);
	glEnd();

	glBegin(GL_POINTS);
	glVertex2f(sin(length * 3) * 10 + (sin(length) * 30 + 50), cos(length * 3) * 10 + (cos(length) * 30 + 50));
	glEnd();

	// Orbit Planet & Stars
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(50, 50); glVertex2f(sin(length * 2) * 10 + 50, cos(length * 2) * 10 + 50);
	glVertex2f(50, 50); glVertex2f(sin(length) * 30 + 50, cos(length) * 30 + 50);
	glVertex2f(sin(length) * 30 + 50, cos(length) * 30 + 50); glVertex2f(sin(length * 3) * 10 + (sin(length) * 30 + 50), cos(length * 3) * 10 + (cos(length) * 30 + 50));
	glEnd();


	glFlush();
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 30, timer, 0);

	length += 0.05;
}

void myInit() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glPointSize(10);
	glLineWidth(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Ardian Pramudya Alphita - 672018150");

	glutTimerFunc(0, timer, 0);
	glutDisplayFunc(display);

	myInit();
	glutMainLoop();

	return 0;
}