#include <iostream>
//#include <iomanip>

#include "Loc.h"

#include <cmath>

// angle units conversion functions
float to_radians(float theta_d);
float to_degrees(float theta_r);

struct Polar_vector;

typedef struct Cartesian_vector {
	Cartesian_vector(const struct Polar_vector & pv);
	Cartesian_vector();
    Cartesian_vector(const Loc& loc_source, const Loc& loc_dest);
	void operator=(const struct Polar_vector & pv);
	float delta_x;
	float delta_y;
} Cartesian_vector;

typedef struct Polar_vector {
	Polar_vector(const Cartesian_vector & cv);
	Polar_vector();
    Polar_vector(float radius, float theta_in_degree);
	void operator=(const Cartesian_vector & cv);
    float theta_in_degrees();
	float r;
	float theta;
} Polar_vector;

