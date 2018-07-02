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
  // Validate parameters
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
  if (target_size < 1)
    Log::fatal("Cannot generate fractal with a size less than 1.");
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
add_monomer(const Vector_3& new_monomer) {
  _fractal.push_back(new_monomer);
  Log::info("Adding monomer at point " + new_monomer.print());
  
  _r_sum += new_monomer;
  _r_squared += new_monomer * new_monomer;

  parameter_update();
}
// Create monomer, randomly attach to factal such that it does not overlap
// beyond the accepted parameters ----------------------------------------------
Vector_3 Fractal::
add_random_monomer() {
  Vector_3 new_monomer;
  double threshold = 2 * _a * _k;

  // Repeat until monomer is above threshold distance from nearest monomer
  do {
    // Scale random unit vector to 2x radius, translate to random monomer
    // TODO: should get_random_monomer() be run every single time?
    new_monomer = Vector_3::random_vec() * threshold + get_random_monomer();
  } while (monomer_proximity(new_monomer, threshold));

  return new_monomer;
}
// MonteCarlo add monomer ------------------------------------------------------
void Fractal::
monte_carlo() {
	Vector_3 temp_monomer;
  // WARNING: "out of range" is highly dependent on mean_radius
  // TODO: change to invalid value
  Vector_3 best_monomer(1000.0f, 1000.0f, 1000.0f); // Initialized out of range

	double temp_rg;
	double expected_rg = pow(((_n + 1) / _kf), 1 / _df) * _a;
  double best_rg = expected_rg * 1000; // Initialized out of range	
  double best_diff = abs(best_rg - expected_rg);

	for (int attempt = 0; attempt < max_monomer_tries; attempt++) {
	  temp_monomer = add_random_monomer();
	  temp_rg = test_rg(temp_monomer);
    // Check if monomer is within expected parameters
		if (abs(temp_rg - expected_rg) < best_diff) {
		  best_rg = temp_rg;
		  best_monomer = temp_monomer;
      best_diff = abs(best_rg - expected_rg);
		}
	}
  add_monomer(best_monomer);
}
// Find how a monomer would affect radius of gyration --------------------------
double Fractal::
test_rg(const Vector_3& test_monomer) {
  Vector_3 temp_r_mean = (_r_sum + test_monomer) / (_n + 1);
  double temp_r_squared = _r_squared + test_monomer * test_monomer;
  
  return sqrt(temp_r_squared / (_n + 1) - (temp_r_mean * temp_r_mean));
}
// Update _rg from sum of radii and r_mean -------------------------------------
// TBD: keep this? - increased efficiency vs opaque parameters + prone to bugs
void Fractal::
parameter_update() {
  _n = (int)_fractal.size();
  _r_mean = _r_sum / _n;
  _rg = sqrt(_r_squared / _n - (_r_mean * _r_mean)); // Standard deviation
  Log::info("Fractal parameters updated."); //May remove depending on speed cost
}
// Obtain a random monomer from the agglomerate --------------------------------
Vector_3 Fractal::
get_random_monomer() {
	return _fractal[rand() % _fractal.size()];
}
// Returns true if new monomer within threshold distance of another ------------
bool Fractal::
monomer_proximity(const Vector_3& new_monomer, double threshold) {
  for (const auto& monomer : _fractal) {
		if (new_monomer.distance(monomer) < threshold)
			return true; // Overlap found
	}
	return false;
}
// Clear fractal ---------------------------------------------------------------
void Fractal::clear() {
	_fractal.clear();
	parameter_update();
  Log::info("Fractal cleared.");
}

// Print functions =============================================================
// Print monomer XYZ centers ---------------------------------------------------
void Fractal::
print_monomers(ostream& out) const {
  out << "Df: " << _df
      << "\nkf: " << _kf
      << "\nn: " << _n
      << "\nk: " << _k
      << "\n\nRg: " << _rg
      << "\n\nX Y Z" << endl;
  for (Vector_3 v : _fractal)
    out << v << endl;
}
