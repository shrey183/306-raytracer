#include <math.h>
#include "vector.h"
#pragma once

using namespace std;

class Light {
public:
	Vector O;
	Vector color;
	float intensity;

	explicit Light(Vector origin=Vector(), Vector col=Vector(), float intense=0.){
		O = origin;
		color = col;
		intensity = intense;
	}
};
