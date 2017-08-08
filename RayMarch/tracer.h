//#include <vector>
#ifndef __tracer
#define __tracer

#include <vector>
#include "myvector.h"
#include "camera.h"
#include "material.h"
#include "primitive.h"

struct Ray
{
	vec3 point;
	vec3 direction;
};

struct Hit
{
	int index;
	vec3 point;
	bool exist;

	Hit();
	Hit(vec3, int);
};

struct Light	
{
	vec3 pos;

	color Id;
	color Is;

	Light(vec3, vec3, vec3);
};

class Scene
{
	int rec;
	float eps;
	color ambientCol;
	Box boundaryBox;
	Camera cam;
	std::vector<MyPrimitive*> objects;
	std::vector<Light*> lights;

	Hit Intersect(const Ray &, int);
	vec3 Raytrace(const Ray &);
	bool Visible(vec3, vec3);
	color Shade(vec3, MyPrimitive*, vec3, Light*, vec3);
	color ShadeAmbient(MyPrimitive*);

public:
	Scene(float, color);
	void setCam(vec3, vec3, vec3, float, float);
	void setBox(float, float, float);

	void addObject(vec3);
	void addSphere(vec3, float, Material);
	void addBox(vec3, float, float, float, Material);
	void addRoundBox(vec3, vec3, float, Material);
	void addPlane(vec4, Material);
	void addTorus(vec3, float, float, Material);
	// ����� ��� ��������� ��������� � ��� ���� ��������� ��������
	// Union ���� mode = 0
	// Substraction ���� = 1
	// Intersection ���� ����� ������
	void addBoolean(int);

	void addLight(vec3, vec3, vec3);
	void Draw(System::Drawing::Bitmap^);
};

#endif // __tracer