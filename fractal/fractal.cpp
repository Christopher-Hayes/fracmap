/* fractal.cpp
 * Created:  Mark Garro  (09/06/07)
 * Modified: Chris Hayes (06/26/18)
 */
#include "fractal.h"
using namespace std;

// Constructors / Deconstructors ===============================================
// Fractal constructor with Fractal Dimension, PreFactor, Overlap passed -------
Fractal::
Fractal(double df, double kf, double k)
: _df(df),
  _kf(kf),
  _a(mean_radius),
  _k(k),
  _r_sum(Vector_3(0, 0, 0)),
  _r_squared(0),
  _r_mean(Vector_3(0, 0, 0)),
  _rg(0),
  _n(0)
{
  // Validate parameters TODO: more helpful output
  if (df < 1.0 || df > 3.0)
    Log::fatal("Invalid fractal dimension. Range: [1.0, 3.0]");
  if (kf < 1.0)
    Log::fatal("Invalid prefactor. Range: [1.0, inf)");
  if (k < 0.5 || k > 1.0)
    Log::fatal("Invalid overlap. Range: [0.5, 1.0]");
  Log::info("Fractal initialized successfully. df, kf, k are good.");
}

// Fractal Generation ==========================================================
// Generate fractal ------------------------------------------------------------
void Fractal::
generate_fractal(int target_size) {
  Log::info("Generating fractal..");
  while ((int)size() < target_size) {
    create_monomer();
    cout << "Fractal size: " << (int)size() << " of " << target_size << endl;
  }
  cout << "Fractal successfully generated." << endl;
}
// Add new monomer -------------------------------------------------------------
void Fractal::
create_monomer() {
	if (_fractal.empty()) {
    Log::info("Adding fractal monomer center at (0.0, 0.0, 0.0)");
		add_monomer(0.0f, 0.0f, 0.0f);
	}else if (_fractal.size() == 1) {
    Log::info("Attaching random monomer to center monomer.");
	  add_monomer(add_random_monomer());
	}else {
    Log::info("Adding new monomer to fractal using Monte Carlo algorithm.");
		monte_carlo();
	}
}
// Add monomer using x,y,z coordinates -----------------------------------------
void Fractal::
add_monomer(double x, double y, double z) {
	add_monomer(Vector_3(x, y, z));
}
// Append monomer; update r and r^2 sums ---------------------------------------
void Fractal::
add_monomer(Vector_3 new_monomer) {
  _fractal.push_back(new_monomer);
  Log::info("Adding monomer at point " + new_monomer.print());
  
  _r_sum += new_monomer;
  _r_squared += new_monomer * new_monomer;

  parameter_update();
}
// MonteCarlo add monomer ------------------------------------------------------
void Fractal::monte_carlo() {
	Vector_3 temp_monomer;
  Vector_3 best_monomer(1000.0f, 1000.0f, 1000.0f); // Initialized out of range

	double expected_rg = pow(((_n + 1) / _kf), 1 / _df) * _a;
	double temp_rg;
  double best_rg = expected_rg * 1000; // Initialized out of range	

	for (int attempt = 0; attempt < max_monomer_tries; attempt++) {
	  temp_monomer = add_random_monomer();
	  temp_rg = test_rg(temp_monomer);
    // Check if monomer is within expected parameters
		if (abs(temp_rg - expected_rg) < abs(best_rg - expected_rg)) {
		  best_rg = temp_rg;
		  best_monomer = temp_monomer;
		}
	}
  add_monomer(best_monomer);
}
// Find how a monomer would affect radius of gyration --------------------------
double Fractal::test_rg(Vector_3 monomer) {
  Vector_3 temp_r_mean = (_r_sum + monomer) / (_n + 1);
  double temp_r_squared = _r_squared + monomer * monomer;
  
  return sqrt(temp_r_squared / (_n + 1) - (temp_r_mean * temp_r_mean));
}
// Update _rg from sum of radii and r_mean -------------------------------------
void Fractal::
parameter_update() {
  _n = (int)_fractal.size();
  _r_mean = _r_sum / _n;
  _rg = sqrt(_r_squared / _n - (_r_mean * _r_mean)); // Standard deviation
  Log::info("Fractal parameters updated.");
}
// Obtain a random monomer from the agglomerate --------------------------------
Vector_3 Fractal::
get_random_monomer() {
	return _fractal[rand() % _fractal.size()];
}
// Create monomer, randomly attach to factal such that it does not overlap
// beyond the accepted parameters ----------------------------------------------
Vector_3 Fractal::
add_random_monomer() {
  Vector_3 new_monomer;
  while (check_overlap(new_monomer)) {
    new_monomer = random_vec();
    new_monomer *= 2 * _a * _k; // Scale unit vector to twice monomer radius
    new_monomer += get_random_monomer(); // Translate monomer to new center
  }
  return new_monomer;
}
// Remove last monomer; update r and r^2 sums ----------------------------------
void Fractal::
remove_last() {
  Vector_3 last_monomer = _fractal.back();
  _fractal.pop_back();
  
  _r_sum -= last_monomer;
  _r_squared -= last_monomer * last_monomer;
  
  parameter_update();
}
/* Returns true if monomers are point contact (do not overlap) */
/* Changes by SC on 1/9/09 to check if a PARTICULAR monomer overlaps */
bool Fractal::
check_overlap(const Vector_3& monomer) {
  // TODO:  This should be updated to use an octtree for collision detection.
	for(vector<Vector_3>::iterator iter = _fractal.begin(); iter != _fractal.end(); iter++)
	{
		if(//iter != monomer && //TODO: Fix this!
		    //Until this is fixed, assuming it's checking for overlap on UNADDED monomer
 		   monomer.distance(*iter) < (2 * _a * _k - 0.01)) //This is rudimentary
		{
			return true; //There was an overlap
		}
	}

	return false;
}
// Clear fractal ---------------------------------------------------------------
void Fractal::clear() {
	_fractal.clear();
	points.clear();
	parameter_update();
  Log::info("Fractal cleared.");
}
