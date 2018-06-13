#include "Matrix.h"

#define _USE_MATH_DEFINES
#include <math.h>

Matrix3::Matrix3(){
	float m21 = 0.0, m31 = 0.0;
	float m12 = 0.0, m32 = 0.0;
	float m13 = 0.0, m23 = 0.0;
	float m11 = 1.0, m22 = 1.0, m33 = 1.0;
}

Matrix3::Matrix3(float p11, float p21, float p31, float p12, float p22, float p32, float p13, float p23, float p33){
	m11 = p11;
	m21 = p21;
	m31 = p31;
	m12 = p12;
	m22 = p22;
	m32 = p32;
	m13 = p13;
	m23 = p23;
	m33 = p33;
}

Vector3 Matrix3::operator*(Vector3 other){
	float newX = (other.x * m11) + (other.y * m21) + (other.w * m31);
	float newY = (other.x * m12) + (other.y * m22) + (other.w * m32);
	float newW = (other.x * m13) + (other.y * m23) + (other.w * m33);

	return Vector3(newX, newY, newW);
}

Matrix3 Matrix3::operator*(Matrix3 p){
	float new11, new21, new31;
	float new12, new22, new32;
	float new13, new23, new33;
	
	
	
	new11 = (p.m11 * m11) + (p.m12 * m21) + (p.m13 * m31);
	new12 = (p.m11 * m12) + (p.m12 * m22) + (p.m13 * m32);
	new13 = (p.m11 * m13) + (p.m12 * m23) + (p.m13 * m33);

	new21 = (p.m21 * m11) + (p.m22 * m21) + (p.m23 * m31);
	new22 = (p.m21 * m12) + (p.m22 * m22) + (p.m23 * m32);
	new23 = (p.m21 * m13) + (p.m22 * m23) + (p.m23 * m33);

	new31 = (p.m31 * m11) + (p.m32 * m21) + (p.m33 * m31);
	new32 = (p.m31 * m12) + (p.m32 * m22) + (p.m33 * m32);
	new33 = (p.m31 * m13) + (p.m32 * m23) + (p.m33 * m33);


	return Matrix3(new11, new21, new31,
					new12, new22, new32,
					new13, new23, new33);
}


Matrix3 Scale2Dm(float sX, float sY){
	return Matrix3(sX, 0.0, 0.0, 0.0, sY, 0.0, 0.0, 0.0, 1.0);
}

Matrix3 Translate2D(float sX, float sY){
	return Matrix3(1.0, 0.0, sX,
					0.0, 1.0, sY,
					0.0, 0.0, 1.0);
}

Matrix3 Rotate2D(float degrees){
	float radians = degrees * (M_PI / 180.0);


	return Matrix3( cosf(radians), -sinf(radians), 0.0,
		sinf(radians), cosf(radians), 0.0,
		0.0, 0.0, 1.0);
}


//============================================================ Matrix4 stuff =================================================

Matrix4::Matrix4(){
	 m11 = 1.0, m21 = 0, m31 = 0, m41 = 0;
	 m12 = 0, m22 = 1.0, m32 = 0, m42 = 0;
	 m13 = 0, m23 = 0, m33 = 1.0 , m43 = 0;
	 m14 = 0, m24 = 0, m34 = 0, m44 = 1.0;

}

Matrix4::Matrix4(float p11, float p21, float p31, float p41,
				float p12, float p22, float p32, float p42,
				float p13, float p23, float p33, float p43,
				float p14, float p24, float p34, float p44){

	m11 = p11, m21 = p21, m31 = p31, m41 = p41;
	m12 = p12, m22 = p22, m32 = p32, m42 = p42;
	m13 = p13, m23 = p23, m33 = p33, m43 = p43;
	m14 = p14, m24 = p24, m34 = p34, m44 = p44;
}

Vector4 Matrix4::operator*(Vector4 other){

	float newX = (other.x * m11) + (other.y * m21) + (other.z * m31) + (other.w * m41);
	float newY = (other.x * m12) + (other.y * m22) + (other.z * m32) + (other.w * m42);
	float newZ = (other.x * m13) + (other.y * m23) + (other.z * m33) + (other.w * m43);
	float newW = (other.x * m14) + (other.y * m24) + (other.z * m34) + (other.w * m44);

	return Vector4(newX, newY, newZ, newW);
}

