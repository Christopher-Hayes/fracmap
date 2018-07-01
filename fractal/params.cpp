/* params.cpp
 * Modified: Chris Hayes (06/28/18)
 */
#include <cstdlib>
#include <string>
using namespace std;
#include "params.h"
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// constructor
Params::Params(int argc, char* argv[])
{
  // init
  _df_v = _kf_v = _k_v = 0.0;
  _n_v = 0;
  _verbose = _output = _usage = _df = _kf = _n = _k = false;
  // process switches
  int code, opt;
  while ((opt = getopt_long(argc, argv, "vbho:d:p:n:k:", LONG_OPTS, &code)) != -1){
    switch (opt) {
      case 'o': // Output
        _output = true;
        _output_file = optarg;
        break;
      case 'b': // Verbose
        _verbose = true;
        break;
      case 'd': // Fractal Dimension
        _df = true;
        _df_v = extract_double("Fractal Dimension");
        break;
      case 'p': // Prefactor
        _kf = true;
        _kf_v = extract_double("Prefactor");
        break;
      case 'n': // Monomer Count
        _n = true;
        _n_v = extract_int("Monomer Count");
        break;
      case 'k': // Overlap factor
        _k = true;
        _k_v = extract_double("Overlap Factor");
        break;
      case 'v': // Version
        _usage = true;
        cout << "fracMAP v" << log_green << version << log_reset << endl;
        break;
      case 'h': // Help
        _usage = true;
        print_usage();
        break;
      case '?':
      default:
        print_usage(1);
    }
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Extract float from optarg
double Params::
extract_double(string parameter) {
  try {
    return stod(string(optarg)); // stod() used instead of atof() for exceptions
  }catch (const exception& e) {
    print_usage();
    Log::fatal("Invalid argument for " + parameter + ": " + e.what());
    return -1.0; // remove no return warnings
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Extract integer from optarg
int Params::
extract_int(string parameter) {
  try {
    string s = string(optarg);
    if ((double)stoi(s) != stod(s))
      Log::fatal(parameter + " cannot be a decimal. Must be integer.");
    return stoi(s);
  }catch (const exception& e) {
    print_usage();
    Log::fatal("Invalid argument for " + parameter + ". Must be integer.");
    return -1; // remove no return warnings
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// print usage; err defaults to -1 (no fatal error)
void
Params::print_usage(int err)
{
  // print usage; modeled from nmap's usage comment
  cout << "\n\tfracMAP v" << log_green << version << log_reset
       << "\n\nUsage:"
       << "\n\n\t./fracmap [Options]"
       << "\n\n\nInline Command Arguments (program will prompt in absence)"
       // Fractal Dimension
       << "\n\n" << " Fractal Dimension"
       << "\n  " << log_cyan << "-d <fractal dimension>"
       << log_magenta << " --fractal_dimension <fractal dimension>" << log_reset
       << "\n  Expects " << log_blue << "decimal value " << log_reset << "with the range of [1.0, 3.0]"
       // Prefactor
       << "\n\n Prefactor"
       << "\n  " << log_cyan << "-p <prefactor>"
       << log_magenta << " --prefactor <prefactor>" << log_reset
       << "\n  Expects " << log_blue << "decimal value " << log_reset << "with the range of [1.0, inf)"
       // Monomer Count
       << "\n\n Monomer Count"
       << "\n  " << log_cyan << "-n <monomer count>"
       << log_magenta <<" --monomers <monomer count>" << log_reset
       << "\n  Expects " << log_green << "integer value " << log_reset << "greater than 0"
       // Overlap Factor
       << "\n\n Overlap Factor"
       << "\n  " << log_cyan << "-k <overlap factor>"
       << log_magenta <<  " --overlap <overlap factor>" << log_reset
       << "\n  Expects " << log_blue << "decimal value " << log_reset << "with the range of [0.5, 1.0]"
       << "\n\n\nOUTPUT:"
       // File output
       << "\n\n File Output"
       << "\n  " << log_cyan << "-o <destination>"
       << log_magenta << " --output <destination>" << log_reset
       << "\n  Log output to file"
       // Verbose
       << "\n\n Verbose"
       << "\n  " << log_cyan << "-b"
       << log_magenta << " --verbose" << log_reset
       << "\n  Verbose output"
       << "\n\n\nMISC:"
       // Help / Usage
       << "\n\n Help"
       << "\n  " << log_cyan << "-h"
       << log_magenta << " --help --usage" << log_reset
       << "\n  Print this help summary page"
       // Version
       << "\n\n Version"
       << "\n  " << log_cyan << "-v"
       << log_magenta << " --version" << log_reset
       << "\n  Get program version"
       << "\n\n\nEXAMPLES:"
       << "\n\n  ./fracmap -d 1.8 -p 3.4 -n 13 -k 0.8 -o out.txt"
       << "\n\n  ./fracmap --fractal_dimension 2.4 --output output.txt -b\n\n" <<endl;
  // specific fatal error
  switch (err)
  {
    case 0:
      Log::fatal("ERROR: Missing required argument.\n");
    case 1:
      Log::fatal("ERROR: Invalid switch.\n");
    case 2:
      Log::fatal("ERROR: Invalid required argument.\n");
  }
}
