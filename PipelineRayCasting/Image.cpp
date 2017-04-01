#include "Image.h"



Image::Image(int width, int height)
{
	w = width;
	h = height; 
	pixels = new RGBType[w*h];
}


Image::~Image()
{
}

void Image::saveImage(string fileName)
{
	FILE *file;
	int k = w*h;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi*m;

	unsigned char bmpfileheader[14] = { 'B', 'M', 0,0,0,0, 0,0,0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0 ,0,0,0,0, 0,0,0,0, 1,0,24,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	file = fopen(fileName.c_str(), "wb");
	fwrite(bmpfileheader, 1, 14, file);
	fwrite(bmpinfoheader, 1, 40, file);

	for (int i = 0; i < k; i++)
	{
		RGBType rgb = pixels[i];

		double red = (pixels[i].r);
		double green = (pixels[i].g);
		double blue = (pixels[i].b);

		/*cout << pixels[i].r << endl;
		cout << pixels[i].g << endl;
		cout << pixels[i].b << endl;

		cout << endl;*/

		unsigned char color[3] = { blue, green, red };

		fwrite(color, 1, 3, file);
	}

	fclose(file);

	//delete pixels;
}

void Image::setPixel(double r, double g, double b, int x, int y)
{

	RGBType newRBG;
	newRBG.r = r;
	newRBG.g = g;
	newRBG.b = b;

	pixels[y * w + x] = newRBG;

	cout << pixels[y * w + x].r<< endl;
	cout << pixels[y * w + x].g << endl;
	cout << pixels[y * w + x].b << endl;

	cout << endl;
}

/*void Image::setPixel(Vec3 color, int width, int height)
{
	RGBType newRBG;
	newRBG.r = color.x;
	newRBG.g = color.y;
	newRBG.b = color.z;


	pixels[height * w + width] = newRBG;
}*/
