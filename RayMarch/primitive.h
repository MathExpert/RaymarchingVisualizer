#ifndef __primitive
#define __primitive

#include "material.h"

struct MyPrimitive
{
	vec3 Position;
	Material Mat;

	MyPrimitive();
	virtual float Primitive(const vec3 &) = 0;
	virtual vec3 Normal(const vec3 &) = 0; 
};

struct Sphere: MyPrimitive
{
	float radius;

	Sphere(vec3, float, Material);
	float Primitive(const vec3 &);
	vec3 Normal(const vec3 &);
};

struct Box: MyPrimitive
{
	float a;
	float b;
	float c;

	Box();
	Box(vec3, float, float, float, Material);
	float Primitive(const vec3 &);
	vec3 Normal(const vec3 &);
};

struct RoundBox: MyPrimitive
{
	vec3 size;
	float roundRad;

	RoundBox(vec3, vec3, float, Material);
	float Primitive(const vec3 &);
	vec3 Normal(const vec3 &);
};

struct Plane: MyPrimitive
{
	vec4 coeffs;

	Plane(vec4, Material);
	float Primitive(const vec3 &);
	vec3 Normal(const vec3 &);
};

struct Torus: MyPrimitive
{
	float radIn, radOut;

	Torus(vec3, float, float, Material);
	float Primitive(const vec3 &);
	vec3 Normal(const vec3 &);
};

struct Boolean: MyPrimitive
{
	int mode;
	MyPrimitive *obj1;
	MyPrimitive *obj2;

	Boolean(int, Material, MyPrimitive *, MyPrimitive *);
	float Primitive(const vec3 &);
	vec3 Normal(const vec3 &);
};

#endif // __primitive