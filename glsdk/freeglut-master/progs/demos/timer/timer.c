/* Timer demo
 *
 * Written by John Tsiombikas <nuclear@member.fsf.org>
 *
 * Demonstrate the use of glutTimerFunc, by changing the color of the
 * framebuffer every (approximately) 1 sec.
 */
#include <stdio.h>
#include <GL/glut.h>

void disp(void);
void timer_func(int unused);

/* color index will be advanced every time the timer expires */
int cidx = 0;
int pcidx = 2;
float color[][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1},
	{1, 1, 0},
	{0, 1, 1},
	{1, 0, 1}
};
int timerInts[] = {
    250,
    500,
    1000
};
int timerSurroundInt = 1000, timerCenterInt = 1000;

/* menu IDs, creation/update funcs and callback */
int menuID, subMenuSurround, subMenuCenter;

void createMenuEntries(int which)
{
	int i;
    for (i = 0; i < sizeof(timerInts) / sizeof(*timerInts); i++)
    {
        char temp[10] = {'\0'};
        /* flag current value */
        if ((which == 1 ? timerSurroundInt : timerCenterInt) == timerInts[i])
            temp[0] = '+';
        else
            temp[0] = '-';

        sprintf(temp + 1, " %4d ms", timerInts[i]);

        glutAddMenuEntry(temp, timerInts[i]);
    }
}

void updateMenuEntries(int which)
{
	int i;
    for (i = 0; i < sizeof(timerInts) / sizeof(*timerInts); i++)
    {
        char temp[10] = { '\0' };
        /* flag current value */
        if ((which == 1 ? timerSurroundInt : timerCenterInt) == timerInts[i])
            temp[0] = '+';
        else
            temp[0] = '-';

        sprintf(temp + 1, " %4d ms", timerInts[i]);

        glutChangeToMenuEntry(i+1, temp, timerInts[i]);
    }
}

void MenuSurround(int timerInt)
{
    timerSurroundInt = timerInt;
    glutSetMenu(subMenuSurround);
    updateMenuEntries(1);
}
void MenuCenter(int timerInt)
{
    timerCenterInt = timerInt;
    glutSetMenu(subMenuCenter);
    updateMenuEntries(2);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(128, 128);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("timer test");

	glutDisplayFunc(disp);

    /* get timer started, its reset in the timer function itself */
    glutTimerFunc(1000, timer_func, 1);
    glutTimerFunc(500, timer_func, 2);

    /* menus for setting timing */
    subMenuSurround = glutCreateMenu(MenuSurround);
    createMenuEntries(1);

    subMenuCenter = glutCreateMenu(MenuCenter);
    createMenuEntries(2);

    menuID = glutCreateMenu(MenuSurround);  /* doesn't matter, no clickable entries in this menu */
    glutAddSubMenu("Center", subMenuCenter);
    glutAddSubMenu("Surround", subMenuSurround);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

void disp(void)
{
	glClearColor(color[cidx][0], color[cidx][1], color[cidx][2], 1);
	glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(10.f);
    glColor3f(color[pcidx][0], color[pcidx][1], color[pcidx][2]);
    glBegin(GL_POINTS);
        glVertex2i(0,0);
    glEnd();

	glutSwapBuffers();
}

void timer_func(int which)
{
	/* advance the color index and trigger a redisplay */
    switch (which)
    {
    case 1:
        cidx = (cidx + 1) % (sizeof color / sizeof *color);
        break;
    case 2:
        pcidx = (pcidx + 1) % (sizeof color / sizeof *color);
        break;
    }
    
	glutPostRedisplay();

	/* (re)set the timer callback and ask glut to call it in x ms */
    glutTimerFunc(which == 1 ? timerSurroundInt:timerCenterInt, timer_func, which);
}
