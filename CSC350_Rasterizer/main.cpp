#include <iostream>
using namespace std;
#include "Color.h"
#include "Raster.h"
#include "Vector.h"
#include "Triangle2D.h"

int main(){
	/*
	Raster myRaster(100, 100, ColorWhite);
	Triangle3D t(Vector4(0, 0, 0, 1), Vector4(40, 0, 0, 1), Vector4(40, 40, 0, 1), ColorRed, ColorBlue, ColorGreen);
	
	Matrix4 m = RotateX3D(60.0);
	//Matrix4 m = Translate3D(10, 10, 5);
	t.Transform(m);
	
	myRaster.DrawTriangle3D_Barycentric(t);
	myRaster.WriteToPPM();
	*/

	Raster myRaster(100, 100, ColorWhite);
	Model m = Model();
	m.ReadFromOBJFile("./bunny.obj", ColorRed);

	Matrix4 mat = Translate3D(50, 50, 0) * RotateZ3D(-45.0) * Scale3D(500, 500, 500);
	m.Transform(mat);

	myRaster.DrawModel(m);
	myRaster.WriteToPPM();

	cin.get();
	return 0;
}