#ifndef __myvector
#define __myvector

struct vec2
{
	float x, y;

	vec2();
	vec2(float x, float y);
	vec2(const vec2&);

	float length();
};

struct vec3
{
	float x, y, z;
	vec2 xz;//xy, xz, yz;

	vec3();
	vec3(float x, float y, float z);
	vec3(const vec3&);

	inline float length();
	float maxcomp();
	vec3 abs() const;
	vec3 max(float);
	vec3 normalize();
	static float dot(vec3, vec3);
	static vec3 cross(vec3, vec3);
	vec3 operator - (const vec3&) const;
	vec3 operator + (const vec3&) const;
	vec3 operator += (const vec3&);
	vec3 operator * (const float) const;
	vec3 operator / (const float) const;
	bool operator == (const vec3&) const;
	void crop();
};
typedef vec3 color;

struct vec4
{
	float x, y, z, w;
	vec3 xyz;

	vec4();
	vec4(float, float, float, float);

	vec4 normalize();
};

#endif // __myvector