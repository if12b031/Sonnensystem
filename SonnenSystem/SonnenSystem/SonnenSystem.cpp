#include <stdlib.h>
#include <stdio.h>
#define RAD(x) (((x)*M_PI)/180.)
#define _USE_MATH_DEFINES
#include <GL/tga.h>
#include <math.h>
// Some math.h files don't define pi...
#ifndef M_PI
#define M_PI 3.141592653
#endif

#ifdef __APPLE__
#include <GLUT/glut.h> 
#include <OpenGL/gl.h>  
#include <OpenGL/glu.h>  
#else
#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#endif

#ifdef __STRICT_ANSI__
#define sinf(x) ((float)sin((x)))
#define cosf(x) ((float)cos((x)))
#define atan2f(x, y) ((float)atan2((x), (y)))
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
float inc = 0.0;
float resume = 1.0;
float scale = 2.0;
int started = 0; // User has started animation
/* Camera movement taken from http://www.lighthouse3d.com/tutorials/glut-tutorial/ */
int begin_x = -1; // X value of mouse movement
GLfloat angle_x = -2.68f;  // Angle of spin around x axis of scene
float deltaAngle_x = 0.0f; // Difference between old x and new x
float deltaMove = 0.0f; // Indicates wheather user is moving
float lx = -0.5f, lz = 1.0f; // Actual vector representing the camera's direction
float x = 0.5f, z = -0.2f; // XZ position of the camera
GLuint texture;
GLUquadricObj *sunSphere;

void resize(int width, int height)
{
	// prevent division by zero
	if (height == 0) { height = 1; }

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.001f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 13: // Enter - Start animation
		if (inc < 0.9f) {
			inc = 1.0f;
			started = 1;
		}
		break;
	case 27: // Esc - Close program
		glutDestroyWindow(window);
		exit(0);
		break;
	case 'w': // Move forward
		deltaMove = 0.01f;
		glutPostRedisplay();
		break;
	case 's': // Move back
		deltaMove = -0.01f;
		glutPostRedisplay();
		break;
	case 'W': // Move fast forward
		deltaMove = 0.5f;;
		glutPostRedisplay();
		break;
	case 'S': // Move fast back
		deltaMove = -0.5f;;
		glutPostRedisplay();
		break;
	case 'e': // Scalue up
		scale += 0.5f;
		glutPostRedisplay();
		break;
	case 'r': // Scale down
		if (scale > 0.5f) {
			scale -= 0.5f;
			glutPostRedisplay();
		}
		break;
	case 'p': // Pause rotations
		if (inc > 0.0f) {
			resume = inc;
			inc = 0.0f;
			glutPostRedisplay();
		}
		break;
	case 'u': // Resume rotations
		inc = resume;
		glutPostRedisplay();
		break;
	case ' ': // Reset planets
		if (started) {
			inc = 1.0;
		}
		resume = 1.0;
		scale = 2.0;
		mercury_day = 0.0;
		venus_day = 0.0;
		earth_hour = 0.0;
		earth_day = 0.0;
		mars_day = 0.0;
		jupiter_day = 0.0;
		saturn_day = 0.0;
		uranus_day = 0.0;
		neptune_day = 0.0;
		glutPostRedisplay();
		break;
	case '+': // Speed up
		inc *= 1.5;
		break;
	case '-': // Speed down
		inc *= 0.5;
		break;
	case '0': // Jump to Sun
		x = 0.5f;
		z = -0.2f;
		lx = -0.5f;
		lz = 1.0f;
		angle_x = -2.68f;
		glutPostRedisplay();
		break;
	case '1': // Jump to Mercury
		x = 0.3f;
		z = 0.39f;
		lx = -1.0f;
		lz = 0.6f;
		angle_x = -2.11f;
		glutPostRedisplay();
		break;
	case '2': // Jump to Venus
		x = 0.3f;
		z = 1.0f;
		lx = -1.0f;
		lz = 1.0f;
		angle_x = -2.36f;
		glutPostRedisplay();
		break;
	case '3': // Jump to Earth
		x = 0.3f;
		z = 1.5f;
		lx = -1.0f;
		lz = 1.0f;
		angle_x = -2.36f;
		glutPostRedisplay();
		break;
	case '4': // Jump to Mars
		x = 0.3f;
		z = 2.5f;
		lx = -1.0f;
		lz = 1.0f;
		angle_x = -2.36f;
		glutPostRedisplay();
		break;
	case '5': // Jump to Jupiter
		x = 0.3f;
		z = 9.8f;
		lx = -1.0f;
		lz = 1.0f;
		angle_x = -2.36f;
		glutPostRedisplay();
		break;
	case '6': // Jump to Saturn
		x = 0.3f;
		z = 18.5f;
		lx = -1.0f;
		lz = 1.0f;
		angle_x = -2.36f;
		glutPostRedisplay();
		break;
	case '7': // Jump to Uranus
		x = 0.3f;
		z = 37.5f;
		lx = -1.0f;
		lz = 1.0f;
		angle_x = -2.36f;
		glutPostRedisplay();
		break;
	case '8': // Jump to Neptune
		x = 0.3f;
		z = 59.5f;
		lx = -1.0f;
		lz = 1.0f;
		angle_x = -2.36f;
		glutPostRedisplay();
		break;
	}
}

