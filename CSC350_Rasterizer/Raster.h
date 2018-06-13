
#ifndef Raster_H
#define Raster_H

#include "Color.h"
#include "Triangle2D.h"
#include "Model.h"

 class Raster{

 private:
	//Fields:
	int width;
	int height;
	Color* colorPixels;

 public:
	//Constructor
	Raster();
	Raster(int pWidth, int pHeight, Color pFillColor);

	//Destructor
	//~Raster();

	//Methods
	int GetWidth();
	int GetHeight();
	Color GetColorPixel(int pRowIndex, int pColIndex);
	void SetColorPixel(int pRowIndex, int pColIndex, Color pFillColor);
	void Clear(Color pFillColor);
	void WriteToPPM();
	void DrawLine_DDA(float pX1, float pY1, float pX2, float pY2, Color pFillColor);
	void swap(float* pX1, float* pY1, float* pX2, float* pY2);
	void DrawLine_BresenHam(float X1, float Y1, float X2, float Y2, Color pFillColor);
	void DrawLine_BresenHam_Interpolated(float X1, float Y1, float X2, float Y2, Color c1, Color c2);
	void DrawTriangle2D_DotProduct(Triangle2D t);
	void DrawLine_DDA_Interpolated(float pX1, float pY1, float pX2, float pY2, Color color1, Color color2);
	void DrawTriangle3D_Barycentric(Triangle3D t);
	void DrawModel(Model o);
};



#endif