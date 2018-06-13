#include "Raster.h"
#include <fstream>
#include <math.h>
#include <iostream>
using namespace std;

Raster::Raster(){
	width = 0;
	height = 0;
	colorPixels = NULL;
}


Raster::Raster(int pWidth, int pHeight, Color pFillColor){
	width = pWidth;
	height = pHeight;
	colorPixels = new Color[width*height];

	for (int i = 0; i < width*height; i++)
	{
		colorPixels[i] = pFillColor;
	}
}

/*
Raster::~Raster(){
	delete[] colorPixels;	
}
*/

int Raster::GetWidth(){
	return width;

}
int Raster::GetHeight(){
	return height;
}
Color Raster::GetColorPixel(int pRowIndex, int pColIndex){
	int thisIndex =  ((height - 1 - pRowIndex) * width) + pColIndex ;
	return colorPixels[thisIndex];

}

void Raster::SetColorPixel(int pRowIndex, int pColIndex, Color pFillColor){
	int thisIndex = ((height - 1 - pRowIndex) * width) + pColIndex;
	colorPixels[thisIndex] = pFillColor;
}

void Raster::Clear(Color pFillColor){
	for (int i = 0; i < width*height; i++)
	{
		colorPixels[i] = pFillColor;
	}
}

void Raster::WriteToPPM(){
	ofstream oFile;
	oFile.open("FRAME_BUFFER.ppm");
	oFile << "P3" << endl;
	oFile << width << " " << height << endl;
	oFile << "255" << endl;


	int count = 0;
	int r, g, b, a;
	for (int i = 0; i < width*height; i++){
		colorPixels[i].GetIntegerChannels(&r,&g, &b, &a);
		oFile << r << " " << g << " " << b << " ";
		count++;
		if (count % width == 0){
			oFile << endl;
		}
	}
	oFile.flush();
	oFile.close();

	/*for (int j = 1; j < width; j++){
	int count = 0;
		for (int i = (width*height) - (j * width); i < width*height - (count * width); i++){
			oFile << colorPixels[i].red << " " << colorPixels[i].green << " " << colorPixels[i].blue;
		}
	oFile << endl;
	count++;
		}
		*/

	}

void Raster::swap(float* pX1, float* pY1, float* pX2, float* pY2){
	float* tempx1 = pX1;
	float* tempy1 = pY1;
	pX1 = pX2;
	pX2 = tempx1;
	pY1 = pY2;
	pY2 = tempy1;
}

void Raster::DrawLine_DDA(float pX1, float pY1, float pX2, float pY2, Color pFillColor){
	if (pX2 < pX1 || (pX1 == pX2 && pY1 > pY2) ){
		float tempx1 = pX1;
		float tempy1 = pY1;
		pX1 = pX2;
		pX2 = tempx1;
		pY1 = pY2;
		pY2 = tempy1;
	}

	float m = (pY2 - pY1) / (pX2 - pX1);
	float m2 = (pX2 - pX1) / (pY2 - pY1);

	//vertical
	if (m2 == 0){
		float x = pX2;
		for (int y = pY1; y <= pY2; y++){
			SetColorPixel(y, round(x), pFillColor);
			x += m2;
		}
	}
	//horizontal
	else if (m == 0){
		float y = pY1;
		for (int x = pX1; x <= pX2; x++){
			SetColorPixel(round(y), x, pFillColor);
			y += m;
		}
	}
	//Slope is not too steep
	else if (m <= 1 && m >= -1){
		float y = pY1;
		for (int x = pX1; x <= pX2; x++){
			SetColorPixel(round(y), x, pFillColor);
			y += m;
		}

	}
	//Slope is very positive
	else if (m > 1){
		float x = pX1;
		for (int y = pY1; y <= pY2; y++){
			SetColorPixel(y, round(x), pFillColor);
			x += m2;
		}
	}
	//if it's very negative
	else if (m < -1){
		float x = pX1;
		for (int y = pY1; y > pY2; y--){
			SetColorPixel(y, round(x), pFillColor);
			x -= m2;
		}
	}




}

