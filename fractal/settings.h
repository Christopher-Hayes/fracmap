/* settings.h
 * Modified: Mark Garro and Shammah Chancellor (09/06/07)
 * Modified: Chris Hayes (06/26/18)
 */
#pragma once
#include <vector>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include "Vector_3.h"

const std::string version = "07.02.18";

// Program Parameters (defaults)
const double fractal_dimension = 1.82;
const double prefactor = 1.19;
const double overlap = 1.0;

const double mean_radius = 1.0;
const double epsilon = 0.05;
const int max_monomer_tries = 1000;
const int precision = 40;
const int num_colors = 8;
const Vector_3 center = Vector_3(0.0, 0.0, 0.0);

const double pi = 3.14159;

//const int CORRELATION_PRECISION = 500;
const int parts_per_radius = 10;
//const double SHELL_RADIUS = 2.0 * MEAN_RADIUS / PARTS_PER_RADIUS;
//const double CORRELATION_INCR = MEAN_RADIUS / PARTS_PER_RADIUS / 2;
const double filter_depth = mean_radius;
