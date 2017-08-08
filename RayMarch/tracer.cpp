#include "stdafx.h"
#include <cmath>
#include <vector>
#include "tracer.h"

Light::Light(vec3 Id, vec3 Is, vec3 pos)
{
	this->Id = Id;
	this->Is = Is;
	this->pos = pos;
}
Hit::Hit()
{
	exist = false;
}
Hit::Hit(vec3 point, int index)
{
	this->index = index;
	this->point = point;
	exist = true;
}

void Scene::addLight(vec3 Id, vec3 Is, vec3 pos)
{
	lights.push_back(new Light(Id, Is, pos));
}

void Scene::addSphere(vec3 pos, float rad, Material mat)
{
	objects.push_back(new Sphere(pos, rad, mat));
}

void Scene::addBox(vec3 pos, float a, float b, float c, Material mat)
{
	objects.push_back(new Box(pos, a, b, c, mat));
}

void Scene::addRoundBox(vec3 pos, vec3 size, float rad, Material mat)
{
	objects.push_back(new RoundBox(pos, size, rad, mat));
}
void Scene::addPlane(vec4 coeffs, Material mat)
{
	objects.push_back(new Plane(coeffs, mat));
}
void Scene::addTorus(vec3 pos, float rad1, float rad2, Material mat)
{
	objects.push_back(new Torus(pos, rad1, rad2, mat));
}

void Scene::addBoolean(int mode)
{
	MyPrimitive *obj1 = objects[objects.size()-2];
	MyPrimitive *obj2 = objects[objects.size()-1];
	Material mat = objects[objects.size()-2]->Mat;
	objects.pop_back();
	objects.pop_back();
	objects.push_back(new Boolean(mode, mat, obj1, obj2));
}

void Scene::setBox(float a, float b, float c)
{
	boundaryBox.a = a;
	boundaryBox.b = b;
	boundaryBox.c = c;
}

void Scene::setCam(vec3 pos, vec3 dir, vec3 up, float dist, float ps)
{
	cam = Camera(pos, dir, up);
	cam.distance = dist;
	cam.pixelSize = ps;
}

color Scene::ShadeAmbient(MyPrimitive *obj)
{
	color col;

	col.x = ambientCol.x*obj->Mat.Ka.x;
	col.y = ambientCol.y*obj->Mat.Ka.y;
	col.z = ambientCol.z*obj->Mat.Ka.z;

	return col;
}

color Scene::Shade(vec3 normal, MyPrimitive* obj, vec3 lDir, Light* light, vec3 point)
{
	color col;

	vec3 viewerDir = cam.position - point;
	if (viewerDir.length() != 0)
		viewerDir = viewerDir.normalize();
	else
		return col;

	vec3 reflDir = normal*2*vec3::dot(normal, lDir) - lDir;

	float cos1 = vec3::dot(normal, lDir);
	if (cos1 < 0)
		cos1 = 0;
	float cos2 = vec3::dot(reflDir, viewerDir);
	if (cos2 < 0)
		cos2 = 0;
	else
		cos2 = (float)pow(cos2, obj->Mat.alpha);

	col.x = /*ambientCol.x*obj->Mat.Ka.x + \*/
		light->Id.x*obj->Mat.Kd.x*cos1 + \
		light->Is.x*obj->Mat.Ks.x*cos2;

	col.y = /*ambientCol.y*obj->Mat.Ka.y + \*/
		light->Id.y*obj->Mat.Kd.y*cos1 + \
		light->Is.y*obj->Mat.Ks.y*cos2;

	col.z = /*ambientCol.z*obj->Mat.Ka.z + \*/
		light->Id.z*obj->Mat.Kd.z*cos1 + \
		light->Is.z*obj->Mat.Ks.z*cos2;

	return col;
}

Hit Scene::Intersect(const Ray &ray, int exc = -1)
{
	vec3 currPoint = ray.point;
	int size = objects.size();
	int index;
	float distance = 10000;
	float min, temp;

	for (int i = 0; i < size; ++i)
	{
		if (objects[i]->Primitive(currPoint) < eps)
		{
			while (objects[i]->Primitive(currPoint) < eps)
			{
				currPoint = currPoint + ray.direction*eps;
			}
		}
	}
	//
	while(distance > eps)
	{
		min = 10000;
		for (int i = 0; i < size; ++i)
		{
			if (exc == i)
				continue;
			if (((temp = objects[i]->Primitive(currPoint)) < min))
			{
				min = temp;
				index = i;
			}
		}
		distance = min;

		currPoint = currPoint + ray.direction*min; 

		if (boundaryBox.Primitive(currPoint) > 0)
			return Hit();
	}
	return Hit(currPoint, index);
}

