/*
* smooth_opengl3.c, based on smooth.c, which is (c) by SGI, see below.
* This program demonstrates smooth shading in a way which is fully
* OpenGL-3.1-compliant.
* A smooth shaded polygon is drawn in a 2-D projection.
*/

/*
* Original copyright notice from smooth.c:
*
* License Applicability. Except to the extent portions of this file are
* made subject to an alternative license as permitted in the SGI Free
* Software License B, Version 1.1 (the "License"), the contents of this
* file are subject only to the provisions of the License. You may not use
* this file except in compliance with the License. You may obtain a copy
* of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
* Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
* 
* http://oss.sgi.com/projects/FreeB
* 
* Note that, as provided in the License, the Software is distributed on an
* "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
* DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
* CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
* PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
* 
* Original Code. The Original Code is: OpenGL Sample Implementation,
* Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
* Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
* Copyright in any portions created by third parties is as indicated
* elsewhere herein. All Rights Reserved.
* 
* Additional Notice Provisions: The application programming interfaces
* established by SGI in conjunction with the Original Code are The
* OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
* April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
* 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
* Window System(R) (Version 1.3), released October 19, 1998. This software
* was created using the OpenGL(R) version 1.2.1 Sample Implementation
* published by SGI, but has not been independently verified as being
* compliant with the OpenGL(R) version 1.2.1 Specification.
*
*/

#include <glloader/gl_3_2_comp.h>
#include <glloader/wgl_exts.h>
#include <glloader/gle.h>
#include <GL/freeglut.h>


void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL);
	/* add command line argument "classic" for a pre-3.x context */
	if ((argc != 2) || (strcmp (argv[1], "classic") != 0)) {
		glutInitContextVersion (3, 2);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (300, 200);
	glutCreateWindow (argv[0]);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	gleLoadFunctions();
	init();

	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
