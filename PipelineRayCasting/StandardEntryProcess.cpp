#include "StandardEntryProcess.h"
#include <iostream>
#include <string>


StandardEntryProcess::StandardEntryProcess()
{
}


StandardEntryProcess::~StandardEntryProcess()
{
}

ParamsFile StandardEntryProcess::processEntry(ParamsFile *paramsFile)
{
	ifstream file;
	file.open("files/params.txt");

	if (!file.is_open())
	{
		exit(EXIT_FAILURE);
	}

	string line;
	string ReadingParam;
	int nLights, nObjects;
	char program[3];
	char outputType;
	int raio;
	Vec3f pos = Vec3f(0, 0, 0);
	Vec3f color = Vec3f(0, 0, 0);
	Color tempColor;

	while (file.good())
	{
		getline(file, line);
		if (line[0] != '#' || line[1] != '#')
		{
			if (line == "begin stage 1")
			{
				//camera
				cout << line << endl;
				getline(file, line); //descarta a linha
				cout << "Configuring the camera..." << endl;
				file >> ReadingParam >> paramsFile->cameraDefinition.position.x >> paramsFile->cameraDefinition.position.y >> paramsFile->cameraDefinition.position.z; //define a posicao da câmera
				cout << ReadingParam << " " << paramsFile->cameraDefinition.position.x << ", " << paramsFile->cameraDefinition.position.y << ", " << paramsFile->cameraDefinition.position.z << endl;

				//light
				getline(file, line); //descarta a linha
				getline(file, line); //descarta a linha

				file >> ReadingParam >> nLights; //pega o numero de luzes
				getline(file, line); //descarta a linha
				cout << "Configuring the lights..." << endl;
				for (int i = 1; i <= nLights; i++)
				{
					getline(file, line); //descarta a linha
					cout << line << i << endl;
					file >> ReadingParam >> pos.x >> pos.y >> pos.z; //seta a posicao em valores temporarios

					paramsFile->lightPointDefinition.setCenter(Vec3f(pos.x, pos.y, pos.z)); //seta a posicao
					cout << ReadingParam << " " << pos.x << ", " << pos.y << ", " << pos.z << endl;

					getline(file, line); //descarta a linha

					file >> ReadingParam >> color.x >> color.y >> color.z; // seta a cor	
					paramsFile->lightPointDefinition.setColor(color);

					cout << ReadingParam << " " << paramsFile->lightPointDefinition.getColor().getColorRed() << ", " << paramsFile->lightPointDefinition.getColor().getColorGreen() << ", " << paramsFile->lightPointDefinition.getColor().getColorBlue() << endl;
					getline(file, line); //descarta a linha
					getline(file, line); //descarta a linha
					cout << line << i << endl;
				}

				//primitives
				getline(file, line); //descarta a linha
				file >> ReadingParam >> nObjects; //pega o numero de objetos
				getline(file, line); //descarta a linha
				getline(file, line); //descarta a linha
				cout << "Configuring the primitives..." << endl;
				for (int i = 0; i < nObjects; i++)
				{
					getline(file, line); //descarta a linha
					cout << line << i << endl;
					file >> ReadingParam >> raio;
					cout << ReadingParam << " " << raio << endl;

					getline(file, line); //descarta a linha
					file >> ReadingParam >> color.x >> color.y >> color.z;
					cout << ReadingParam << " " << color.x << ", " << color.y << ", " << color.z << endl;

					getline(file, line); //descarta a linha
					file >> ReadingParam >> pos.x >> pos.y >> pos.z;
					cout << ReadingParam << " " << pos.x << ", " << pos.y << ", " << pos.z << endl;

					//Sphere newSphere(Vec3f(pos.x, pos.y, pos.z), raio, color);
					//newSphere.setColor(color);
					//paramsFile->objects.push_back(dynamic_cast<Object*>(&newSphere));
					paramsFile->objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(pos.x, pos.y, pos.z), raio, color, 1, 1.33)));

					getline(file, line); //descarta a linha
				}
			}
			else if (line == "begin stage 3")
			{
				cout << line << endl;
				getline(file, line); //descarta a linha
				getline(file, line); //descarta a linha
				file >> ReadingParam >> program;
				cout << ReadingParam << " " << program << endl;
				//program é o tipo do algoritimo de render rc ou rt
			}
			else if (line == "begin stage 4")
			{
				cout << line << endl;
				cout << "Aqui ler filtros pos-render!" << endl;
			}
			else if (line == "begin stage 5")
			{
				//output
				cout << line << endl;
				getline(file, line); //descarta a linha
				file >> ReadingParam >> paramsFile->height >> paramsFile->width >> outputType;
				cout << ReadingParam << " " << paramsFile->height << " x " << paramsFile->width << " - " << outputType << endl;
				//outputType é um char que recebe s|f
			}
		}
	}

	return *paramsFile;
}

