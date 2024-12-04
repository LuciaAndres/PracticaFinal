#pragma once

class Color
{
private:
	float red;
	float green;
	float blue;
public:
	Color() :
		red(1.0), green(1.0), blue(1.0) {}

	Color(float red, float green, float blue)
	{
		SetRed(red);
		SetGreen(green);
		SetBlue(blue);
	}
	inline float GetRed() const { return this->red; }
	inline float GetGreen() const { return this->green; }
	inline float GetBlue() const { return this->blue; }
	inline void SetRed(float& RedToSet)
	{
		if (RedToSet > 1) { RedToSet = 1; }
		else if (RedToSet < 0) { RedToSet = 0; }
		else { red = RedToSet; }
	}
	inline void SetGreen(float& GreenToSet)
	{
		if (GreenToSet > 1) { GreenToSet = 1; }
		else if (GreenToSet < 0) { GreenToSet = 0; }
		else { green = GreenToSet; }
	}
	inline void SetBlue(float& BlueToSet)
	{
		if (BlueToSet > 1) { BlueToSet = 1; }
		else if (BlueToSet < 0) { BlueToSet = 0; }
		else { blue = BlueToSet; }
	}
};



