#ifndef Vector_H
#define Vector_H

struct Vector3;

struct Vector2{
	float x;
	float y;

	Vector2();
	Vector2(float pX, float pY);
	Vector2(Vector3 other);

	Vector2 operator*(float scalar);
	Vector2 operator+(Vector2 other);
	Vector2 operator-(Vector2 other);
	float Magnitude();
	float Dot(Vector2 other);
	Vector2 Normalize();
	Vector2 Perpendicular();




};

float Determinant(Vector2 a, Vector2 b);

struct Vector3{
	float x;
	float y;
	float w;
	// w = 1 is point vector, w = 0 is free vector


	Vector3();
	Vector3(float Px, float Py, float Pw);
	Vector3 operator*(float scalar);
	Vector3 operator/(float scalar);
	Vector3 operator+(Vector3 other);
	Vector3 operator-(Vector3 other);
	float Magnitude();
	float Dot(Vector3 other);
	Vector3 Normalize();

};

struct Vector4{
	float x;
	float y;
	float z;
	float w;

	Vector4();
	Vector4(float Px, float Py, float Pz, float Pw);
	Vector4 operator*(float scalar);
	Vector4 operator+(Vector4 other);
	Vector4 operator-(Vector4 other);
	float Magnitude();
	Vector4 Normalize();
	float Dot(Vector4 other);
	Vector4 Cross(Vector4 other);
};




//

#endif