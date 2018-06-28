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
  _df_v = _kf_v = _n_v = 0;
  _verbose = _output = _df = _kf = _n = false;
  // process switches
  int code, opt;
  while ((opt = getopt_long(argc, argv, "vo:d:k:n:h", LONG_OPTS, &code)) != -1){
    switch (opt) {
      case 'o': // Output
        _output = true;
        _output_file = optarg; break;
      case 'v': // Verbose
        _verbose = true;       break;
      case 'd': // Fractal Dimension
        _df = true;
        _df_v = atof(optarg);  break;
      case 'k': // Prefactor
        _kf = true;
        _kf_v = atof(optarg);  break;
      case 'n': // Monomer Count
        _n = true;
        _n_v = atof(optarg);   break;
      case 'h': // Help
        _usage = true;
        printUsage(-1);        break;
      case '?':
      default:
        printUsage(1);
    }
  }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// print usage
void
Params::printUsage(int err)
{
  // print usage; modeled from nmap's usage comment
  cout << log_green << "\n\tfracMAP" << log_reset
       << "\n\nUsage:"
       << "\n\t./fractal [Options]"
       << "\n\nInline Command Arguments: (if not, program will prompt)"
       << "\n  -d, --fractal_dimension: Set fractal dimension; Range: [1.0, 3.0]"
       << "\n  -k, --prefactor: Set fractal prefactor; Range: [1.0, inf)"
       << "\n  -n, --monomer_count: Set number of monomers in fractal; Integer > 0"
       << "\n\nOUTPUT:"
       << "\n  -o <destination>,--output <destination>: Log output to file"
       << "\n  -v, --verbose: Verbose output"
       << "\n\nMISC:"
       << "\n  -h, --help, --usage: Print this help summary page"
       << "\n\nEXAMPLES:"
       << "\n  ./fractal -d 1.8 -k 3.4 -n 13 -o out.txt"
       << "\n  ./fractal --fractal_dimension 2.4 --output output.txt -v\n\n" <<endl;
  // specific fatal error or just quit
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