void Raster::DrawLine_BresenHam(float X1, float Y1, float X2, float Y2, Color pFillColor){
	int deltax = X2 - X1;
	int deltay = Y2 - Y1;
	int implicit = 2 * (-deltay) + deltax;

	int y = Y1;

	for (int x = X1; x <= X2; x++){

		SetColorPixel(y, x, pFillColor);
		if (implicit < 0){
			implicit += (2 * -deltay + deltax);
			y++;
		}
		else{
			implicit += (2 * -deltay);
		}

	}
}

void Raster::DrawLine_BresenHam_Interpolated(float X1, float Y1, float X2, float Y2, Color c1, Color c2){

	int deltax = X2 - X1;
	int deltay = Y2 - Y1;
	int implicit = 2 * (-deltay) + deltax;


	Vector2 start(X1, Y1);
	Vector2 end(X2, Y2);
	Vector2 fullVec = end - start;
	float fullMag = fullVec.Magnitude();

	int y = Y1;
	for (int x = X1; x <= X2; x++){
	
		Vector2 P(x, y);
		Vector2 currentVec = P - start;
		float currentMag = currentVec.Magnitude();
		float percentage = currentMag / fullMag;

		Color c = c2 * percentage + (c1 * (1.0 - percentage));

		SetColorPixel(y, x, c1);
		if (implicit < 0){
			implicit += (2 * -deltay + deltax);
			y++;
		}
		else{
			implicit += (2 * -deltay);
		}

	}



}

void Raster::DrawLine_DDA_Interpolated(float pX1, float pY1, float pX2, float pY2, Color color1, Color color2){


	if (pX2 < pX1 || (pX1 == pX2 && pY1 > pY2)){
		float tempx1 = pX1;
		float tempy1 = pY1;
		pX1 = pX2;
		pX2 = tempx1;
		pY1 = pY2;
		pY2 = tempy1;
		Color tempcolor = color1;
		color1 = color2;
		color2 = tempcolor;
	}

	float m = (pY2 - pY1) / (pX2 - pX1);
	float m2 = (pX2 - pX1) / (pY2 - pY1);

	Vector2 v1 = Vector2(pX1, pY1);
	Vector2 v2 = Vector2(pX2, pY2);
	Vector2 wholeline = v2 - v1;
	Vector2 P(pX1, pY1);
	Vector2 toP = P - v1;
	float wholelineMag = wholeline.Magnitude();
	float toPMag = toP.Magnitude();
	float ratio = toPMag / wholelineMag;
	Color interpolatedColor = color1 * (1.0 - ratio) + color2 * (ratio);


	//vertical
	if (m2 == 0){
		float x = pX2;
		for (int y = pY1; y <= pY2; y++){
			P = Vector2(x, y);
			toP = P - v1;
			toPMag = toP.Magnitude();
			ratio = toPMag / wholelineMag;
			interpolatedColor = color1 * (1.0 - ratio) + color2 * (ratio);
			SetColorPixel(y, round(x), interpolatedColor);
			x += m2;
		}
	}
	//horizontal
	else if (m == 0){
		float y = pY1;
		for (int x = pX1; x <= pX2; x++){
			P = Vector2(x, y);
			toP = P - v1;
			toPMag = toP.Magnitude();
			ratio = toPMag / wholelineMag;
			interpolatedColor = color1 * (1.0 - ratio) + color2 * (ratio);
			SetColorPixel(round(y), x, interpolatedColor);
			y += m;
		}
	}
	//Slope is not too steep
	else if (m <= 1 && m >= -1){
		float y = pY1;
		for (int x = pX1; x <= pX2; x++){
			P = Vector2(x, y);
			toP = P - v1;
			toPMag = toP.Magnitude();
			ratio = toPMag / wholelineMag;
			interpolatedColor = color1 * (1.0 - ratio) + color2 * (ratio);
			SetColorPixel(round(y), x, interpolatedColor);
			y += m;
		}

	}
	//Slope is very positive
	else if (m > 1){
		float x = pX1;
		for (int y = pY1; y <= pY2; y++){
			P = Vector2(x, y);
			toP = P - v1;
			toPMag = toP.Magnitude();
			ratio = toPMag / wholelineMag;
			interpolatedColor = color1 * (1.0 - ratio) + color2 * (ratio);
			SetColorPixel(y, round(x), interpolatedColor);
			x += m2;
		}
	}
	//if it's very negative
	else if (m < -1){
		float x = pX1;
		for (int y = pY1; y > pY2; y--){
			P = Vector2(x, y);
			toP = P - v1;
			toPMag = toP.Magnitude();
			ratio = toPMag / wholelineMag;
			interpolatedColor = color1 * (1.0 - ratio) + color2 * (ratio);
			SetColorPixel(y, round(x), interpolatedColor);
			x -= m2;
		}
	}

}

