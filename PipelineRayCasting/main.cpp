#include <iostream>
#include "ParamsFile.h"
#include "RayTracing.h"
#include "PNGProcessor.h"
#include "StandardOutputProcessor.h"
#include "StandardEntryProcess.h"
#include "Image.h"
#include <time.h>   
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

ParamsFile myParamsFile;
Image *image;
Render *myRender;
PNGProcessor *myImageProcessor;
OutputProcessor *myOutputProcessor;
EntryProcessor *myEntryPocessor;

int h = 480, w = 640;

Matrix44f lookAt(Vec3f pos, Vec3f target, Vec3f up)
{
	Vec3f z = (target - pos).normalize();
	Vec3f x = up.crossProduct(z).normalize();
	Vec3f y = z.crossProduct(x).normalize();
	
	Matrix44f mat;
	
	mat[0][0] = x.x;
	mat[0][1] = x.y;
	mat[0][2] = x.z;

	mat[1][0] = y.x;
	mat[1][1] = y.y;
	mat[1][2] = y.z;
	
	mat[2][0] = z.x;
	mat[2][1] = z.y;
	mat[2][2] = z.z;
	
	mat[3][0] = pos.x;
	mat[3][1] = pos.y;
	mat[3][2] = pos.z;
	
	mat[3][3] = 1;
	
	return mat;
}

void initialize()
{
	srand(time(NULL));

	myRender = new RayTracing();
	myImageProcessor = new PNGProcessor();
	myOutputProcessor = new StandardOutputProcessor();
	myEntryPocessor = new StandardEntryProcess();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glPixelZoom(1, -1);
}

void processEntry(ParamsFile paramsFile)
{
	ParamsFile newParams;
	myEntryPocessor->processEntry2(&newParams);
	myParamsFile.objects = newParams.objects;

	Camera myCam(lookAt(newParams.cameraDefinition.position, newParams.cameraDefinition.getTarget(), Vec3f(0, 1, 0)), newParams.cameraDefinition.FOV());
	
	myParamsFile.cameraDefinition = myCam;
	myParamsFile.width = newParams.width;
	myParamsFile.height = newParams.height;
}

void processRender()
{
	image = myRender->RenderScene(myParamsFile.objects, myParamsFile.cameraDefinition, myParamsFile.width, myParamsFile.height);
}


void processImage(int filterType)
{
	myImageProcessor->processImage(filterType, image);
}

void processOutput(string fileName)
{
	image->saveImage(fileName);
}

void displayImage() {

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2d(0, h);

	glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, &image->pixels[0]);

	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	if ('q' == key) {
		exit(0);
	}
	if ('g' == key) {
		//grey filter
		//processImage();
	}
	if ('s' == key) {
		//save
		processOutput("ImageWithFilter.png");
	}
	glutPostRedisplay();

}

enum MENU_TYPE
{
	SHARPEN,
	ORIGINAL,
	BLUR,
	EDGE,
	GREYSCALE,
	SAVE,
	QUIT,
};

void menu(int item)
{
	switch (item)
	{
	case MENU_TYPE::QUIT:
	{
		exit(0);
	}
	break;
	case MENU_TYPE::SAVE:
	{
		processOutput("result.png");
	}
	break;
	default:
	{
		processImage(item);
	}
	break;
	}

	glutPostRedisplay();

	return;
}

int main(int argc, char** argv)
{
	initialize();

	//Read file
	processEntry(myParamsFile);

	//Add configs from file to myParamsFile

	//Render Scene
	processRender();

	//Create image
	processOutput("OriginalImage.png");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(400, 60);
	glutCreateWindow("Post-Processing - CGA - 2017/1");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	// Create a menu
	glutCreateMenu(menu);

	// Add menu items
	glutAddMenuEntry("Sharpen", SHARPEN);
	glutAddMenuEntry("Original", ORIGINAL);
	glutAddMenuEntry("Blur", BLUR);
	glutAddMenuEntry("Edge", EDGE);
	glutAddMenuEntry("Grey Scale", GREYSCALE);
	glutAddMenuEntry("Save Image", SAVE);
	glutAddMenuEntry("Quit", QUIT);


	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	//glutMouseFunc(mouse);
	glutMainLoop();

	system("pause");
	return 0;
}