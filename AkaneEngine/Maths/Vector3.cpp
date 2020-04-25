#include "Vector3.h"

const Vector3 Vector3::FORWARD = Vector3(1,0,0);
const Vector3 Vector3::RIGHT = Vector3(0, 0, 1);
const Vector3 Vector3::UP = Vector3(0, 1, 0);
const Vector3 Vector3::ZERO = Vector3(0, 0, 0);


Vector3::Vector3()
{}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


float Vector3::Dot(Vector3 a, Vector3 b)
{
	return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
}

Vector3 Vector3::Coss(Vector3 a, Vector3 b)
{
	Vector3 result = Vector3();

	result.x = (a.y*b.z)-(a.z*b.y);
	result.y = (a.z*b.x)-(a.x*b.z);
	result.z = (a.x*b.y)-(a.y*b.x);

	return result;
}

Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float alpha)
{
	return (a*(1-alpha))+(b*alpha);
}

Vector3 Vector3::operator + (Vector3 b)
{
	return Vector3(x+b.x, y+b.y, z+b.z);
}

Vector3 Vector3::operator - (Vector3 b)
{
	return Vector3(x - b.x, y - b.y, z - b.z);
}

Vector3 Vector3::operator*(float b)
{
	return Vector3(x * b, y * b, z * b);
}
