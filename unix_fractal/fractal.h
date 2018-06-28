/* fractal.h
 * Created:  Mark Garro  (09/06/07)
 * Modified: Chris Hayes (06/26/18)
 */
#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sstream>

#include "settings.h"
#include "Vector_3.h"
using namespace std;

class Fractal
{
public:
  // Constructors / Deconstructors =============================================
	Fractal(Vector_3 center);
	Fractal(double df=fractal_dimension, double kf=prefactor, double ol=1.0);
	~Fractal() {}

  // Core operations ===========================================================
  // Create/Add monomer
	void add_monomer(double x, double y, double z);
	void add_monomer(Vector_3 new_monomer);
	Vector_3 add_random_monomer();
	void create_monomer();

	void clear();
	
	void monte_carlo();
	bool overlap(const Vector_3& monomer);

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
	vector<Vector_3>& monomers() { return _fractal;}
  
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
	void structurec(ofstream & output);
	
	void orient_random(ofstream & output, unsigned int num_trials = 25, bool stablize = true);
	void rotate_newZ( Vector_3 newZ );
  
	// Convex hull codes
	Vector_3& max_point(Vector_3 direction);
	Vector_3& min_angle_point(Vector_3 head, Vector_3 tail, Vector_3 dir);

	bool find_stable_vector(Vector_3 seed, Vector_3 & stableOut);
	void find_first_facet(vector<Vector_3>& facets, Vector_3 seed);
	void find_next_facet(vector<Vector_3>& facets);

	Vector_3 last_facet_normal(vector<Vector_3> facets);
	bool cm_proj_in_facet(vector<Vector_3>& facets);
	bool check_last_facet(vector<Vector_3>& _facets);

	static bool last_trial;

	vector<Vector_3> points;
	bool box_created;

	vector<Vector_3> _facets; // Temporary debug for surface detection
	
private:
  // A vector containing the centers of the monomers.
	vector<Vector_3> _fractal;
	
	// Overlap parameters
	double _ol;  // in percent
	// Fixed parameters
	double _df, _kf, _a;
  
  // Rg linear time calculations
	Vector_3 _r_sum;  
	double _r_squared;
	
  // Dependent parameters
	Vector_3 _r_mean;
	double _rg;
	int _n;
	
	double box_length;
	int num_parts;
};

// ?
double psdrand(int);
