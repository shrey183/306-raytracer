#include "common.h"
#include "sphere.h"
#include "light.h"
#include "geometry.h"
#pragma once


class Scene: public Geometry {

public:
	Scene(){}
	Scene(shared_ptr<Geometry> obj){ add(obj); }
	Scene(vector<shared_ptr<Geometry> > Spheres, Light light_source){
	Sph = Spheres;
	lsource = light_source;
}
	void add(shared_ptr<Geometry> obj){
		Sph.push_back(obj);

}
	void set_light(Light light_source){lsource = light_source;}
	Vector get_colors(Ray ray, int ray_depth);
	virtual bool intersection(Ray ray, Intersection& rec) const;

public:
	vector<shared_ptr<Geometry> > Sph;
	Light lsource;
	double epsilon = 0.001;
};

bool Scene::intersection(Ray ray, Intersection& rec) const{
		Intersection temp_rec;
    auto hit_anything = false;
    auto closest_so_far = pow(2,31);

    for (const auto& object : Sph) {
        if (object->intersection(ray, temp_rec))
				{
						if(temp_rec.t <= closest_so_far)
						{
							hit_anything = true;
	            closest_so_far = temp_rec.t;
	            rec = temp_rec;
						}
        }
    }

    return hit_anything;
}


Vector Scene::get_colors(Ray ray, int ray_depth){
    Intersection rec;
		auto hit = intersection(ray, rec);
    if(ray_depth <= 0 )
		{
			return Vector(0., 0., 0.);
		}

		if(hit)
		{
			//std::cout << "Are we being hit" << std::endl;

			Vector Normal = rec.Normal;
			Vector P = rec.inter + Normal*(epsilon);

			if(rec.material == 1){
				// reflective surface
				Vector incident = ray.u;
				Vector reflected = reflect(incident, Normal);
				Ray scattered = Ray(P, reflected);
				return get_colors(scattered, ray_depth - 1);
			}

			else if(rec.material == 2 or rec.material == 3){
				// transparent surface
				double n1 = 1.;
				double n2 = 1.5;
				double ref_index = n2/n1;

				// for hollow materials
				ref_index = (rec.material == 3) ? 1 : ref_index;
				Normal = (rec.material == 3) ? -Normal : Normal;

				bool front_facing = (dot(ray.u, Normal) <= 0) ? ref_index : 1/ref_index;
				Normal = (dot(ray.u, Normal) <= 0) ? Normal : -Normal;

				double R = schlick(dot(Normal,ray.u), ref_index);
				double T = 1 - R;
        auto u = uniform(engine);

        if (u < R){
						// Reflect
            Ray reflectedRay = Ray(P, reflect(ray.u, Normal));
            return get_colors(reflectedRay, ray_depth-1);
        }
        else{
            //	Refract
            Vector omega_T = (1/ref_index) * (ray.u - dot(ray.u,Normal)*Normal);
            double TIR = 1 - pow(1/ref_index, 2) * (1- pow(dot(ray.u,Normal),2));
            if(TIR<0){
							// Total Internal Reflection
	            Ray ray = Ray(P, reflect(ray.u, Normal));
	            return get_colors(ray,ray_depth-1);
            }
            Vector omega_N = (- Normal) * sqrt(TIR);
            Vector scattered = (omega_T + omega_N);
            Ray refractRay = Ray(P - Normal * (2 * epsilon), scattered);
            return get_colors(refractRay, ray_depth-1);
        }
			}
			else
			{
				// Diffuse Surfaces
				Vector omega = lsource.O - P;
				double d = omega.norm();
				omega = omega*(1./d);
				Ray scnd_ray = Ray(lsource.O, -omega);
				Intersection secd_intersect;
				bool hit_anything = intersection(scnd_ray, secd_intersect);
				bool visible = secd_intersect.t > d;
				Vector Lo = rec.albedo * visible * (lsource.intensity/
										(4*M_PI*pow(d,2))*
										max(dot(Normal,omega),0.0)/M_PI);

				// Add Indirect Lighting here
				Ray randomRay = Ray(P, random_cos(Normal));
				Vector x = get_colors(randomRay, ray_depth - 1);
				Lo = Lo +  rec.albedo * x;
				return Lo;
			}


		}
		return Vector(0., 0., 0.);
	}
