#include <stdlib.h> // for exit
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/tga.h>

#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h>  
#include <OpenGL/glu.h>  
#else
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#endif

int window;

float mercury_day = 0.0;
float venus_day = 0.0;
float earth_hour = 0.0;
float earth_day = 0.0;
float mars_day = 0.0;
float jupiter_day = 0.0;
float saturn_day = 0.0;
float uranus_day = 0.0;
float neptune_day = 0.0;
float inc = 0.10;
GLuint texture;

void resize(int width, int height)
{
	// prevent division by zero
	if (height == 0) { height = 1; }

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutDestroyWindow(window);
		exit(0);
		break;
	}
}

static void specialKeyPressed(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		inc *= 1.5;
		break;
	case GLUT_KEY_DOWN:
		inc *= 0.75;
		break;
	}
}

void display()
{
	/*
	* Distances to sun in AE (1 AE = 150.00.000 km),
	* and for this project used values (1 AE = 10.0f):
	* 
	* Mercury -	0,39	>> 3,90f
	* Venus -	0,72	>> 7,20f
	* Earth -	1,00	>> 10,0f
	* Mars -	1,52	>> 15,2f
	* Jupiter -	5,20	>> 52,0f
	* Saturn -	9,54	>> 95,4f
	* Uranus -	19,18	>> 191,8f
	* Neptune -	30,06	>> 300,6f
	==================================================
	* Sizes of planets (= diameter) in km, and for this 
	* project used values (1 AE = 10.0f):
	*
	* Sun -	1.390.000 km	>> 0,0927f
	* Mercury -	4.900 km	>> 0,0003f
	* Venus -	12.100 km	>> 0,0008f
	* Earth -	12.800 km	>> 0,0009f
	* Moon -	3.475 km	>> 0,0002f
	* Mars -	6.800 km	>> 0,0005f
	* Jupiter -	143.000 km	>> 0,0095f
	* Saturn -	120.500 km	>> 0,0080f
	* Uranus -	51.100 km	>> 0,0034f
	* Neptune -	49.500 km	>> 0,0033f
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/* Compute position values for each planet */
	earth_hour += inc;
	earth_hour = earth_hour - ((int)(earth_hour / 24)) * 24;
	earth_day += inc / 24.0;
	earth_day = earth_day - ((int)(earth_day / 365)) * 365;
	mercury_day += inc / 24.0;
	mercury_day = mercury_day - ((int)(mercury_day / 88)) * 88;
	venus_day += inc / 24.0;
	venus_day = venus_day - ((int)(venus_day / 225)) * 225;
	mars_day += inc / 24.0;
	mars_day = mars_day - ((int)(mars_day / 687)) * 687;
	jupiter_day += inc / 24.0;
	jupiter_day = jupiter_day - ((int)(jupiter_day / 4380)) * 4380;
	saturn_day += inc / 24.0;
	saturn_day = saturn_day - ((int)(saturn_day / 10585)) * 10585;
	uranus_day += inc / 24.0;
	uranus_day = uranus_day - ((int)(uranus_day / 30660)) * 30660;
	neptune_day += inc / 24.0;
	neptune_day = uranus_day - ((int)(neptune_day / 60225)) * 60225;

	glTranslatef(0.0, 0.0, -1.0);

	/* Sun */
	glRotatef(360*earth_day / 365.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glutWireSphere(0.0927f, 15, 15);

	/* Mercury - period around sun = 88 days */
	glPushMatrix();
	glRotatef(360.0*mercury_day / 88.0f, 0.0, 1.0, 0.0);
	glTranslatef(3.90f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutWireSphere(0.0003f, 10, 10);
	glPopMatrix();

	/* Venus - period around sun = 225 days */
	glPushMatrix();
	glRotatef(360.0*venus_day / 225.0f, 0.0, 1.0, 0.0);
	glTranslatef(7.20f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutWireSphere(0.0008f, 10, 10);
	glPopMatrix();

	/* Earth and Moon - period around sun = 365 days */
	// Position around the sun
	glPushMatrix();
	glRotatef(360.0*earth_day / 365.0f, 0.0, 1.0, 0.0);
	glTranslatef(10.0f, 0.0, 0.0);
	// Rotate the earth on its axis
	glPushMatrix();
	glRotatef(360.0*earth_hour / 24.0f, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glutWireSphere(0.0009f, 10, 10);
	glPopMatrix();
	// Moon
	glRotatef(360.0 * 4 * earth_day / 365.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.003f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutWireSphere(0.0002f, 10, 10);
	glPopMatrix();

	/* Mars - period around sun = 687 days */
	glPushMatrix();
	glRotatef(360.0*mars_day / 687.0f, 0.0, 1.0, 0.0);
	glTranslatef(15.2f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutWireSphere(0.0005f, 10, 10);
	glPopMatrix();

	/* Jupiter - period around sun = 4380 days (12 years)*/
	glPushMatrix();
	glRotatef(360.0*jupiter_day / 4380.0f, 0.0, 1.0, 0.0);
	glTranslatef(52.04f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutWireSphere(0.0095f, 10, 10);
	glPopMatrix();

	/* Saturn - period around sun = 10585 days (29 years)*/
	glPushMatrix();
	glRotatef(360.0*saturn_day / 10585.0f, 0.0, 1.0, 0.0);
	glTranslatef(95.4f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutWireSphere(0.0080f, 10, 10);
	glPopMatrix();

	/* Uranus - period around sun = 30660 days (84 years)*/
	glPushMatrix();
	glRotatef(360.0*uranus_day / 30660.0f, 0.0, 1.0, 0.0);
	glTranslatef(191.8f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutWireSphere(0.0034f, 10, 10);
	glPopMatrix();

	/* Neptune - period around sun = 60225 days (165 years)*/
	glPushMatrix();
	glRotatef(360.0*neptune_day / 60225.0f, 0.0, 1.0, 0.0);
	glTranslatef(300.6f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutWireSphere(0.0033f, 10, 10);
	glPopMatrix();

	glutSwapBuffers();
}

void reportGLError(const char * msg)
{
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		fprintf(stderr, "OpenGL Error: %s %s\n", msg, errString);
	}
	return;
}

void init(int width, int height)
{
	GLint format;
	GLsizei w, h;
	tgaInfo *info = 0;
	int mode;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	resize(width, height);

	info = tgaLoad("Textures/sunmap.tga");

	if (info->status != TGA_OK) {
		fprintf(stderr, "error loading texture image: %d\n", info->status);

		return;
	}
	if (info->width != info->height) {
		fprintf(stderr, "Image size %d x %d is not rectangular, giving up.\n",
			info->width, info->height);
		return;
	}

	mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
	glGenTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Upload the texture bitmap. 
	w = info->width;
	h = info->height;

	reportGLError("before uploading texture");
	format = (mode == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
		GL_UNSIGNED_BYTE, info->imageData);
	reportGLError("after uploading texture");

	tgaDestroy(info);

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("Sonnensystem");
	glutDisplayFunc(&display);
	glutIdleFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	glutSpecialFunc(&specialKeyPressed);
	init(640, 480);
	glutFullScreen();
	glutMainLoop();
	return 0;
}