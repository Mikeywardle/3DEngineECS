#pragma once
struct Color
{
public:
	Color();
	Color(float r, float g, float b, float a);

	float r;
	float g;
	float b;
	float a;

	static Color Lerp(Color a, Color b, float alpha);

	static Color Black;
	static Color White;
	static Color Red;
	static Color Blue;
	static Color Green;
	static Color Clear;
};

