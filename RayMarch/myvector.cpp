#include "StdAfx.h"
#include <cmath>
#include "myvector.h"

vec2::vec2()
{
	x = 0;
	y = 0;
}

vec2::vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

vec2::vec2(const vec2 &vec)
{
	x = vec.x;
	y = vec.y;
}

float vec2::length()
{
	return sqrt(x*x + y*y);
}

vec3::vec3()
{
	x = 0;
	y = 0;
	z = 0;
	xz = vec2();
}
vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	//xy = vec2(x, y);
	xz = vec2(x, z);
	//yz = vec2(y, z);
}

vec3::vec3(const vec3 &vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	xz = vec.xz;
}

float vec3::length()
{
	return sqrt(x*x + y*y + z*z);
}

float vec3::maxcomp()
{
	return x>y?(x>z?x:z):(y>z?y:z);
}

vec3 vec3::abs() const
{
	return vec3(x<0?-x:x, y<0?-y:y, z<0?-z:z);
}

vec3 vec3::max(float a)
{
	return vec3(x>a?x:a, y>a?y:a, z>a?z:a);
}

vec3 vec3::normalize()
{
	float nc = this->length();
	if (nc == 0)
	{
		System::Windows::Forms::MessageBox::Show(L"В normalize передан нулевой вектор!");
		return *this;
	}
	x /= nc;
	y /= nc;
	z /= nc;
	return *this;
}
float vec3::dot(vec3 v1, vec3 v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
vec3 vec3::operator - (const vec3 &vec) const
{
	return vec3(x - vec.x, y - vec.y, z - vec.z);
}

vec3 vec3::operator + (const vec3 &vec) const
{
	return vec3(x + vec.x, y + vec.y, z + vec.z);
}

vec3 vec3::operator += (const vec3 &vec)
{
	return vec3(x += vec.x, y += vec.y, z += vec.z);
}
vec3 vec3::operator * (const float a) const
{
	return vec3(x*a, y*a, z*a);
}

vec3 vec3::cross(vec3 a, vec3 b)
{
	return vec3(a.y*b.z - b.y*a.z, b.x*a.z - a.x*b.z, a.x*b.y - b.x*a.y);
}

vec3 vec3::operator / (const float a) const
{
	return vec3(x/a, y/a, z/a);
}

bool vec3::operator == (const vec3 &vec) const
{
	return ((x == vec.x) && (y == vec.y) && (z == vec.z));
}

void vec3::crop()
{
	if (x > 1.0)
		x = 1.0;
	else if (x < 0.0)
		x = 0.0;
	if (y > 1.0)
		y = 1.0;
	else if (y < 0.0)
		y = 0.0;
	if (z > 1.0)
		z = 1.0;
	else if (z < 0.0)
		z = 0.0;
}

vec4::vec4()
{
}

vec4::vec4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;

	xyz = vec3(x, y, z);
}

vec4 vec4::normalize()
{
	float nc = sqrt(x*x + y*y + z*z + w*w);
	if (nc == 0)
	{
		System::Windows::Forms::MessageBox::Show(L"В normalize vec4 передан нулевой вектор!");
		return *this;
	}
	x /= nc;
	y /= nc;
	z /= nc;
	w /= nc;
	return *this;	
}