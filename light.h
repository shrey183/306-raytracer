#include <math.h>
#include "vector.h"
#pragma once

using namespace std;

class Light {
public:
	Vector O;
	Vector color;
	float intensity;

	explicit Light(Vector origin=Vector(), float intense=0.){
		O = origin;
		intensity = intense;
	}
};
