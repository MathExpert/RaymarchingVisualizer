#include "StdAfx.h"

#include "material.h"

Material::Material()
{
	refl = 0;
	refr = 0;
}

Material::Material(color Ka, color Kd, color Ks, float alpha)
{
	this->Ka = Ka;
	this->Kd = Kd;
	this->Ks = Ks;
	this->alpha = alpha;
	refl = 0;
	refr = 0;
}