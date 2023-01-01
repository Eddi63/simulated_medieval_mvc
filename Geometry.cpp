#include "Geometry.h"
#include <cmath>

const float pi = 2. * atan2(1., 0.);

float to_radians(float theta_d){
	return theta_d * pi / 180.0;
}

float to_degrees(float theta_r){
	return theta_r * 180.0 / pi;
}


// construct a Cartesian_vector from a Polar_vector
Cartesian_vector::Cartesian_vector(const Polar_vector& pv) {
	delta_x = pv.r * cos(pv.theta); //theta in radians
	delta_y = pv.r * sin(pv.theta);
}
Cartesian_vector::Cartesian_vector()
{
	delta_x = 0.0;
	delta_y = 0.0;
}

Cartesian_vector::Cartesian_vector(const Loc &loc_source, const Loc &loc_dest) {
    delta_x = loc_dest.getX() - loc_source.getX();
    delta_y = loc_dest.getY() - loc_source.getY(); // is this right???
}

void Cartesian_vector::operator=(const Polar_vector& pv)
{
	delta_x = pv.r * cos(pv.theta);
	delta_y = pv.r * sin(pv.theta);
}

// construct a Polar_vector from a Cartesian_vector
Polar_vector::Polar_vector(const Cartesian_vector& cv) {
	r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
	/* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
	theta = atan2(cv.delta_y, cv.delta_x);
	if (theta < 0.)
		theta = 2. * pi + theta; // normalize theta positive
}
Polar_vector::Polar_vector()
{
	r = 0.0;
	theta = 0.0;
}

Polar_vector::Polar_vector(float radius, float theta_in_degree){
    r = radius;
    theta = to_radians(theta_in_degree);
}

void Polar_vector::operator=(const Cartesian_vector& cv)
{
	r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
	/* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
	theta = atan2(cv.delta_y, cv.delta_x);
	if (theta < 0.)
		theta = 2. * pi + theta; // normalize theta positive
}

float Polar_vector::theta_in_degrees() {
    return to_degrees(theta);
}
