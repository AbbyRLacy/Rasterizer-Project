
#ifndef Triangle2D_H
#define Triangle2D_H

#include "Vector.h"
#include "Color.h"
#include "Matrix.h"

struct Triangle3D;

struct Triangle2D{
	

	Vector3 v0;
	Vector3 v1;
	Vector3 v2;
	Color c0;
	Color c1;
	Color c2;

	Triangle2D();
	Triangle2D(Triangle3D t);
	Triangle2D(Vector3 pv0, Vector3 pv1, Vector3 pv2, Color pc0, Color pc1 , Color pc2);
	void CalculateBarycentricCoordinates(Vector2 p, float &lambda1, float &lambda2, float &lambda3);
	void Transform(Matrix3 m);
};

struct Triangle3D{
	Vector4 v0;
	Vector4 v1;
	Vector4 v2;
	Color c0;
	Color c1;
	Color c2;

	Triangle3D();
	Triangle3D(Vector4 pv0, Vector4 pv1, Vector4 pv2, Color pc0, Color pc1, Color pc2);
	void Transform(Matrix4 m);
};


#endif