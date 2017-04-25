#include <iostream>
#include "ParamsFile.h"
#include "RayCasting.h"
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


//TODO use params from file instead
void defineParams()
{

}

void initialize()
{
	srand(time(NULL));

	myRender = new RayCasting();
	myImageProcessor = new PNGProcessor();
	myOutputProcessor = new StandardOutputProcessor();
	myEntryPocessor = new StandardEntryProcess();

	defineParams();
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
	myEntryPocessor->processEntry(paramsFile);
}

void processRender(/*vector<Sphere> objects, CameraDefinition camera,*/ float w, float h)
{
	image = myRender->RenderScene(/*objects, camera,*/ w, h);
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
		processOutput("OutImage.png");
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
	processRender(640, 480);

	//Add filter
	//processImage();

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
	glutAddMenuEntry("Quit", QUIT);


	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	//glutMouseFunc(mouse);
	glutMainLoop();


	//Create image
	processOutput("OutImage.png");

	system("pause");
	return 0;
}