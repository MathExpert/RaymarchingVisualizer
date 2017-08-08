#ifndef __camera
#define __camera

#include "myvector.h"

struct Camera
{
	vec3 position;
	vec3 direction;
	vec3 up;

	float distance;
	vec3 downScreen;
	vec3 rightScreen;

	float pixelSize;

	Camera();
	Camera(vec3, vec3, vec3);
};

#endif // __camera