#include "Graphics.h"
int main(int argc, char* argv[])
{
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("intergalactic puberty");
	glutFullScreen();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(process_keys);
	glutMouseFunc(process_click);
	test();
	glutMainLoop();
}
