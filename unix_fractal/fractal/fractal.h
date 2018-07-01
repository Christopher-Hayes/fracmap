/* fractal.h
 * Created:  Mark Garro  (09/06/07)
 * Modified: Chris Hayes (06/26/18)
 */
#pragma once
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <vector>

#include "log.h"
#include "settings.h"
#include "Vector_3.h"

class Fractal
{
public:
  // Constructors / Deconstructors =============================================
	// Fractal(Vector_3 center);
	Fractal(double df=fractal_dimension, double kf=prefactor, double k=overlap);
	~Fractal() {}

  // Core operations ===========================================================
  void generate_fractal(int size);
	void monte_carlo();
  // Create/Add monomer
	void add_monomer(double x, double y, double z);
	void add_monomer(Vector_3 new_monomer);
	Vector_3 add_random_monomer();
	void create_monomer();

	void clear();
	
	bool check_overlap(const Vector_3& monomer);

  // Update
	void parameter_update();
  
	double test_rg(Vector_3 monomer);
  
	Vector_3 get_random_monomer();
	void remove_last();
	Vector_3 return_last();		

  // Getters
	double N(); // Where is this function?
	double get_df() const { return _df; }
	double get_kf() const { return _kf; }
	double radius() const {	return _a; }
	Vector_3 rmean() const { return _r_mean; }
	Vector_3 cm() const { return _r_mean; }
	double rg() const { return _rg; }
	std::vector<Vector_3>& monomers() { return _fractal;}
  
  // Vector-like operations
	unsigned int size() const { return _n; }
  int begin() const { return 0; }
  int end() const { return _fractal.size(); }
  Vector_3 return_last() const { return _fractal.back(); }
  Vector_3& grab(int i) {	return _fractal[i]; }
  Vector_3 operator[](int i) { return _fractal[i]; }

  // Setters
	void set_Df(double df) { _df = df; }
	void set_kf(double kf) { _kf = kf; }

	// Structure constant functions
	void create_box();
	void structurec(std::ofstream& output);
	
	void orient_random(std::ofstream& output, unsigned int num_trials = 25, bool stablize = true);
	void rotate_newZ( Vector_3 newZ );
  
	// Convex hull codes
	Vector_3& max_point(Vector_3 direction);
	Vector_3& min_angle_point(Vector_3 head, Vector_3 tail, Vector_3 dir);

	bool find_stable_vector(Vector_3 seed, Vector_3 & stableOut);
	void find_first_facet(std::vector<Vector_3>& facets, Vector_3 seed);
	void find_next_facet(std::vector<Vector_3>& facets);

	Vector_3 last_facet_normal(std::vector<Vector_3> facets);
	bool cm_proj_in_facet(std::vector<Vector_3>& facets);
	bool check_last_facet(std::vector<Vector_3>& _facets);
	
private:
  // A vector containing the centers of the monomers.
	std::vector<Vector_3> _fractal;
	
	// Fixed parameters
  double _df; // Fractal dimension
  double _kf; // Prefactor
  double _a;  // Radius?
  double _k;  // Monomer overlap factor
  
  // Rg linear time calculations
	Vector_3 _r_sum;  
	double _r_squared;
	
  // Dependent parameters
	Vector_3 _r_mean;
	double _rg;
	int _n;
	
	double box_length;
	int num_parts;

  // Put these in private..

	static bool last_trial; // ?

	std::vector<Vector_3> points; // What is this for when there's _fractal?
	bool box_created;

	std::vector<Vector_3> _facets; // Temporary debug for surface detection
};

// ?
double psdrand(int);
