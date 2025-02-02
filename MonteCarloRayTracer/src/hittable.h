#pragma once
#include <float.h>
#include "aabb.h"

class material;

struct hit_record {
	float t;
	float u;
	float v;
	vec3 p;
	vec3 normal;
	material* mat_ptr;
};

class hittable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
	virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
	virtual float pdf_value(const vec3& o, const vec3& v) const { return 0.0; }
	virtual vec3 random(const vec3& o) const { return vec3(1, 0, 0); }
};