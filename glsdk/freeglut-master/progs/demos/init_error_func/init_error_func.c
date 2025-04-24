/*
 * ------------------------------------------
 * user_error_handler.c
 *
 * This is a sample program showing a basic
 * user defined error handlers with FreeGLUT
 * ------------------------------------------
 */

#include <GL/freeglut.h>

/*
 * ------------------------------------------
 * Declare our own Error handler for FreeGLUT
 * ------------------------------------------
 */

/* This declares the vprintf() routine */
#include <stdio.h>

/* This declares the va_list type */
#include <stdarg.h>

/* The new handler looks like a vprintf prototype */
void myError (const char *fmt, va_list ap)
{
    fprintf(stderr, "myError: Entering user defined error handler\n");

    /* print warning message */
    fprintf(stderr, "myError:");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");

    /* deInitialize the freeglut state */
    fprintf(stderr, "myError: Calling glutExit()\n");
    glutExit();

    /* terminate error handler appropriately */
    fprintf(stderr, "myError: Exit-ing handler routine\n");

    exit(1);
}

/*
 * ------------------------------------------
 * Just enough code to create the error to
 * demonstrate the user defined handler
 * ------------------------------------------
 */
int main(int argc, char** argv)
{
    glutInitErrorFunc(&myError);
    glutCreateWindow ("error test");  /* This is an error! */
    glutInit(&argc, argv);            /* Should be called
                                         after glutInit() */
    glutMainLoop();
    return 0;
}
