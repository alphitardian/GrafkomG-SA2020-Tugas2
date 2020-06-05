#include <iostream>
#include <math.h>
#include <GL/freeglut.h>
#define phi 3.14
using namespace std;

float length = 0.0;
float deltaMovement = 0.0;
bool isMove = false;
bool orbitLine = false;

void drawPlanetObject(float radius, float distance, float delta) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float rad = (2 * phi) * i / 360;
		glVertex2f(cos(rad) * radius + (cos(delta) * distance + 50), sin(rad) * radius + (sin(delta) * distance + 50));
		glColor3f(0.0, 0.0, 0.0);
	}
	glEnd();
}

void drawSatelliteObject(float radius, float distanceSatellite, float distancePlanet, float deltaPlanet, float deltaSatellite) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float rad = (2 * phi) * i / 360;
		glVertex2f(cos(rad) * radius + (cos(deltaSatellite) * distanceSatellite + (cos(deltaPlanet) * distancePlanet + 50)), 
			sin(rad) * radius + (sin(deltaSatellite) * distanceSatellite + (sin(deltaPlanet) * distancePlanet + 50)));
		glColor3f(0.0, 0.0, 0.0);
	}
	glEnd();
}

void drawPlanetTrack(float radius) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		float rad = (2 * phi) * i / 360;
		glVertex2f(cos(rad) * radius + 50, sin(rad) * radius + 50);
	}
	glEnd();
}

void drawSatelliteTrack(float radius, float deltaPlanet, float distancePlanet) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		float rad = (2 * phi) * i / 360;
		glVertex2f(cos(rad) * radius + (cos(deltaPlanet) * distancePlanet + 50), sin(rad) * radius + (sin(deltaPlanet) * distancePlanet + 50));
	}
	glEnd();
}

void connectingLinePlanet(float distance, float delta) {
	glVertex2f((cos(delta) * distance + 50), (sin(delta) * distance + 50));
}

void connectingLineSatelliteCenter(float distancePlanet, float deltaPlanet) {
	glVertex2f(cos(deltaPlanet) * distancePlanet + 50, sin(deltaPlanet) * distancePlanet + 50);
}

void connectingLineSatellite(float distancePlanet, float distanceSatellite, float deltaPlanet, float deltaSatellite) {
	glVertex2f(cos(deltaSatellite) * distanceSatellite + (cos(deltaPlanet) * distancePlanet + 50), 
		sin(deltaSatellite) * distanceSatellite + (sin(deltaPlanet) * distancePlanet + 50));
}

void drawOrbitLine() {
	glColor3f(0.3, 0.3, 0.3);
	/* Orbit Line Planet & Stars - Start */
	glBegin(GL_LINES);
	glVertex2f(50, 50); connectingLinePlanet(15, length * 2.5);
	glVertex2f(50, 50); connectingLinePlanet(25, length * 2);
	glVertex2f(50, 50); connectingLinePlanet(35, length * 1.5);
	glVertex2f(50, 50); connectingLinePlanet(45, length);
	glEnd();
	/* Orbit Line Planet & Stars - End */

	/* Orbit Moon & Planet - Start */
	glBegin(GL_LINES);
	connectingLineSatelliteCenter(35, length * 1.5); connectingLineSatellite(35, 4, length * 1.5, length * 5);
	connectingLineSatelliteCenter(45, length); connectingLineSatellite(45, 3, length, length * 4.5);
	connectingLineSatelliteCenter(45, length); connectingLineSatellite(45, 5, length, length * 4);
	glEnd();
	/* Orbit Moon & Planet - End */

	/* Planet & Satellite Track Orbit - Start */
	drawPlanetTrack(15);
	drawPlanetTrack(25);
	drawPlanetTrack(35);
	drawPlanetTrack(45);
	drawSatelliteTrack(4, length * 1.5, 35);
	drawSatelliteTrack(3, length, 45);
	drawSatelliteTrack(5, length, 45);
	/* Planet & Satellite Track Orbit - End */
}

void keyFun(unsigned char key, int x, int y) {
	cout << key << " key pressed" << endl;

	if (isMove == false) { 
		deltaMovement = 0.025; 
		isMove = true; 
	}
	else if (isMove == true) { 
		deltaMovement = 0; 
		isMove = false; 
	}

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	/* Stars & Planet Object - Start*/
	// Sun
	glColor3f(1.0, 1.0, 0.5); drawPlanetObject(7, 0, 0);

	// Mercury
	glColor3f(1.0, 0.0, 0.0); drawPlanetObject(1, 15, length * 2.5);

	// Venus
	glColor3f(1.0, 0.0, 1.0); drawPlanetObject(1.5, 25, length * 2);

	// Earth
	glColor3f(0.0, 0.0, 1.0); drawPlanetObject(2.5, 35, length * 1.5);

	// Mars
	glColor3f(0.8, 0.0, 0.0); drawPlanetObject(1.75, 45, length);
	/* Stars & Planet Object - End*/

	/* Satellite Object - Start */
	// Earth Satellite
	glColor3f(1.0, 1.0, 1.0); drawSatelliteObject(0.75, 4, 35, length * 1.5, length * 5);

	// Mars Satellite
	glColor3f(0.8, 0.0, 0.8); drawSatelliteObject(0.5, 3, 45, length, length * 4.5);
	glColor3f(0.8, 0.0, 0.8); drawSatelliteObject(0.75, 5, 45, length, length * 4);
	/* Satellite Object - Done */

	drawOrbitLine();
	
	glFlush();
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 30, timer, 0);

	length -= deltaMovement;
}

void myInit() {
	glClearColor(0.1, 0.1, 0.1, 1.0);
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
	glutKeyboardFunc(keyFun);

	myInit();
	glutMainLoop();

	return 0;
}