void keyReleased(unsigned char key, int x, int y) 
{
	switch (key) {
	case 'w': deltaMove = 0;
		break;
	case 's': deltaMove = 0; 
		break;
	case 'W': deltaMove = 0;
		break;
	case 'S': deltaMove = 0;
		break;
	}
}

static void specialKeyPressed(int key, int x, int y)
{

}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			angle_x += deltaAngle_x;
			begin_x = -1;
		}
		else  {
			begin_x = x;
		}
	}
	glutPostRedisplay();
}


void mouseMotion(int x, int y) {

	if (begin_x > 0) {
		// Update deltaAngle
		deltaAngle_x = (x - begin_x) * 0.01f;
		// Update camera's direction
		lx = sin(angle_x + deltaAngle_x);
		lz = -cos(angle_x + deltaAngle_x);
	}
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void display()
{
	/*
	* Proprtion <Distance>:<Planet Size> = 10:1
	*
	* Distances to sun in AE (1 AE = 150.00.000 km),
	* and for this project used values (1 AE = 1f):
	* 
	* Mercury -	0,39	>> 0,39f
	* Venus -	0,72	>> 0,72f
	* Earth -	1,00	>> 1,00f
	* Mars -	1,52	>> 1,52f
	* Jupiter -	5,20	>> 5,2f
	* Saturn -	9,54	>> 9,54f
	* Uranus -	19,18	>> 19,18f
	* Neptune -	30,06	>> 30,06f
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
	glBindTexture(GL_TEXTURE_2D, texture);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat light_color[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat material_color[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_color);

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

	/* Update X and Z if user is moving */
	if (deltaMove) {
		computePos(deltaMove);
	}

	gluLookAt(x, 0.0f, z,
		x + lx, 0.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	glScalef(scale, scale, scale);

	/* Sun */
	glPushMatrix();
	glRotatef(360 * earth_day / 365.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	gluSphere(sunSphere, 0.0927f, 30, 30);
	glPopMatrix();

	/* Mercury - period around sun = 88 days */
	glPushMatrix();
	glRotatef(360.0*mercury_day / 88.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, 0.39f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutSolidSphere(0.0003f, 30, 30);
	glPopMatrix();

	/* Venus - period around sun = 225 days */
	glPushMatrix();
	glRotatef(360.0*venus_day / 225.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, 0.72f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutSolidSphere(0.0008f, 30, 30);
	glPopMatrix();

	/* Earth and Moon - period around sun = 365 days */
	// Position around the sun
	glPushMatrix();
	glRotatef(360.0*earth_day / 365.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 1.0f);
	// Rotate the earth on its axis
	glPushMatrix();
	glRotatef(360.0*earth_hour / 24.0f, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(0.0009f, 30, 30);
	glPopMatrix();
	// Moon
	glRotatef(360.0 * 4 * earth_day / 365.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, 0.003f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutSolidSphere(0.0002f, 10, 10);
	glPopMatrix();

	/* Mars - period around sun = 687 days */
	glPushMatrix();
	glRotatef(360.0*mars_day / 687.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, 1.52f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutSolidSphere(0.0005f, 20, 20);
	glPopMatrix();

	/* Jupiter - period around sun = 4380 days (12 years)*/
	glPushMatrix();
	glRotatef(360.0*jupiter_day / 4380.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, 5.2f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutSolidSphere(0.0095f, 30, 30);
	glPopMatrix();

	/* Saturn - period around sun = 10585 days (29 years)*/
	glPushMatrix();
	glRotatef(360.0*saturn_day / 10585.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, 9.54f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutSolidSphere(0.0080f, 30, 30);
	glPopMatrix();

	/* Uranus - period around sun = 30660 days (84 years)*/
	glPushMatrix();
	glRotatef(360.0*uranus_day / 30660.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, 19.08f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutSolidSphere(0.0034f, 30, 30);
	glPopMatrix();

	/* Neptune - period around sun = 60225 days (165 years)*/
	glPushMatrix();
	glRotatef(360.0*neptune_day / 60225.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, 30.06f);
	glColor3f(0.3f, 0.7f, 0.3f);
	glutSolidSphere(0.0033f, 30, 30);
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

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(60, timer, 1);
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
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	resize(width, height);
	

	info = tgaLoad("Textures/sunmap.tga");

	if (info->status != TGA_OK) {
		fprintf(stderr, "error loading texture image: %d\n", info->status);

		return;
	}
	/*if (info->width != info->height) {
		fprintf(stderr, "Image size %d x %d is not rectangular, giving up.\n",
			info->width, info->height);
		return;
	}*/

	mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
	glGenTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	sunSphere = gluNewQuadric();
	gluQuadricDrawStyle(sunSphere, GLU_FILL);
	gluQuadricTexture(sunSphere, GL_TRUE);
	gluQuadricNormals(sunSphere, GLU_SMOOTH);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("Sonnensystem");
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	glutKeyboardUpFunc(&keyReleased);
	glutSpecialFunc(&specialKeyPressed);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(60, timer, 1);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	init(640, 480);
	glutFullScreen();
	glutMainLoop();
	return 0;
}