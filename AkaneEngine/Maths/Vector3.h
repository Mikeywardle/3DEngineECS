#pragma once
#define AKANEENGINE_API __declspec(dllexport)

struct AKANEENGINE_API Vector3
{
	Vector3();
	Vector3(float x, float y, float z);

	static const Vector3 FORWARD;
	static const Vector3 RIGHT;
	static const Vector3 UP;
	static const Vector3 ZERO;

	static float Dot(Vector3 a, Vector3 b);
	static Vector3 Coss(Vector3 a, Vector3 b);
	static Vector3 Lerp(Vector3 a, Vector3 b, float alpha);

	float x;
	float y;
	float z;

	Vector3 operator+(Vector3 b);
	Vector3 operator-(Vector3 b);
	Vector3 operator*(float b);
};

