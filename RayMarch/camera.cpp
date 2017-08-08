#include "StdAfx.h"
#include "camera.h"

#include "myvector.h"

Camera::Camera()
{
}

Camera::Camera(vec3 pos, vec3 dir, vec3 upv)
{
	position = pos;
	direction = (dir - pos).normalize();
	up = upv.normalize();
	up = up - direction*vec3::dot(up, direction);
	if (up.x == 0 && up.y == 0 && up.z == 0)
	{
		if (dir.z != 1)
			up.z = 1;
		else
			up.z = -1;
	}
	up = up.normalize();
	downScreen = vec3(-up.x, -up.y, -up.z);
	rightScreen = vec3::cross(up, direction);
}