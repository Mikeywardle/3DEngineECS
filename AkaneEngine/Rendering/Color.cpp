#include "Color.h"

Color Color::Black = Color(0.f,0.f,0.f,1.f);
Color Color::White = Color(1.f, 1.f, 1.f, 1.f);
Color Color::Red = Color(1.f, 0.f, 0.f, 1.f);
Color Color::Blue = Color(0.f, 0.f, 1.f, 1.f);
Color Color::Green = Color(0.f, 1.f, 0.f, 1.f);
Color Color::Clear = Color(0.f, 0.f, 0.f, 0.f);

Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color Color::Lerp(Color a, Color b, float alpha)
{
	return Color(0.f,0.f,0.f,0.f);
}
