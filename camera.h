#ifndef CAMERA_H
#define CAMERA_H
#include "common.h"

class camera {
    public:
				camera() : camera(Vector(0., 0., 0.), 0., 0, 0) {}
				camera(Vector orig, double angle, int width, int height)
				{
						W = width;
						H = height;
            origin = orig;
						alpha = degrees_to_radians(angle);
        }

				Ray get_ray(double x, double y) {
						Vector u = Vector(origin[0] + x + 0.5 - W/2,
															origin[1] + y + 0.5 - H/2,
															origin[2]  - W/(2*tan(alpha/2)));
            u = u.normalize();
            return Ray(origin, u);
        }

    public:
        Vector origin;
				double alpha; // in radians, value given to constructor will be in degrees
				int W;
				int H;
};

#endif
