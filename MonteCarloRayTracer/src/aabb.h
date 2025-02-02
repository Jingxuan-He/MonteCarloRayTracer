#pragma once
#include "hittable.h"
#include "ray.h"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class aabb {
public:
	aabb() {}
	aabb(const vec3& a, const vec3& b) { _min = a; _max = b; }
	vec3 min() const { return _min; }
	vec3 max() const { return _max; }
	bool hit(const ray& r, float tmin, float tmax) const;
	float area() const;
	int longest_axis() const;

private:
	vec3 _min;
	vec3 _max;
};

bool aabb::hit(const ray& r, float tmin, float tmax) const {
	for (int a = 0; a < 3; a++) {
		float t0 = ffmin(
			(_min[a] - r.origin()[a]) / r.direction()[a],
			(_max[a] - r.origin()[a]) / r.direction()[a]
		);
		float t1 = ffmax(
			(_min[a] - r.origin()[a]) / r.direction()[a],
			(_max[a] - r.origin()[a]) / r.direction()[a]
		);
		tmin = ffmax(t0, tmin);
		tmax = ffmin(t1, tmax);
		if (tmax <= tmin)
			return false;
	}
	return true;
}

float aabb::area() const {
	float a = _max.x() - _min.x();
	float b = _max.y() - _min.y();
	float c = _max.z() - _min.z();
	return 2 * (a * b + b * c + c * a);
}

int aabb::longest_axis() const {
	float a = _max.x() - _min.x();
	float b = _max.y() - _min.y();
	float c = _max.z() - _min.z();
	if (a > b && a > c)
		return 0;
	else if (b > c)
		return 1;
	else
		return 2;
}

aabb surrounding_box(aabb box0, aabb box1) {
	vec3 small(
		fmin(box0.min().x(), box1.min().x()),
		fmin(box0.min().y(), box1.min().y()),
		fmin(box0.min().z(), box1.min().z())
	);
	vec3 big(
		fmax(box0.max().x(), box1.max().x()),
		fmax(box0.max().y(), box1.max().y()),
		fmax(box0.max().z(), box1.max().z())
	);
	return aabb(small, big);
}