Matrix4 Matrix4::operator*(Matrix4 p){

	float new11, new21, new31, new41;
	float new12, new22, new32, new42;
	float new13, new23, new33, new43;
	float new14, new24, new34, new44;



	new11 = (p.m11 * m11) + (p.m12 * m21) + (p.m13 * m31) + (p.m14 * m41);
	new12 = (p.m11 * m12) + (p.m12 * m22) + (p.m13 * m32) + (p.m14 * m42);
	new13 = (p.m11 * m13) + (p.m12 * m23) + (p.m13 * m33) + (p.m14 * m43);
	new14 = (p.m11 * m14) + (p.m12 * m24) + (p.m13 * m34) + (p.m14 * m44);

	new21 = (p.m21 * m11) + (p.m22 * m21) + (p.m23 * m31) + (p.m24 * m41);
	new22 = (p.m21 * m12) + (p.m22 * m22) + (p.m23 * m32) + (p.m24 * m42);
	new23 = (p.m21 * m13) + (p.m22 * m23) + (p.m23 * m33) + (p.m24 * m43);
	new24 = (p.m21 * m14) + (p.m22 * m24) + (p.m23 * m34) + (p.m24 * m44);

	new31 = (p.m31 * m11) + (p.m32 * m21) + (p.m33 * m31) + (p.m34 * m41);
	new32 = (p.m31 * m12) + (p.m32 * m22) + (p.m33 * m32) + (p.m34 * m42);
	new33 = (p.m31 * m13) + (p.m32 * m23) + (p.m33 * m33) + (p.m34 * m43);
	new34 = (p.m31 * m14) + (p.m32 * m24) + (p.m33 * m34) + (p.m34 * m44);

	new41 = (p.m41 * m11) + (p.m42 * m21) + (p.m43 * m31) + (p.m44 * m41);
	new42 = (p.m41 * m12) + (p.m42 * m22) + (p.m43 * m32) + (p.m44 * m42);
	new43 = (p.m41 * m13) + (p.m42 * m23) + (p.m43 * m33) + (p.m44 * m43);
	new44 = (p.m41 * m14) + (p.m42 * m24) + (p.m43 * m34) + (p.m44 * m44);


	return Matrix4(new11, new21, new31,new41,
					new12, new22, new32, new42,
					new13, new23, new33, new43,
					new14, new24, new34, new44);
}

Matrix4 Translate3D(float tX, float tY, float tZ){
	return Matrix4(1.0, 0.0, 0.0, tX,
				   0.0, 1.0, 0.0, tY,
				   0.0, 0.0, 1.0, tZ,
				   0.0, 0.0, 0.0, 1 );

}

Matrix4 Scale3D(float sX, float sY, float sZ){
	return Matrix4(sX, 0.0, 0.0, 0.0,
		0.0, sY, 0.0, 0.0,
		0.0, 0.0, sZ, 0.0,
		0.0, 0.0, 0.0, 1);
}


Matrix4 RotateX3D(float degrees){
	return Matrix4(1.0, 0, 0, 0,
				   0, cosf(degrees), sinf(degrees), 0,
				   0, -sinf(degrees), cosf(degrees), 0,
				   0, 0, 0, 1);

}

Matrix4 RotateY3D(float degrees){
	return Matrix4(cosf(degrees), 0, -sinf(degrees), 0,
		0, 1, 0, 0,
		sinf(degrees), 0, cosf(degrees), 0,
		0, 0, 0, 1);


}

Matrix4 RotateZ3D(float degrees){
	return Matrix4(cosf(degrees), sinf(degrees), 0, 0,
		-sinf(degrees), cosf(degrees), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
Matrix4 Rotate3D(float degreesX, float degreesY, float degreesZ){
	return RotateX3D(degreesX) * RotateY3D(degreesY) * RotateZ3D(degreesZ);
}

Matrix4 Rotate3D(float degrees, Vector4 vec){
	float beta = acosf(vec.y / vec.Magnitude());
	float alpha = atanf(vec.x / vec.z);
	return RotateY3D(-alpha) * RotateX3D(-beta) * RotateY3D(degrees) * RotateX3D(beta) * RotateY3D(alpha);
}

/*
Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up){
	Matrix4 translate = Translate3D(-eye.x, -eye.y, -eye.z);
	Vector4 look = (spot - eye).Normalize();
	Vector4 right = (look.Cross(up)).Normalize();
	Vector4 up = (right.Cross(look)).Normalize();

	Matrix4 reMap(right.x, right.y, right.z, 0
				  up.x, up.y, up,z, 0
				  -look.x, -look.y, -look.z, 0
				  0, 0, 0, 1);

	return reMap * translate;
}





*/
