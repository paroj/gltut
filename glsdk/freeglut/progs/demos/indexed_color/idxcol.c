/* Indexed color mode demo
 * Written by John Tsiombikas <nuclear@member.fsf.org>
 *
 * Demonstrates how to create an indexed color OpenGL context, manipulate the
 * colormap, and do lighting in indexed color mode.
 *
 * Obviously none of this will work if your OpenGL implementation and/or
 * window system does not support indexed color.
 */
#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

void display(void);
void reshape(int x, int y);
void keyb(unsigned char key, int x, int y);
void mouse(int bn, int st, int x, int y);
void motion(int x, int y);

float cam_theta, cam_phi, cam_dist = 6;

int prev_x, prev_y;
int bnstate[8];

int sphere, torus;
int redramp[3], blueramp[3];


int main(int argc, char **argv)
{
	int i, ncolors, rampsz, maxdif;
	float x;

	glutInit(&argc, argv);
	/* request an indexed color visual, this will fail on most modern systems */
	glutInitDisplayMode(GLUT_INDEX | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("FreeGLUT indexed color demo");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyb);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	ncolors = glutGet(GLUT_WINDOW_COLORMAP_SIZE);
	printf("Colormap size: %d\n", ncolors);

	rampsz = ncolors / 2;
	maxdif = (int)(rampsz * 0.75f);

	/* prepare a palette with two color ramps for a red and a blue object */
	for(i=0; i<rampsz; i++) {
		if(i < maxdif) {
			x = (float)i / (maxdif - 1);
			glutSetColor(i, x, 0, 0);
			glutSetColor(i + rampsz, 0, 0, x);
		} else {
			x = (float)(i - maxdif) / (rampsz - maxdif - 1);
			glutSetColor(i, 1, x, x);
			glutSetColor(i + rampsz, x, x, 1);
		}
	}
	/* prepare the indexed color lighting descriptors needed by OpenGL to
	 * compute lighting in indexed color mode.
	 */
	redramp[0] = 0;				/* unlit color index*/
	redramp[1] = maxdif - 1;	/* maximum diffuse color index*/
	redramp[2] = rampsz - 1;	/* maximum specularity color index */
	blueramp[0] = rampsz;		/* ... and same for the blue ramp ... */
	blueramp[1] = rampsz + maxdif - 1;
	blueramp[2] = rampsz * 2 - 1;

	/* set the specular exponent for all objects once */
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 40);


	sphere = glGenLists(1);
	glNewList(sphere, GL_COMPILE);
	glutSolidSphere(1, 30, 15);
	glEndList();

	torus = glGenLists(1);
	glNewList(torus, GL_COMPILE);
	glutSolidTorus(0.35, 0.9, 20, 40);
	glEndList();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutMainLoop();
	return 0;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -cam_dist);
	glRotatef(cam_phi, 1, 0, 0);
	glRotatef(cam_theta, 0, 1, 0);

	/* set up the red object's lighting indices */
	glMaterialiv(GL_FRONT_AND_BACK, GL_COLOR_INDEXES, redramp);

	glPushMatrix();
	glTranslatef(-1.5, 0, 0);
	glCallList(sphere);
	glPopMatrix();

	/* setup the blue object's lighting indices */
	glMaterialiv(GL_FRONT_AND_BACK, GL_COLOR_INDEXES, blueramp);

	glPushMatrix();
	glTranslatef(1.5, 0, 0);
	glRotatef(90, 1, 0, 0);
	glCallList(torus);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int x, int y)
{
	glViewport(0, 0, x, y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (float)x / y, 0.5, 500.0);
}

void keyb(unsigned char key, int x, int y)
{
	switch(key) {
	case 27:
		exit(0);
	}
}

void mouse(int bn, int st, int x, int y)
{
	bnstate[bn - GLUT_LEFT_BUTTON] = st == GLUT_DOWN;
	prev_x = x;
	prev_y = y;
}

void motion(int x, int y)
{
	int dx, dy;

	dx = x - prev_x;
	dy = y - prev_y;
	prev_x = x;
	prev_y = y;

	if(!(dx | dy)) return;

	if(bnstate[0]) {
		cam_theta += dx * 0.5f;
		cam_phi += dy * 0.5f;
		if(cam_phi < -90) cam_phi = -90;
		if(cam_phi > 90) cam_phi = 90;
		glutPostRedisplay();
	}
	if(bnstate[2]) {
		cam_dist += dy * 0.1f;
		if(cam_dist < 0) cam_dist = 0;
		glutPostRedisplay();
	}
}
