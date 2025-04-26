/* Joystick demo
 * Written by John Tsiombikas <nuclear@member.fsf.org>
 * Press escape or q to exit.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <GL/freeglut.h>

#ifndef M_PI
#define M_PI	3.14159265358979323846
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4305 4244)
#endif

void display(void);
void rect(float x0, float y0, float x1, float y1);
void text(float x, float y, const char *fmt, ...);
void widget(float xsz, float ysz, float xpos, float ypos);
void button(float sz, float state);
void reshape(int x, int y);
void keyboard(unsigned char key, int x, int y);
void joystick(unsigned int bmask, int x, int y, int z);

int win_width, win_height;
int joy[3];
unsigned int joy_bmask;
int num_buttons, bhist;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Joystick demo");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutJoystickFunc(joystick, 25);

	if(!glutGet(GLUT_HAS_JOYSTICK)) {
		fprintf(stderr, "no joystick detected\n");
		return 1;
	}
	printf("Joystick axes: %d\n", glutGet(GLUT_JOYSTICK_AXES));
	num_buttons = glutGet(GLUT_JOYSTICK_BUTTONS);
	printf("Joystick buttons: %d\n", num_buttons);

	glutMainLoop();
}

#define WSZ		0.8
#define RAD		(WSZ / 8)
#define FRM		0.0075
#define MAX_BSZ	(WSZ / 9)

void display(void)
{
	float dmax = WSZ * 0.5f - RAD;
	float jx, jy, jz, cury, bsz;
	int i, num;

	jx = joy[0] / 1000.0f;
	jy = joy[1] / 1000.0f;
	jz = joy[2] / 1000.0f;

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-WSZ / 2, 0, 0);
	widget(WSZ, WSZ, jx * dmax, -jy * dmax);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(WSZ / 2, 0, 0);
	widget(RAD * 2, WSZ, 0, -jz * dmax);
	glPopMatrix();

	if(num_buttons > 0) {
		num = num_buttons;
	} else {
		bhist |= joy_bmask;
		num = 0;
		while(num < 32 && bhist >> num) {
			num++;
		}
	}

	if(num) {
		if(num > 32) num = 32;
		bsz = 2.0 / (num * 1.4);

		if(bsz > MAX_BSZ) bsz = MAX_BSZ;

		glPushMatrix();
		glTranslatef(-bsz * 1.4 * (num - 1) / 2, 0.7, 0);
		for(i=0; i<num; i++) {
			button(bsz, joy_bmask & (1 << i));
			glTranslatef(bsz * 1.4, 0, 0);
		}
		glPopMatrix();
	}

	glColor3f(0, 1, 0);
	cury = -2 * WSZ / 3;
	text(-WSZ * 0.75, cury, "X: %d", joy[0]);
	cury -= 0.08;
	text(-WSZ * 0.75, cury, "Y: %d", joy[1]);
	cury -= 0.08;
	text(-WSZ * 0.75, cury, "Z: %d", joy[2]);

	glutSwapBuffers();
}

void rect(float x0, float y0, float x1, float y1)
{
	glVertex2f(x0, y0);
	glVertex2f(x1, y0);
	glVertex2f(x1, y1);
	glVertex2f(x0, y1);
}

void text(float x, float y, const char *fmt, ...)
{
	va_list ap;
	char buf[256], *s;

	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	va_end(ap);

	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos2f(x, y);

	s = buf;
	while(*s) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *s++);
	}

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void widget(float xsz, float ysz, float xpos, float ypos)
{
	int i;
	float x, y, theta;

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	rect(-xsz / 2 - FRM, -ysz / 2 - FRM, xsz / 2 + FRM, ysz / 2 + FRM);
	glColor3f(0.1, 0.1, 0.1);
	rect(-xsz / 2, -ysz / 2, xsz / 2, ysz / 2);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0);
	glVertex2f(xpos, ypos);
	for(i=0; i<20; i++) {
		theta = M_PI * 2 * i / 19.0;
		x = cos(theta) * RAD;
		y = sin(theta) * RAD;
		glVertex2f(xpos + x, ypos + y);
	}
	glEnd();
}

void button(float sz, float state)
{
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	rect(-sz / 2 - FRM, -sz / 2 - FRM, sz / 2 + FRM, sz / 2 + FRM);

	glColor3f(state ? 1 : 0.2, 0.2, 0.2);
	rect(-sz / 2, -sz / 2, sz / 2, sz / 2);
	glEnd();
}

void reshape(int x, int y)
{
	float aspect = (float)x / y;

	win_width = x;
	win_height = y;

	glViewport(0, 0, x, y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(1.0 / aspect, 1, 1);
}

void keyboard(unsigned char key, int x, int y)
{
	if(key == 27 || key == 'q') {
		exit(0);
	}
}

void joystick(unsigned int bmask, int x, int y, int z)
{
	joy[0] = x;
	joy[1] = y;
	joy[2] = z;
	joy_bmask = bmask;

	glutPostRedisplay();
}
