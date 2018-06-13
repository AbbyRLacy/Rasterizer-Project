#ifndef Color_H
#define Color_H
// ==============================================================================
// Floating-Point-based Color (used within our program)

struct Color{

	// Fields/Attributes
	float red;
	float green;
	float blue;
	float alpha;

	// Constructors
	Color();
	Color(float pRed, float pGreen, float pBlue, float pAlpha);

	//Destructor
	//~Color();

	// Methods
	void GetIntegerChannels(int* pRed, int* pGreen, int* pBlue, int* pAlpha);
	void Clamp();

	// Operators
	Color operator*(float scalar);
	Color operator/(float scalar);
	Color operator+(Color c);
	Color operator-(Color c);
	Color operator*(Color c);

};

// Default colors
#define ColorRed Color(1.0, 0.0, 0.0, 1.0)
#define ColorGreen Color(0.0, 1.0, 0.0, 1.0)
#define ColorBlue Color(0.0,0.0,1.0,1.0)
#define ColorBlack Color(0.0,0.0,0.0,1.0)
#define ColorWhite Color(1.0,1.0,1.0,1.0)
#define ColorClear Color(0.0,0.0,0.0,0.0)


#endif
