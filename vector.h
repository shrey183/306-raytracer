#include <math.h>
#include <bits/stdc++.h>
#pragma once

using namespace std;

class Vector {
	public:
		explicit Vector(double x=0., double y=0., double z=0.){
			coords[0] = x;
			coords[1] = y;
			coords[2] = z;
		};

		Vector& operator+=(const Vector& b){
			coords[0] += b[0];
			coords[1] += b[1];
			coords[2] += b[2];
			return *this;
		}
		const double& operator[](int i) const{ return coords[i];}
		double& operator[](int i) {return coords[i]; }
		Vector operator-() const { return Vector(-coords[0], -coords[1], -coords[2]); }

		double norm(){
			double n = 0.0;
			for (int i=0;i<3;i++) n += pow(coords[i],2);

			return sqrt(n);
		}

		Vector normalize(){
			double N = norm();
			return Vector(coords[0]/N, coords[1]/N, coords[2]/N);
		}

		Vector gammaCorrect(){
			float gamma = 2.2;
			return Vector(pow(coords[0], 1./gamma),
										pow(coords[1], 1./gamma),
										pow(coords[2], 1./gamma));
		}

		double dot(const Vector&a){
			return coords[0]*a[0] + coords[1]*a[1] + coords[2]*a[2];
		}
	private:
		double coords[3];
	};


	Vector operator+(const Vector& a, const Vector &b) {
		return Vector(a[0] + b[0], a[1]+b[1], a[2]+b[2]);
	}


	Vector cross(const Vector &u, const Vector &v) {
	    return Vector(u[1] * v[2] - u[2] * v[1],
	                u[2] * v[0] - u[0] * v[2],
	                u[0] * v[1] - u[1] * v[0]);
	}

	void printVec(const Vector& v){
		std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
	}


	Vector operator*(const Vector &u, const Vector &v) {
	    return Vector(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
	}

	Vector operator*(double t, const Vector &v) {
	    return Vector(t*v[0], t*v[1], t*v[2]);
	}

	Vector operator*(const Vector &v, double t) {
	    return t * v;
	}

	Vector operator-(const Vector &u, const Vector &v) {
	    return Vector(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
	}

	double dot(const Vector &u, const Vector &v) {
	    return u[0] * v[0]
	         + u[1] * v[1]
	         + u[2] * v[2];
	}

	Vector reflect(const Vector& v, const Vector& n) {
	    return v - 2*dot(v,n)*n;
	}
	double get_min(double a, double b) { return a <= b ? a : b; }

	Vector refract(const Vector& uv, const Vector& n, double etai_over_etat) {
	    auto cos_theta = get_min(dot(uv*(-1), n), 1.0);
	    Vector r_out_parallel =  etai_over_etat * (uv + cos_theta*n);
	    Vector r_out_perp = -sqrt(1.0 - r_out_parallel.norm()) * n;
	    return r_out_parallel + r_out_perp;
	}
