/* main.cpp - Program entry point.
 * Created:  Mark Garro  (09/06/07)
 * Modified: Chris Hayes (06/26/18)
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "fractal.h"
#include "log.h"
#include "settings.h"
#include "micrograph.h"
#include "params.h"

using namespace std;

enum {escape, key_0, key_1, key_2, key_3};

// Print function menu ---------------------------------------------------------
void 
print_menu() {
	cout << "Choose an option to continue."
	     << "\nFractal menu:"
	     << "\n\t" << escape << ": Exit"
	     << "\n\t" << key_0 << ": Clear current fractal and create a new fractal"
	     << "\n\t" << key_1 << ": Calculate Structure Factor of Current Fractal"
	     << "\n\t" << key_2 << ": 2D Micrograph Analysis"
	     << "\n\t" << key_3 << ": Help" << endl;
}
// Open output file ------------------------------------------------------------
void open_output(ofstream& output) {
  string filename = "";

  // Open ofstream
  for (;;) {
    cout << "Output File Name? (e.g. output.txt)" << endl;
    cin >> filename;
    // Check that file doesn't already exists. access() is a sys/stat.h function
    if (access(filename.c_str(), F_OK) == -1)
      break;
    Log::warn("file already exists.");
  }

  output.open(filename.c_str());
}
// Compute structure factor ----------------------------------------------------
void
struct_factor(Fractal& base) {
  // Get output file
  ofstream output;
  open_output(output);

  // Compute structure factor
  base.structurec(output);

  output.close();
}
// Compute 2D micrograph analysis ----------------------------------------------
void
micro_analysis(Fractal& base) {
  // Get output file
  ofstream output;
  open_output(output);

  // Compute 2D micrograph analysis
  base.orient_random(output, 25, true);

  output.close();
}
// Input Validation ============================================================
// Validate Fractal Dimension --------------------------------------------------
void
validate_df(double& df) {
  // Prompt for value if not passed in CLI
  if (df == -1.0) {
    cout << "Fractal Dimension (decimal value within [1.0, 3.0])\n: ";
    cin >> df; // TODO: bad input
  }
  for (;;) {
    // Check value is within bounds
    if (df >= 1.0 && df <= 3.0)
      break;
    Log::warn("Fractal Dimension is invalid. It must be a double within the bounds [1.0, 3.0]\n");
    cout << "New Fractal Dimension: ";
    cin >> df;
  }
  Log::info("Good input: fractal dimension");
}
// Validate Prefactor ----------------------------------------------------------
void
validate_kf(double& kf) {
  // Prompt for value if not passed in CLI
  if (kf == -1.0) {
    cout << "Prefactor (decimal value within [1.0, inf) )\n: ";
    cin >> kf; // TODO: bad input
  }
  for (;;) {
    // Check value is within bounds
    if (kf >= 1.0)
      break;
    Log::warn("Prefactor is invalid. It must be a double within the bounds [1.0, inf)\n");
    cout << "New Prefactor: ";
    cin >> kf;
  }
  Log::info("Good input: prefactor");
}
// Validate Monomer Count ------------------------------------------------------
void
validate_n(int& n) {
  // Prompt for value if not passed in CLI
  if (n == -1) {
    cout << "Monomer count (integer value greater than 0)\n: ";
    cin >> n; // TODO: bad input
  }
  for (;;) {
    // Check value is within bounds
    if (n > 0)
      break;
    Log::warn("Monomer count is invalid. It must be an integer with the bounds [1, inf)\n");
    cout << "New Monomer Count: ";
    cin >> n;
  }
  Log::info("Good input: monomer count");
}
// Validate Overlap Factor -----------------------------------------------------
void
validate_k(double& k) {
  // Prompt for value if not passed in CLI
  if (k == -1.0) {
    cout << "Overlap Factor (decimal value within [0.5, 1.0] )\n: ";
    cin >> k; // TODO: bad input
  }
  for (;;) {
    // Check value is within bounds
    if (k >= 0.5 && k <= 1.0)
      break;
    Log::warn("Overlap Factor is invalid. It must be a decimal with the bounds [0.5, 1.0]\n");
    cout << "New Overlap Factor: ";
    cin >> k;
  }
  Log::info("Good input: overlap factor");
}

// Program entry point ---------------------------------------------------------
int
main(int argc, char **argv) {
  srand((unsigned int)time(NULL));

	Fractal base;
  double df = -1; // Fractal Dimension
  double kf = -1; // Prefactor
  int n = -1; // Monomer Count
  double k = -1; // Overlap Factor
  Params p = Params(argc, argv);
  // Quit out if usage/help parameter is active.
  if (p.check_usage())
    return 0;
  // Verbose
  if (p.check_verbose())
    log_info = true; // Log::info messages will now output
  Log::info("Verbose mode ON");

  // Fractal Dimension
  if (p.check_df()) {
    df = p.get_df();
    Log::info("CLI argument df=" + to_string(df));
  }
  // Prefactor
  if (p.check_kf()) {
    kf = p.get_kf();
    Log::info("CLI argument kf=" + to_string(kf));
  }
  // Monomer Count
  if (p.check_n()) {
    n = p.get_n();
    Log::info("CLI argument n=" + to_string(n));
  }
  // Overlap Factor
  if (p.check_k()) {
    k = p.get_k();
    Log::info("CLI argument k=" + to_string(k));
  }
	
  // Program loop; on first run automatically run new fractal
	for (int key = key_0;;) {
    switch (key)
    {
      case escape: // Quit
        Log::info("Program terminated successfully.\n");
        return 0;
      case key_0: // New fractal
        Log::info("Creating new fractal..");
        // Validate / get params
        validate_df(df);
        validate_kf(kf);
        validate_n(n);
        validate_k(k);
        // Generate fractal
        base = Fractal(df, kf, k);
        base.generate_fractal(n);
        // Reset parameters for next iteration
        df = kf = k = -1.0;
        n = -1;
        break;
      case key_1: // Structure Factor
        Log::info("Computing the fractal's stucture factor..");
        struct_factor(base);
        break;
      case key_2: // Micrograph analysis
        Log::info("Computing a 2D micrograph analysis on the fractal..");
        micro_analysis(base);
        break;
      case key_3: // Help
        Params::print_usage();
        break;
      default: // Catch all invalid input
        Log::warn("Invalid menu option.\n");
        break;					
    }
    // Print main menu; get user input
    print_menu();
    cin >> key;
	}
	return 0;
}
