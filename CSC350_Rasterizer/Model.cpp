#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

Model::Model(){
	triangles;
}

int Model::NumTriangles(){
	return triangles.size();
}

Triangle3D Model::operator[](int i){
	return triangles[i];
}

void Model::Transform(Matrix4 m){
	for (int i = 0; i < triangles.size(); i++){
		triangles[i].Transform(m);
	}
}

void Model::ReadFromOBJFile(string filepath, Color pFillColor){
	vector<Vector4> vertices;
	
	ifstream myFile(filepath);
	if (myFile.is_open()){
		string line;
		//for each line in a file
		while (getline(myFile, line)){
			vector<string> words;

			istringstream s(line);
			string myWord;
			while (getline(s, myWord, ' ')){
				words.push_back(myWord);
			}


			if (!words[0].compare("v")){
				float xVal = atof(words[1].c_str());
				float yVal = atof(words[2].c_str());
				float zVal = atof(words[3].c_str());
				Vector4 vTemp(xVal,yVal,zVal,1.0);
				vertices.push_back(vTemp);
			}
			else if (!words[0].compare("f")){
				if (words.size() == 4){
					int vert1 = atoi(words[1].c_str()) - 1;
					int vert2 = atoi(words[2].c_str()) - 1;
					int vert3 = atoi(words[3].c_str()) - 1;
						Triangle3D tTemp(vertices[vert1], vertices[vert2], vertices[vert3], pFillColor, pFillColor, pFillColor);
						triangles.push_back(tTemp);
				}
				else if (words.size() == 5){
					int vert1 = atoi(words[1].c_str());
					int vert2 = atoi(words[2].c_str());
					int vert3 = atoi(words[3].c_str());
					int vert4 = atoi(words[4].c_str());
					Triangle3D tTemp1(vertices[vert1], vertices[vert3], vertices[vert4], pFillColor, pFillColor, pFillColor);
					Triangle3D tTemp2(vertices[vert1], vertices[vert2], vertices[vert3], pFillColor, pFillColor, pFillColor);
					triangles.push_back(tTemp2);
					triangles.push_back(tTemp1);
				}
			}
			words.clear();

		}
		myFile.close();
	}

}