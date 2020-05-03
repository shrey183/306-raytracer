#include <bits/stdc++.h>
#include <math.h>
#include "vector.h"
#include "ray.h"
#include "geometry.h"
#pragma once

using namespace std;



class Sphere: public Geometry {
public:
	Sphere(){}
	Sphere(Vector center=Vector(), double radius=10, Vector colors=Vector(), int mat=0):
	C(center), R(radius), albedo(colors), material(mat) {};
	virtual bool intersection(Ray r, Intersection& rec) const;

public:
	Vector C;
	double R;
	Vector albedo;
	int material;
};


bool Sphere::intersection(Ray r, Intersection& rec) const
{

	Vector origin = r.O;
	Vector direction = r.u;
	Vector N = origin + C*(-1);

	double delta = pow(direction.dot(N), 2) - (N.dot(N) - pow(R,2));
	if (delta<0) return false;

	else if (delta == 0)
	{
	double t = direction.dot(N*(-1));
	if (t >= 0)
	{
		rec.inter = origin+direction*t;
		rec.t = t;
		rec.Normal = (rec.inter + C*(-1)).normalize();
		rec.albedo = albedo;
		rec.material = material;
		rec.check = 1;
		return true;
	}
	else return false;
	}
	else
	{
	double t1 =  direction.dot(N*(-1)) - sqrt(delta);
	double t2 = direction.dot(N*(-1)) + sqrt(delta);

	if (t2 < 0) return false;
	else
	{
		if (t1 >= 0) {

		rec.inter = origin+direction*t1;
		rec.t = t1;
		rec.Normal = (rec.inter + C*(-1)).normalize();
		rec.albedo = albedo;
		rec.material = material;
		rec.check = 1;
		return true;
		}
		else{
		rec.inter = origin+direction*t2;
		rec.t = t2;
		rec.Normal = (rec.inter + C*(-1)).normalize();
		rec.albedo = albedo;
		rec.material = material;
		rec.check = 1;
		return true;

		}
	}
	}
}
