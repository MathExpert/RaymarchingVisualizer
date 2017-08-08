#include "StdAfx.h"

#include "myvector.h"
#include "primitive.h"

//////////////////////////////////
////////// Constructors //////////
//////////////////////////////////

MyPrimitive::MyPrimitive()
{
	Position = vec3(0, 0, 0);
	Mat = Material();
}

Sphere::Sphere(vec3 pos, float rad, Material mat)
{
	Position = pos;
	radius = rad;
	Mat = mat;
}

Box::Box()
{
}

Box::Box(vec3 pos, float a, float b, float c, Material mat)
{
	Position = pos;
	this->a = a;
	this->b = b;
	this->c = c;
	Mat = mat;
}

RoundBox::RoundBox(vec3 pos, vec3 size, float rad, Material mat)
{
	Position = pos;
	roundRad = rad;
	this->size.x = size.x;
	this->size.y = size.y;
	this->size.z = size.z;
	Mat = mat;
}

Plane::Plane(vec4 coeffs, Material mat)
{
	this->coeffs = coeffs;
	//this->coeffs.normalize();
	Mat = mat;
}

Torus::Torus(vec3 pos, float rad1, float rad2, Material mat)
{
	Position = pos;
	radIn = rad1;
	radOut = rad2;
	Mat = mat;
}

Boolean::Boolean(int mode, Material mat, MyPrimitive *obj1, MyPrimitive *obj2)
{
	this->mode = mode;
	this->Mat = mat;
	this->obj1 = obj1;
	this->obj2 = obj2;
}

////////////////////////////////////////
////////// Distance functions //////////
////////////////////////////////////////

float Sphere::Primitive(const vec3 &point)
{
	vec3 vec = vec3(point.x - Position.x, point.y - Position.y, point.z - Position.z);
	return vec.length() - radius;
}

float Box::Primitive(const vec3 &vec)
{
	vec3 temp = vec3(a, b, c);
	vec3 di = (vec - Position).abs() - temp;
	float mc = di.maxcomp();
	return System::Math::Min(mc, di.max(0.0).length());
}

float RoundBox::Primitive(const vec3 &point)
{
	vec3 di = (point - Position).abs() - size;
	return (di.max(0.0).length()) - roundRad;
}

float Plane::Primitive(const vec3 &point)
{
	/*float a = vec3::dot(point, coeffs.xyz);
	if (a < 0)
		a = -a;
	return a + coeffs.w;*/
	vec4 b = coeffs;
	b.normalize();
	return vec3::dot(point, b.xyz) + coeffs.w;
}

float Torus::Primitive(const vec3 &point)
{
	vec3 vec = point - Position;
	vec2 q = vec2(vec.xz.length() - radIn, vec.y);
	return q.length() - radOut;
}

float Boolean::Primitive(const vec3 &point)
{
	if (mode == 0)
		return System::Math::Min(obj1->Primitive(point), obj2->Primitive(point));
	else if (mode == 1)
		return System::Math::Max(-obj1->Primitive(point), obj2->Primitive(point));
	else
		return System::Math::Max(obj1->Primitive(point), obj2->Primitive(point));
}

/////////////////////////////
////////// Normals //////////
/////////////////////////////

vec3 Sphere::Normal(const vec3 &point)
{
	vec3 normal = point;
	normal = normal - Position;
	return normal.normalize();
}

vec3 Box::Normal(const vec3 &vec)
{
	float eps = 0.01f;
	vec3 z1 = vec + vec3(eps, 0, 0);
	vec3 z2 = vec - vec3(eps, 0, 0);
	vec3 z3 = vec + vec3(0, eps, 0);
	vec3 z4 = vec - vec3(0, eps, 0);
	vec3 z5 = vec + vec3(0, 0, eps);
	vec3 z6 = vec - vec3(0, 0, eps);
 
	float dx = Primitive(z1) - Primitive(z2);
	float dy = Primitive(z3) - Primitive(z4);
	float dz = Primitive(z5) - Primitive(z6);
 
	return (vec3(dx, dy, dz) / (float)(2.0*eps)).normalize();
}

vec3 RoundBox::Normal(const vec3 &vec)
{
	float eps = 0.1f;
	vec3 z1 = vec + vec3(eps, 0, 0);
	vec3 z2 = vec - vec3(eps, 0, 0);
	vec3 z3 = vec + vec3(0, eps, 0);
	vec3 z4 = vec - vec3(0, eps, 0);
	vec3 z5 = vec + vec3(0, 0, eps);
	vec3 z6 = vec - vec3(0, 0, eps);
 
	float dx = Primitive(z1) - Primitive(z2);
	float dy = Primitive(z3) - Primitive(z4);
	float dz = Primitive(z5) - Primitive(z6);
 
	return (vec3(dx, dy, dz) / (float)(2.0*eps)).normalize();
}

vec3 Plane::Normal(const vec3 &vec)
{
	vec3 a = coeffs.xyz;
	return a.normalize();
}

vec3 Torus::Normal(const vec3 &vec)
{
	float eps = 0.1f;
	vec3 z1 = vec + vec3(eps, 0, 0);
	vec3 z2 = vec - vec3(eps, 0, 0);
	vec3 z3 = vec + vec3(0, eps, 0);
	vec3 z4 = vec - vec3(0, eps, 0);
	vec3 z5 = vec + vec3(0, 0, eps);
	vec3 z6 = vec - vec3(0, 0, eps);
 
	float dx = Primitive(z1) - Primitive(z2);
	float dy = Primitive(z3) - Primitive(z4);
	float dz = Primitive(z5) - Primitive(z6);
 
	return (vec3(dx, dy, dz) / (float)(2.0*eps)).normalize();
}

vec3 Boolean::Normal(const vec3 &vec)
{
	float eps = 0.1f;
	vec3 z1 = vec + vec3(eps, 0, 0);
	vec3 z2 = vec - vec3(eps, 0, 0);
	vec3 z3 = vec + vec3(0, eps, 0);
	vec3 z4 = vec - vec3(0, eps, 0);
	vec3 z5 = vec + vec3(0, 0, eps);
	vec3 z6 = vec - vec3(0, 0, eps);
 
	float dx = Primitive(z1) - Primitive(z2);
	float dy = Primitive(z3) - Primitive(z4);
	float dz = Primitive(z5) - Primitive(z6);
 
	return (vec3(dx, dy, dz) / (float)(2.0*eps)).normalize();
}