vec3 Scene::Raytrace(const Ray &ray)
{
	color col(0,0,0);
	vec3 lightDir;
 
	Hit hit = Intersect(ray);

	if (hit.exist == false)
		return color(0.0f, 0.0f, 0.0f);
 
	for(unsigned int i = 0; i < lights.size(); ++i)
		if(Visible(hit.point, lights[i]->pos))
		{
			lightDir = lights[i]->pos - hit.point;
			lightDir.normalize();
			col += Shade(objects[hit.index]->Normal(hit.point), objects[hit.index], lightDir, lights[i], hit.point); 
		}

	float refl = objects[hit.index]->Mat.refl;
	if (refl > 0)
	{
		vec3 normal = objects[hit.index]->Normal(hit.point);
		Ray rayRefl;
		vec3 viewerDir = (ray.direction - hit.point).normalize();
		vec3 reflDir = normal*2*vec3::dot(normal, viewerDir) - viewerDir;
		rayRefl.direction = reflDir;
		rayRefl.point = hit.point;

		rec++;
		if (rec > 4)
			return col;
		col = col*(1 - refl) + Raytrace(rayRefl)*refl;
	}

	col += ShadeAmbient(objects[hit.index]);

	col.crop();

    return col;
}

bool Scene::Visible(vec3 point, vec3 lightPos)
{
	Ray ray;
	ray.point = lightPos;
	vec3 dir = vec3(point.x - lightPos.x, point.y - lightPos.y, point.z - lightPos.z);
	ray.direction = dir.normalize();
	Hit hit = Intersect(ray);
	if ((hit.point - point).length() < eps*10)
		return true;
	else
		return false;
}
Scene::Scene(float eps, color amb)
{
	this->eps = eps;
	ambientCol = amb;
}

void Scene::Draw(System::Drawing::Bitmap ^bmp)
{
	Ray ray;
	color pixelColor;

	//
	color pc1, pc2, pc3, pc4;
	vec3 pixelAA;
	//

	ray.point = cam.position;
	int wid = bmp->Width;
	int hei = bmp->Height;
	vec3 pixel;
	vec3 upperLeftPixel = cam.direction*cam.distance - \
		cam.downScreen*(float)(hei/2)*cam.pixelSize - cam.rightScreen*(float)(wid/2)*cam.pixelSize;
	for (int j = 0; j < hei; ++j)
		for (int i = 0; i < wid; ++i)
		{
			rec = 0;
			pixel = upperLeftPixel + \
				cam.downScreen*(float)j*cam.pixelSize + cam.rightScreen*(float)i*cam.pixelSize;
			//ray.direction = (pixel - cam.position).normalize();
			//pixelColor = Raytrace(ray);

			///* anti-aliasing
			pixelAA = pixel - cam.downScreen*(cam.pixelSize/4) - cam.rightScreen*(cam.pixelSize/4);
			ray.direction = (pixelAA - cam.position).normalize();
			pc1 = Raytrace(ray);
			pixelAA = pixel - cam.downScreen*(cam.pixelSize/4) + cam.rightScreen*(cam.pixelSize/4);
			ray.direction = (pixelAA - cam.position).normalize();
			pc2 = Raytrace(ray);
			pixelAA = pixel + cam.downScreen*(cam.pixelSize/4) - cam.rightScreen*(cam.pixelSize/4);
			ray.direction = (pixelAA - cam.position).normalize();
			pc3 = Raytrace(ray);
			pixelAA = pixel + cam.downScreen*(cam.pixelSize/4) + cam.rightScreen*(cam.pixelSize/4);
			ray.direction = (pixelAA - cam.position).normalize();
			pc4 = Raytrace(ray);
			pixelColor = (pc1 + pc2 + pc3 + pc4)/4;
			// anti-aliasing */

			bmp->SetPixel(i, j, \
			System::Drawing::Color::FromArgb( \
			(unsigned char)(pixelColor.x*255), \
			(unsigned char)(pixelColor.y*255), \
			(unsigned char)(pixelColor.z*255)));
		}
}