#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <chrono>
#include "common.h"
#include "camera.h"
#include "light.h"
#include "geometry.h"
#include "sphere.h"
#include "triangleMesh.h"
#include "scene.h"

Scene make_scene(){
	// Defining colors that we will use
	Vector BLACK = Vector(0.,0.,0.);
	Vector RED = Vector(255.,0.,0.);
	Vector GREEN = Vector(0.,128.,0.);
	Vector BLUE = Vector(0.,0.,255.);
	Vector PINK = Vector(255.,192.,203.);
	Vector WHITE = Vector(255.,255.,255.);
	Vector CYAN =  Vector(0.,255.,255.);
	Vector YELLOW =  Vector(255.,255.,0.);

	float intensity = 2*pow(10, 7);
	Light lsource(Vector(-20., 20., 40.),Vector(), intensity);
	Scene scene;
	scene.set_light(lsource);



	scene.add(make_shared<Sphere>(Vector(0.,1000.,0.), 940, RED));
	scene.add(make_shared<Sphere>(Vector(0.,0., -1000.), 940, GREEN));
	scene.add(make_shared<Sphere>(Vector(0.,-1000.,0.), 990, BLUE));
	scene.add(make_shared<Sphere>(Vector(0.,0., 1000.), 940, PINK));
	scene.add(make_shared<Sphere>(Vector(-1000.,0.,0.),940, CYAN));
	scene.add(make_shared<Sphere>(Vector(0.,0.,0.),940, YELLOW));


	// Sphere with Reflection
	scene.add(make_shared<Sphere>(Vector(-20.,0.,0.),10, WHITE, 1));


	// Sphere with Refraction
	scene.add(make_shared<Sphere>(Vector(0.,0.,0.),10, WHITE, 2));
	// Hollow Sphere
	scene.add(make_shared<Sphere>(Vector(20.,0.,0.),10, WHITE, 3));
	scene.add(make_shared<Sphere>(Vector(20.,0.,0.),-9.5, WHITE, 3));
	/*
	auto tm = make_shared<TriangleMesh>();
	tm->readOBJ("cadnav.com_model/Models_F0202A090/cat.obj");
	tm->scale_model();
	scene.add(tm);
	*/
	return scene;

}





int main(){


	/***
	1) FRESNEL: Time taken 118732 seconds with 50 samples per pixel.
	2) Indirect Lighting
	3) Antialising
	***/

	//Defining the point of view of the user

	int W = 512; //width of grid
	int H = 512; //height of grid

	// Fix Camera
	Vector cam_origin = Vector(0.,0.,55.);
	double angle = 60;
	camera cam(cam_origin, angle, W, H);

	// Get scene
	Scene scene = make_scene();



	int num_samples = 50;
	int max_depth = 50;
	double std = 0.5;

	int counter = 0;
	unsigned char grid[W*H*3]; // of H*W*3 elements

	auto t_start = std::chrono::high_resolution_clock::now();
	for(int i =0;i < H;i++)
	{
		std::cerr << "\rScanlines remaining: " << H - i - 1 << ' ' << std::flush;
		for(int j=0;j<W;j++)
		{
			Vector color(0., 0., 0.);

			for(int k = 0; k < num_samples; k++)
			{
				double x = (double)i;
				double y = (double)j;
				boxMuller(std, x, y);
				Ray first_ray = cam.get_ray(y, H - x - 1);
				color += scene.get_colors(first_ray, max_depth);
			}

			color = color * (1./num_samples);
			color = color.gammaCorrect();
			grid[counter++] = (unsigned char) max(min(color[0],255.),0.);
			grid[counter++] = (unsigned char) max(min(color[1],255.),0.);
			grid[counter++] = (unsigned char) max(min(color[2],255.),0.);

		}
	}
	auto t_end = std::chrono::high_resolution_clock::now();
	stbi_write_png("IndirectLighting.png", W,H, 3, grid, W * 3);
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
	std::cout << "Print Total Time: " << elapsed_time_ms << std::endl;
}
