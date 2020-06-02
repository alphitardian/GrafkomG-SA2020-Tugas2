#include <iostream>
#include <GL/freeglut.h>
using namespace std;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_QUADS);
	glVertex2f(10.0, 10.0);
	glVertex2f(10.0, 50.0);
	glVertex2f(50.0, 50.0);
	glVertex2f(50.0, 10.0);
	glEnd();

	glFlush();
}

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPointSize(5);
	glLineWidth(2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Ardian Pramudya Alphita - 672018150");
	glutDisplayFunc(display);

	myInit();
	glutMainLoop();

	return 0;
}