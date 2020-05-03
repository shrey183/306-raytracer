#include <bits/stdc++.h>
#include <math.h>
#include "vector.h"
#pragma once

using namespace std;

class Ray {
public:
	Vector O;
	Vector u;

	explicit Ray(Vector origin=Vector(), Vector direction=Vector()){
		O = origin;
		u = direction;
	}
};
