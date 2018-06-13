#ifndef Model_H
#define Model_H

#include <vector>
#include "Triangle2D.h"
using namespace std;

class Model{
private:
	
public:
	vector<Triangle3D> triangles;
	Model();
	int NumTriangles();
	Triangle3D operator[](int i);
	void Transform(Matrix4 m);
	void ReadFromOBJFile(string filepath, Color pFillColor);
};


#endif