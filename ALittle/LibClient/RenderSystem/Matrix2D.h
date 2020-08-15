
#ifndef _ALITTLE_MATRIX3D_H_
#define _ALITTLE_MATRIX3D_H_

#include <math.h>
#include <memory>

namespace ALittle
{

class Matrix2D
{
public:
	Matrix2D() { SetIdentity(); }

public:
	Matrix2D& SetIdentity()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;

		return *this;
	}

	Matrix2D& SetRotate(float rad)
	{
		m[0][0] = static_cast<float>(cos(rad)); m[0][1] = static_cast<float>(sin(rad));	m[0][2] = 0.0f;
		m[1][0] = -m[0][1]; m[1][1] = m[0][0];	m[1][2] = 0.0f;
		m[2][0] = 0.0f;		m[2][1] = 0.0f;		m[2][2] = 1.0f;

		return *this;
	}

	Matrix2D& Rotate(float rad)
	{
		Matrix2D m; m.SetRotate(rad);
		return Multiply(m);
	}

	Matrix2D& SetTranslation(float x, float y)
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
		m[2][0] = x;	m[2][1] = y;	m[2][2] = 1.0f;

		return *this;
	}

	Matrix2D& Translation(float x, float y)
	{
		Matrix2D m; m.SetTranslation(x, y);
		return Multiply(m);
	}

	Matrix2D& SetScale(float x, float y)
	{
		m[0][0] = x;	m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = y;	m[1][2] = 0.0f;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;

		return *this;
	}

	Matrix2D& Scale(float x, float y)
	{
		Matrix2D m; m.SetScale(x, y);
		return Multiply(m);
	}

public:
	Matrix2D& Multiply(const Matrix2D& right)
	{
		float r[3][3];

		r[0][0] = m[0][0] * right.m[0][0] + m[0][1] * right.m[1][0] + m[0][2] * right.m[2][0];
		r[0][1] = m[0][0] * right.m[0][1] + m[0][1] * right.m[1][1] + m[0][2] * right.m[2][1];
		r[0][2] = m[0][0] * right.m[0][2] + m[0][1] * right.m[1][2] + m[0][2] * right.m[2][2];

		r[1][0] = m[1][0] * right.m[0][0] + m[1][1] * right.m[1][0] + m[1][2] * right.m[2][0];
		r[1][1] = m[1][0] * right.m[0][1] + m[1][1] * right.m[1][1] + m[1][2] * right.m[2][1];
		r[1][2] = m[1][0] * right.m[0][2] + m[1][1] * right.m[1][2] + m[1][2] * right.m[2][2];

		r[2][0] = m[2][0] * right.m[0][0] + m[2][1] * right.m[1][0] + m[2][2] * right.m[2][0];
		r[2][1] = m[2][0] * right.m[0][1] + m[2][1] * right.m[1][1] + m[2][2] * right.m[2][1];
		r[2][2] = m[2][0] * right.m[0][2] + m[2][1] * right.m[1][2] + m[2][2] * right.m[2][2];

		memcpy(m, r, sizeof(float) * 9);

		return *this;
	}

public:
	float m[3][3];
};

class Vector2D
{
public:
	Vector2D() : x(0.0f), y(0.0f) {}
	Vector2D(float xx, float yy) : x(xx), y(yy) {}
	~Vector2D() {}

public:
	Vector2D& Multiply(const Matrix2D& right)
	{
		float xx = x * right.m[0][0] + y * right.m[1][0] + 1 * right.m[2][0];
		float yy = x * right.m[0][1] + y * right.m[1][1] + 1 * right.m[2][1];

		x = xx; y = yy;

		return *this;
	}

public:
	float x, y;
};

class Color4
{
public:
	Color4() : r(255), g(255), b(255), a(255) {}

	bool operator == (const Color4& rr)
	{
		return r == rr.r && g == rr.g && b == rr.b && a == rr.a;
	}

	bool operator != (const Color4& rr)
	{
		return r != rr.r || g != rr.g || b != rr.b || a != rr.a;
	}

public:
	unsigned char r, g, b, a;
};

} // ALittle

#endif // _ALITTLE_MATRIX3D_H_
