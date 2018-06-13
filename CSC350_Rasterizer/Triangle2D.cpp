#include "Triangle2D.h"
#include <iostream>
using namespace std;


Triangle2D::Triangle2D(){
	v0 = Vector3(0.0, 0.0, 1.0);
	v1 = Vector3(0.0, 0.0, 1.0);
	v2 = Vector3(0.0, 0.0, 1.0);
	c0 = ColorClear;
	c1 = ColorClear;
	c2 = ColorClear;
}

Triangle2D::Triangle2D(Triangle3D t){
	v0 = Vector3(t.v0.x, t.v0.y, 1);
	v1 = Vector3(t.v1.x, t.v1.y, 1);
	v2 = Vector3(t.v2.x, t.v2.y, 1);
	c0 = t.c0;
	c1 = t.c1;
	c2 = t.c2;
}

Triangle2D::Triangle2D(Vector3 pv0, Vector3 pv1, Vector3 pv2, Color pc0, Color pc1, Color pc2){
	v0 = pv0;
	v1 = pv1;
	v2 = pv2;
	c0 = pc0;
	c1 = pc1;
	c2 = pc2;
}

void  Triangle2D::CalculateBarycentricCoordinates(Vector2 p, float &lambda1, float &lambda2, float &lambda3){
	float a1 = Determinant(v1 - v2, p - v2) / 2;
	float a2 = Determinant(p - v2, v0 - v2) / 2;
	float afull = Determinant(v1 - v2, v0 - v2)/ 2;
	lambda1 = a1 / afull;
	lambda2 = a2 / afull;
	lambda3 = 1.0 - lambda1 - lambda2;
}

void Triangle2D::Transform(Matrix3 m){
	v0 = m * v0;
	v1 = m * v1;
	v2 = m * v2;
}

//============================================ Triangle3D ============================================================

Triangle3D::Triangle3D(){
	v0 = Vector4(0.0, 0.0, 0.0, 1.0);
	v1 = Vector4(0.0, 0.0, 0.0, 1);
	v2 = Vector4(0.0, 0.0, 0, 1.0);
	c0 = ColorClear;
	c1 = ColorClear;
	c2 = ColorClear;
}

Triangle3D::Triangle3D(Vector4 pv0, Vector4 pv1, Vector4 pv2, Color pc0, Color pc1, Color pc2){
	v0 = pv0;
	v1 = pv1;
	v2 = pv2;
	c0 = pc0;
	c1 = pc1;
	c2 = pc2;
}

void Triangle3D::Transform(Matrix4 m){
	v0 = m * v0;
	v1 = m * v1;
	v2 = m * v2;
}