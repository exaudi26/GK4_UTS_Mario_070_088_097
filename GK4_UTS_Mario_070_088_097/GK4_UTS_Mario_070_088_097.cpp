// pert2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<glut.h>
#include<math.h>
#include<stdlib.h>

float xp = 0.0f, yp = 0.0f, r = 4.0f, n = 1000.0f, a, x, y;

void ban1() {
	xp = 0.0f;
	yp = 3.0f;
	glColor3ub(241, 180, 47);
	glBegin(GL_POLYGON);
	a = 2 * 3.14 / n;
	for (int i = 0; i < n; i++) {
		x = xp + r * cos(i * a);
		y = yp + r * sin(i * a);
		glVertex2f(x, y);
	}
	glEnd();
}

void draw()
{
	glBegin(GL_QUADS);
	glColor3ub(0, 255, 128);
	glVertex2f(-12.0, -1.0);
	glVertex2f(12.0, -1.0);
	glVertex2f(12.0, -12.0);
	glVertex2f(-12.0, -12.0);
	glEnd();

	ban1();

	glBegin(GL_TRIANGLES);
	glColor3ub(0, 100, 0);
	glVertex2f(-5.0, 3.0);
	glVertex2f(2.0, -1.0);
	glVertex2f(-12.0, -1.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3ub(46, 139, 87);
	glVertex2f(6.0, 3.0);
	glVertex2f(12.0, -1.0);
	glVertex2f(1.0, -1.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(122, 122, 122);
	glVertex2f(1.0, -1.0);
	glVertex2f(2.0, -1.0);
	glVertex2f(-4.0, -12.0);
	glVertex2f(-8.0, -12.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(204, 51, 51);
	glVertex2f(4.0, -5.0);
	glVertex2f(9.0, -5.0);
	glVertex2f(9.0, -7.0);
	glVertex2f(4.0, -7.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3ub(288, 0, 124);
	glVertex2f(5.0, -3.0);
	glVertex2f(6.0, -5.0);
	glVertex2f(4.0, -5.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2f(5.0, -3.0);
	glVertex2f(8.0, -3.0);
	glVertex2f(9.0, -5.0);
	glVertex2f(6.0, -5.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 66, 37);
	glVertex2f(-10.0, -3.0);
	glVertex2f(-9.25, -4.0);
	glVertex2f(-9.0, -3.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 66, 37);
	glVertex2f(-8.0, -3.0);
	glVertex2f(-7.25, -4.0);
	glVertex2f(-7.0, -3.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 66, 37);
	glVertex2f(-6.5, -3.0);
	glVertex2f(-6.25, -4.0);
	glVertex2f(-5.5, -3.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(-5.0, -3.0);
	glVertex2f(-4.25, -4.0);
	glVertex2f(-4.0, -3.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 66, 37);
	glVertex2f(-10.0, -5.0);
	glVertex2f(-9.25, -6.0);
	glVertex2f(-9.0, -5.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 66, 37);
	glVertex2f(-8.0, -5.0);
	glVertex2f(-7.25, -6.0);
	glVertex2f(-7.0, -5.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 66, 37);
	glVertex2f(-6.5, -5.0);
	glVertex2f(-6.25, -6.0);
	glVertex2f(-5.5, -5.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(-5.0, -5.0);
	glVertex2f(-4.25, -6.0);
	glVertex2f(-4.0, -5.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 66, 37);
	glVertex2f(-10.0, -7.0);
	glVertex2f(-9.25, -8.0);
	glVertex2f(-9.0, -7.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 66, 37);
	glVertex2f(-8.0, -7.0);
	glVertex2f(-7.25, -8.0);
	glVertex2f(-7.0, -7.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 66, 37);
	glVertex2f(-6.5, -7.0);
	glVertex2f(-6.25, -8.0);
	glVertex2f(-5.5, -7.0);
	glEnd();

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	draw();
	glutSwapBuffers();
}

int main() {
	glutInit(&__argc, __argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("My First FreeGlut Project");
	glClearColor(135.0 / 255.0f, 206.0 / 255.0f, 235.0 / 255.0f, 1.0f);
	gluOrtho2D(-12, 12, -12, 12);

	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutMainLoop();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file