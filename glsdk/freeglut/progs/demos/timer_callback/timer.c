/* Timer (callback) demo
 *
 * Written by John Tsiombikas <nuclear@member.fsf.org>
 * Modified by Vincent Simonetti
 *
 * A modification of the timer sample, but with this
 * offering a use of the user-data callback.
 */
#include <stdio.h>
#include <GL/freeglut.h>

struct display_index_s
{
	/* color index will be advanced every time the timer expires */
	int surround_color_index;
	int center_color_index;
};
typedef struct display_index_s display_index_t;

struct timer_state_s
{
	int* color_index_ptr;
	int* timer_time_ptr;
};
typedef struct timer_state_s timer_state_t;

struct menu_state_s
{
	int* timer_time_ptr;
	int menu_id;
};
typedef struct menu_state_s menu_state_t;

void disp(void* uptr);
void timer_func(int which, void* uptr);

const float color[][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1},
	{1, 1, 0},
	{0, 1, 1},
	{1, 0, 1}
};
const int timerInts[] = {
    250,
    500,
    1000
};

void createMenuEntries(menu_state_t* menuState)
{
	int i;
    for (i = 0; i < sizeof(timerInts) / sizeof(*timerInts); i++)
    {
        char temp[10] = {'\0'};
        /* flag current value */
        if ((*menuState->timer_time_ptr) == timerInts[i])
            temp[0] = '+';
        else
            temp[0] = '-';

        sprintf(temp + 1, " %4d ms", timerInts[i]);

        glutAddMenuEntry(temp, timerInts[i]);
    }
}

void updateMenuEntries(menu_state_t* menuState)
{
	int i;
    for (i = 0; i < sizeof(timerInts) / sizeof(*timerInts); i++)
    {
        char temp[10] = { '\0' };
        /* flag current value */
        if ((*menuState->timer_time_ptr) == timerInts[i])
            temp[0] = '+';
        else
            temp[0] = '-';

        sprintf(temp + 1, " %4d ms", timerInts[i]);

        glutChangeToMenuEntry(i+1, temp, timerInts[i]);
    }
}

void MenuHandler(int timerInt, void* user_ptr)
{
	menu_state_t* menuState;
	
	if (!user_ptr)
	{
		/* In case main menu is selected somehow */
		return;
	}

	menuState = (menu_state_t*)user_ptr;

	*menuState->timer_time_ptr = timerInt;
	glutSetMenu(menuState->menu_id);
	updateMenuEntries(menuState);
}

int main(int argc, char **argv)
{
	int timerSurroundInt = 1000, timerCenterInt = 500;
	display_index_t displayIndex = { 0, 2 };
	timer_state_t surroundTimerState = { &displayIndex.surround_color_index, &timerSurroundInt };
	timer_state_t centerTimerState = { &displayIndex.center_color_index, &timerCenterInt };
	menu_state_t surroundMenuState = { &timerSurroundInt, 0 };
	menu_state_t centerMenuState = { &timerCenterInt, 0 };

	glutInit(&argc, argv);
	glutInitWindowSize(128, 128);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("timer test");

	glutDisplayFuncUcall(disp, &displayIndex);

    /* get timer started, its reset in the timer function itself */
    glutTimerFuncUcall(timerSurroundInt, timer_func, 1, &surroundTimerState);
	glutTimerFuncUcall(timerCenterInt, timer_func, 2, &centerTimerState);

    /* menus for setting timing */
	surroundMenuState.menu_id = glutCreateMenuUcall(MenuHandler, &surroundMenuState);
    createMenuEntries(&surroundMenuState);

	centerMenuState.menu_id = glutCreateMenuUcall(MenuHandler, &centerMenuState);
    createMenuEntries(&centerMenuState);

    glutCreateMenuUcall(MenuHandler, NULL); /* doesn't matter, no clickable entries in this menu */
    glutAddSubMenu("Center", centerMenuState.menu_id);
    glutAddSubMenu("Surround", surroundMenuState.menu_id);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

void disp(void* user_ptr)
{
	const display_index_t* displayIndex;
	int cidx, pcidx;

	displayIndex = (display_index_t*)user_ptr;
	
	cidx = displayIndex->surround_color_index;
	glClearColor(color[cidx][0], color[cidx][1], color[cidx][2], 1);
	glClear(GL_COLOR_BUFFER_BIT);

	pcidx = displayIndex->center_color_index;
    glPointSize(10.f);
    glColor3f(color[pcidx][0], color[pcidx][1], color[pcidx][2]);
    glBegin(GL_POINTS);
        glVertex2i(0,0);
    glEnd();

	glutSwapBuffers();
}

void timer_func(int which, void* user_ptr)
{
	const timer_state_t* timerState;
	
	timerState = (timer_state_t*)user_ptr;

	/* advance the color index and trigger a redisplay */
	*timerState->color_index_ptr = (*timerState->color_index_ptr + 1) % (sizeof color / sizeof *color);
    
	glutPostRedisplay();

	/* (re)set the timer callback and ask glut to call it in x ms */
    glutTimerFuncUcall(*timerState->timer_time_ptr, timer_func, which, user_ptr);
}
