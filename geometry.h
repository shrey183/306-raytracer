#include <math.h>
#include <bits/stdc++.h>
#include "vector.h"
#include "ray.h"

#pragma once

using namespace std;

class Intersection {
public:
	Vector inter;
	bool check;
	float t; // used to get closest
	Vector Normal;
	Vector albedo;
	/*
	material = 0, diffusive surface
	material = 1, reflective surface
	material = 2, transparent surface
	*/
	int material;

	explicit Intersection(Vector intersection=Vector(), bool ok=0, float val=0., Vector normal=Vector(), Vector alb=Vector(),int mat=0){
		inter = intersection;
		check=ok;
		t = val;
		Normal = normal;
		albedo = alb;
		material = mat;
	}
};

class Geometry{

	public:
			virtual bool intersection(Ray ray, Intersection& rec) const=0;
};
