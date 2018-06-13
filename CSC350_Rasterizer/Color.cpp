#include "Color.h"
#include <math.h>
// =================================================================================================
/*
	Name: 
		Default constructor
	Description: 
		Constructs a color object with default channel values/intensities (i.e., 0.0)
	Parameters: 
		No parameters (default constructor)
	Returns: 
		A new color object
*/

Color::Color(){
	red = 0.0;
	green = 0.0;
	blue = 0.0;
	alpha = 0.0;
}

// =================================================================================================
/*
	Name: 
		Constructor with user-defined values
	Description: 
		Constructs a color object with user-defined channel values/intensities (i.e., values
		between 0.0 and 1.0). Performs a Clamp( ) to ensure legal values afterwards.
	Parameters: 
		pRed = the user-defined intensity for the red channel (value between 0.0 and 1.0)
		pGreen = the user-defined intensity for the green channel (value between 0.0 and 1.0)
		pBlue = the user-defined intensity for the blue channel (value between 0.0 and 1.0)
		pAlpha = the user-defined intensity for the blue channel (value between 0.0 and 1.0)
	Returns: 
		A new color object
*/

Color::Color(float pRed, float pGreen, float pBlue, float pAlpha){
	red = pRed;
	green = pGreen;
	blue = pBlue;
	alpha = pAlpha;
	Clamp(); // Ensure channel intensities are valid
}

// =================================================================================================
/*
	Name:
		GetIntegerChannels( )
	Description:
		Converts the float-based channel intensities (values between 0.0 and 1.0) to integers whose
		intensity values are between 0 and 255
	Parameters:
		pRed = a pointer to an int to store the red channel intensity (value between 0 and 255)
		pGreen = a pointer to an int to store the green channel intensity (value between 0 and 255)
		pBlue = a pointer to an int to store the blue channel intensity (value between 0 and 255)
		pAlpha = a pointer to an int to store the alpha channel intensity (value between 0 and 255)
	Returns:
		None
*/

void Color::GetIntegerChannels(int* pRed, int* pGreen, int* pBlue, int* pAlpha){
	*pRed = red * 255;
	*pGreen = green * 255;
	*pBlue = blue * 255;
	*pAlpha = alpha * 255;
}

// =================================================================================================
/*
	Name:
		Clamp( )
	Description:
		Ensures that the color channels are valid/legal float values (i.e., between 0.0 and 1.0)
	Parameters:
		None
	Returns:
		None
*/

void Color::Clamp(){
	red = fmax(float(0.0), fmin(red, float(1.0)));
	green = fmax(float(0.0), fmin(green, float(1.0)));
	blue = fmax(float(0.0), fmin(blue, float(1.0)));
	alpha = fmax(float(0.0), fmin(alpha, float(1.0)));
}

// =================================================================================================
/*
	Name:
		Color-float multiplication/scaling (*) operator
	Description:
		Creates a new color whose channel intensities have been multiplied by a user-defined amount
	Parameters:
		scalar = the value that each channel intensity should be "scaled" (i.e., multiplied) by
	Returns:
		A new color object whose intensities have been multiplied by scalar
*/
Color Color::operator*(float scalar){
	Color newColor(red, green, blue, alpha);
	newColor.red *= scalar;
	newColor.green *= scalar;
	newColor.blue *= scalar;
	newColor.alpha *= scalar;
	newColor.Clamp(); // Ensure channel intensities are valid
	return newColor;
}
// =================================================================================================
/*
	Name:
		Color-float division/scaling (/) operator
	Description:
		Creates a new color whose channel intensities have been divided by a user-defined amount
	Parameters:
		scalar = the value that each channel intensity should be "scaled" (i.e., divided) by
	Returns:
		A new color object whose intensities have been divided by scalar
*/
Color Color::operator/(float scalar){
	Color newColor(red, green, blue, alpha);
	newColor.red /= scalar;
	newColor.green /= scalar;
	newColor.blue /= scalar;
	newColor.alpha /= scalar;
	newColor.Clamp(); // Ensure channel intensities are valid
	return newColor;
}
// =================================================================================================
/*
	Name:
		Color-Color addition (+) operator
	Description:
		Adds two colors together and returns a new color whose channel intensities have been summed together
	Parameters:
		c = a Color object whose channel intensities should be added to this Color object's channel intensities
	Returns:
		A new color object whose intensities have been added together
*/
Color Color::operator+(Color c){
	Color newColor(red, green, blue, alpha);
	newColor.red += c.red;
	newColor.green += c.green;
	newColor.blue += c.blue;
	newColor.alpha += c.alpha;
	newColor.Clamp(); // Ensure channel intensities are valid
	return newColor;
}
// =================================================================================================
/*
	Name:
		Color-Color subtraction (-) operator
	Description:
		Subtracts two colors from one another and returns the resulting new color
	Parameters:
		c = a Color object whose channel intensities should be subtracted FROM this Color object's channel intensities
	Returns:
		A new color object whose intensities are the result of subtracting Color c's intensities from this color
*/
Color Color::operator-(Color c){
	Color newColor(red, green, blue, alpha);
	newColor.red -= c.red;
	newColor.green -= c.green;
	newColor.blue -= c.blue;
	newColor.alpha -= c.alpha;
	newColor.Clamp(); // Ensure channel intensities are valid
	return newColor;
}
// =================================================================================================
/*
	Name:
		Color-Color multiplication (*) operator
	Description:
		Multiplies two colors together and returns the resulting new color
	Parameters:
		c = a Color object whose channel intensities should be multiplied with this Color object's channel intensities
	Returns:
		A new color object whose intensities are the product of this color's intensities and Color c's intensities
*/
Color Color::operator*(Color c){
	Color newColor(red, green, blue, alpha);
	newColor.red *= c.red;
	newColor.green *= c.green;
	newColor.blue *= c.blue;
	newColor.alpha *= c.alpha;
	newColor.Clamp(); // Ensure channel intensities are valid
	return newColor;
}
// =================================================================================================