void Raster::DrawTriangle2D_DotProduct(Triangle2D t){
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			Vector2 p = Vector2(x, y);
			
			Vector2 e0 = t.v1 - t.v0;
			Vector2 e0Perp = e0.Perpendicular();
			Vector2 g0 = p - t.v0; //Line from v0 to P
			float result0 = e0Perp.Dot(g0);

			Vector2 e1 = t.v2 - t.v1;
			Vector2 e1Perp = e1.Perpendicular();
			Vector2 g1 = p - t.v1; //Line from v1 to P
			float result1 = e1Perp.Dot(g1);

			Vector2 e2 = t.v0 - t.v2;
			Vector2 e2Perp = e2.Perpendicular();
			Vector2 g2 = p - t.v2; //Line from v2 to P
			float result2 = e2Perp.Dot(g2);

			if (result0 >= 0 && result1 >= 0 && result2 >= 0){
				SetColorPixel(y, x, t.c0);
			}

		}
	}



}

void Raster::DrawTriangle3D_Barycentric(Triangle3D t){

	Triangle2D myT(t);

	int xmin = t.v0.x;
	if (xmin > t.v1.x)
		xmin = t.v1.x;
	if (xmin > t.v2.x)
		xmin = t.v2.x;

	int xmax = t.v0.x;
	if (xmax < t.v1.x)
		xmax = t.v1.x;
	if (xmax < t.v2.x)
		xmax = t.v2.x;

	int ymin = t.v0.y;
	if (ymin > t.v1.y)
		ymin = t.v1.y;
	if (ymin > t.v2.y)
		ymin = t.v2.y;

	int ymax = t.v0.y;
	if (ymax < t.v1.y)
		ymax = t.v1.y;
	if (ymax < t.v2.y)
		ymax = t.v2.y;
	if (xmin < 0){
		xmin = 0;
	}
	if (xmax > height){
		xmax = height;
	}

	if (ymin < 0){
		ymin = 0;
	}
	if (ymax > height){
		ymax = height;
	}

	for (int x = xmin; x <= xmax; x++){
		for (int y = ymin; y <= ymax; y++){

			float lambda1;
			float lambda2;
			float lambda3;
			Vector2 p = Vector2(x, y);
			myT.CalculateBarycentricCoordinates(p, lambda1, lambda2, lambda3);
			Color interpolatedcolor = t.c0 * lambda1 + t.c1 * lambda2 + t.c2 * lambda3;
			//Color interpolatedcolor = lambda1 * t.c0 + t.c1 + t.c2;
			//cout << "lambda1 :" << lambda1 << " " << lambda2 << " " << lambda3 << endl;



			if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0){
				SetColorPixel(y, x, interpolatedcolor);
			}

		}
	}
	
}

void Raster::DrawModel(Model mod){
	for (int i = 0; i < mod.NumTriangles(); i++){
		DrawTriangle3D_Barycentric(mod[i]);
	}
}