ParamsFile StandardEntryProcess::processEntry2(ParamsFile * paramsFile)
{
	ifstream _arq;
	_arq.open("files/params.txt");

	if (!_arq.is_open()) {
		cout << "file not found" << endl;
		exit(0);
	}

	stringstream fileLine;
	string newLine;

	//Vec3f color;
	//Vec3f position;
	//float reflection, transparency, emission;

	while (!_arq.eof()) {
		getline(_arq, newLine);

		fileLine.str("");
		fileLine.clear();

		fileLine << newLine;

		string word;
		fileLine >> word;

		if (word == "#") {
			continue;
		}
		else if (word == "cam:") {
			float x, y, z;
			fileLine >> x;
			fileLine >> y;
			fileLine >> z;
			//paramsFile cameraDefinition.position(Vec3f(x, y, z));
			paramsFile->cameraDefinition.position = Vec3f(x, y, z);
		}
		else if (word == "fov:") {
			double fov;
			fileLine >> fov;
			paramsFile->cameraDefinition.setFOV(fov);
		}
		else if (word == "target:") {
			float x, y, z;
			fileLine >> x;
			fileLine >> y;
			fileLine >> z;
			//paramsFile cameraDefinition.position(Vec3f(x, y, z));
			paramsFile->cameraDefinition.setTarget(Vec3f(x, y, z));
		}
		else if (word == "nlight") {
			int n_lights;
			string type, header;
			bool next = false;
			fileLine >> n_lights;
			for (int i = 0; i < n_lights; i++)
			{
				Vec3f color;
				Vec3f position;
				next = false;

				while (!next) {

					next = false;

					getline(_arq, newLine);

					fileLine.str("");
					fileLine.clear();

					fileLine << newLine;
					word.clear();
					fileLine >> word;


					if (word == "#") {
						continue;
					}
					if (word == "begin") {
						fileLine >> type;
					}
					if (word == "end") {
						if (type == "light") {
							paramsFile->objects.push_back(dynamic_cast<Object*>(new Sphere(position, 5, color, 0, 0, Vec3f(3))));
							//myParamsFile.objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 20, 10), 5, Vec3f(0, 0, 0), 0, 0.0, Vec3f(3))));
							//paramsFile->objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 0.0, 0.0), 0.8, Vec3f(0.0, 0.8, 0.0), 0, 0.5)));
						}
						type.clear();
						next = true;
					}
					if (word == "color:") {
						fileLine >> color.x;
						fileLine >> color.y;
						fileLine >> color.z;
					}
					if (word == "position:") {
						fileLine >> position.x;
						fileLine >> position.y;
						fileLine >> position.z;
					}
				}
			}
		}
		else if (word == "program:") {
			string type;
			fileLine >> type;
		}
		else if (word == "nobjects") {
			int n_objects;
			string type, header;
			bool next = false;
			fileLine >> n_objects;
			for (int i = 0; i < n_objects; i++)
			{
				Vec3f color;
				Vec3f position;
				float x, y, z;
				float r, g, b;
				float refraction, emission, transparency, size;
				next = false;

				while (!next) {

					next = false;

					getline(_arq, newLine);

					fileLine.str("");
					fileLine.clear();

					fileLine << newLine;
					word.clear();
					fileLine >> word;


					if (word == "#") {
						continue;
					}
					if (word == "begin") {
						fileLine >> type;
					}
					if (word == "end") {
						if (type == "sphere") {
							paramsFile->objects.push_back(dynamic_cast<Object*>(new Sphere(position, size, color, refraction, transparency/*, emission*/)));
							//paramsFile->objects.push_back(dynamic_cast<Object*>(new Sphere(Vec3f(0.0, 0.0, 0.0), 0.8, Vec3f(0.0, 0.8, 0.0), 0, 0.5)));
						}
						type.clear();
						next = true;
					}
					if (word == "color:") {
						fileLine >> color.x;
						fileLine >> color.y;
						fileLine >> color.z;
					}
					if (word == "position:") {
						fileLine >> position.x;
						fileLine >> position.y;
						fileLine >> position.z;
					}
					if (word == "refraction:") {
						fileLine >> refraction;
					}
					if (word == "emission:") {
						fileLine >> emission;
					}
					if (word == "raio:") {
						fileLine >> size;
					}
					if (word == "transparency:") {
						fileLine >> transparency;
					}
				}

			}
		}
		else if (word == "output:") {
			float w, h;
			fileLine >> w;
			fileLine >> h;
			paramsFile->width = w;
			paramsFile->height = h;
		}
	}

	return *paramsFile;
}


string StandardEntryProcess::readRestOfLine(stringstream& line) {
	string myString;

	while (!line.eof()) {
		string temp;
		line >> temp;
		myString += temp + " ";

	}
	myString.erase(myString.length() - 1, myString.length()); //remove last space

	return myString;
}


bool StandardEntryProcess::strContains(stringstream& line, string part) {
	std::size_t found = line.str().find(part);

	return (found != std::string::npos); //if found == npos, string was not found
}