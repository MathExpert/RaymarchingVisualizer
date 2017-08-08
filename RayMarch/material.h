#ifndef __material
#define __material

#include "myvector.h"

struct Material
{
	Material();
	Material(color, color, color, float);

	color Ka;
	color Kd;
	color Ks;
	float alpha;

	float refl;
	float refr;
};

#endif