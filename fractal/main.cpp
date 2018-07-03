/* main.cpp - Program entry point.
 * Created:  Mark Garro  (09/06/07)
 * Modified: Chris Hayes (06/26/18)
 */
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
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

// Print function menu ---------------------------------------------------------
void 
print_menu() {
	cout << "\n  + - - - - - - - FracMAP  menu - - - - - - - +"
       << "\n  |     " << left << setw(38) << "" << "|"
       << "\n  | 0 | " << setw(38) << "Create new fractal (Clear prexisting)" << "|"
       << "\n  |     " << setw(38) << "" << "|"
       << "\n  | 1 | " << setw(38) << "Calculate structure factor of fractal" << "|"
       << "\n  |     " << setw(38) << "" << "|"
       << "\n  | 2 | " << setw(38) << "Run 2D Micrograph analysis on fractal" << "|"
       << "\n  |     " << setw(38) << "" << "|"
       << "\n  | 3 | " << setw(38) << "Quit" << "|"
	     << "\n  + - - - - - - - - - - - - - - - - - - - - - +"
       << "\n\n  Choose one.\n  Input the integer and press enter: ";
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
    _log.warn("file already exists.");
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
// Extract double input
double
grab_double(const double& def, string param, string range) {
  string input = "";
  try {
    cout << endl << param << " Range=" << range << " Default=" << def << "\n  : ";
    getline(cin, input);
    if (input == "")
      return def;
    else
      return stod(input);
  }catch (const exception& e) {
    _log.fatal("Bad double input."); // improve...
    return -1.0;
  }
}
// Extract integer input
int
grab_int(const int& def, string param, string range) {
  string input = "";
  try {
    cout << endl << param << " Range=" << range << " Default=" << def << "\n  : ";
    getline(cin, input);
    if (input == "")
      return def;
    else
      return stoi(input);
  }catch (const exception& e) {
    _log.fatal("Bad int input."); // improve..
    return -1;
  }
}
// Validate Fractal Dimension --------------------------------------------------
void
validate_df(double& df, bool cli=false) {
  // Prompt for value if not passed in CLI
  if (!cli)
    df = grab_double(fractal_dimension, "Fractal Dimension", "[1.0, 3.0]");
  for (;;) {
    // Check value is within bounds
    if (df >= 1.0 && df <= 3.0)
      break;
    _log.warn("Fractal Dimension is invalid. It must be a double within the bounds [1.0, 3.0]\n");
    cout << "New Fractal Dimension: ";
    df = grab_double(fractal_dimension, "Fractal Dimension", "[1.0, 3.0]");
  }
  _log.info("Good input: fractal dimension");
}
// Validate Prefactor ----------------------------------------------------------
void
validate_kf(double& kf, bool cli=false) {
  // Prompt for value if not passed in CLI
  if (!cli)
    kf = grab_double(prefactor, "Prefactor", "[1.0, inf)");
  for (;;) {
    // Check value is within bounds
    if (kf >= 1.0)
      break;
    _log.warn("Prefactor is invalid. It must be a double within the bounds [1.0, inf)\n");
    cout << "New Prefactor: ";
    kf = grab_double(prefactor, "Prefactor", "[1.0, inf)");
  }
  _log.info("Good input: prefactor");
}
// Validate Monomer Count ------------------------------------------------------
void
validate_n(int& n, bool cli=false) {
  // Prompt for value if not passed in CLI
  if (!cli)
    n = grab_int(monomer_count, "Monomer Count", "[1, inf)");
  for (;;) {
    // Check value is within bounds
    if (n > 0)
      break;
    _log.warn("Monomer count is invalid. It must be an integer with the bounds [1, inf)\n");
    cout << "New Monomer Count: ";
    n = grab_int(monomer_count, "Monomer Count", "[1, inf)");
  }
  _log.info("Good input: monomer count");
}
// Validate Overlap Factor -----------------------------------------------------
void
validate_k(double& k, bool cli=false) {
  // Prompt for value if not passed in CLI
  if (!cli)
    k = grab_double(overlap, "Overlap Factor", "[0.5, 1.0]");
  for (;;) {
    // Check value is within bounds
    if (k >= 0.5 && k <= 1.0)
      break;
    _log.warn("Overlap Factor is invalid. It must be a decimal with the bounds [0.5, 1.0]\n");
    cout << "New Overlap Factor: ";
    k = grab_double(overlap, "Overlap Factor", "[0.5, 1.0]");
  }
  _log.info("Good input: overlap factor");
}
// Validate Epsilon ------------------------------------------------------------
void
validate_e(double& e, bool cli=false) {
  string input;
  // Prompt for value if not passed in CLI
  if (!cli)
    e = grab_double(epsilon, "Epsilon", "(0.0, inf)");
  for (;;) {
    // Check value is within bounds
    if (e > 0.0)
      break;
    _log.warn("Epsilon is invalid. It must be a decimal greater than 0.0\n");
    cout << "New Epsilon (press enter to use default): ";
    e = grab_double(epsilon, "Epsilon", "(0.0, inf)");
  }
  _log.info("Good input: overlap factor");
}
// Program entry point ---------------------------------------------------------
int
main(int argc, char **argv) {
  srand((unsigned int)time(NULL));

  ofstream out("out.txt");

	Fractal* base = nullptr;
  double df = -1; // Fractal Dimension
  double kf = -1; // Prefactor
  int n = -1; // Monomer Count
  double k = -1; // Overlap Factor
  double e = -1; // Epsilon
  string s; // for input
  Params p = Params(argc, argv);
  // Quit out if usage/help parameter is active.
  if (p.check_usage())
    return 0;
  // Verbose
  if (p.check_verbose())
    _log.set_info(true); // _log.info messages will now output
  _log.info("Verbose mode ON");

  // Fractal Dimension
  if (p.check_df()) {
    df = p.get_df();
    validate_df(df, true);
    _log.info("CLI argument df=" + to_string(df));
  }
  // Prefactor
  if (p.check_kf()) {
    kf = p.get_kf();
    validate_kf(kf, true);
    _log.info("CLI argument kf=" + to_string(kf));
  }
  // Monomer Count
  if (p.check_n()) {
    n = p.get_n();
    validate_n(n, true);
    _log.info("CLI argument n=" + to_string(n));
  }
  // Overlap Factor
  if (p.check_k()) {
    k = p.get_k();
    validate_k(k, true);
    _log.info("CLI argument k=" + to_string(k));
  }
  // Epsilon
  if (p.check_e()) {
    e = p.get_e();
    validate_e(e, true);
    _log.info("CLI argument e=" + to_string(e));
  }

  // Runs
  if (p.check_r()) {
    _log.info("Running batch..");
    // Validation
    validate_df(df);
    validate_kf(kf);
    validate_n(n);
    validate_k(k);
    validate_e(e);
    // # runs
    int total_runs = p.get_r();
    if (total_runs < 1)
      _log.fatal("Invalid number of runs. Must be greater than 0.");
    // TODO: ofstream safety
    // Put params in file
    ofstream params_output("./run_output/run_params.txt", ios::trunc); //Discard old contents
    params_output << "Df: " << df
                  << "\nkf: " << kf
                  << "\nn: " << n
                  << "\nk: " << k
                  << "\ne: " << e << endl;
    // Output file
    ofstream run_output;
    if (p.check_run_output())
      run_output.open(string(p.get_run_output()) + "/run.txt");
    else
      run_output.open(run_output_dir + "/run.txt");
    run_output << "Run\tRg\tActual_Epsilon" << endl;
    // Runs
    for (int run=0; run<total_runs; run++) {
      cout << "\n\nRun " << run << endl;
      base = new Fractal(df, kf, k, e);
      base->generate_fractal(n);
      run_output << run << "\t" << base->rg() << "\t" << base->actual_e() << endl;
    }
    run_output.close();
  }else {
    // Program loop; on first run automatically run new fractal
    for (char key = '0';;) {
      switch (key)
      {
        case '0': // Validate new params
          // Validate / get params
          validate_df(df);
          validate_kf(kf);
          validate_n(n);
          validate_k(k);
          validate_e(e);
          _log.info("Creating new fractal..");
          // Generate fractal
          base = new Fractal(df, kf, k, e);
          base->generate_fractal(n);
          // base->print_monomers(out);
          // out.close();
          // Reset parameters for next iteration
          df = kf = k = e = -1.0;
          n = -1;
          break;
        case '1': // Structure Factor
          _log.info("Computing the fractal's stucture factor..");
          struct_factor(*base);
          break;
        case '2': // Micrograph analysis
          _log.info("Computing a 2D micrograph analysis on the fractal..");
          micro_analysis(*base);
          break;
        case '3': // Quit
          if (base != nullptr)
            delete base;
          cout << "Program terminated successfully.\n" << endl;
          return 0;
        default: // Catch all invalid input
          _log.warn("Invalid menu option.\n");
          break;					
      }
      // Print main menu; get user input
      print_menu();
      cin >> key;
      // Ignore extraneous output
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
	return 0;
}
