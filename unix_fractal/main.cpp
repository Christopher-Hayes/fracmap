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
using namespace std;

#include "fractal.h"
#include "log.hpp"
#include "settings.h"
#include "micrograph.h"
#include "params.h"

enum {escape, key_0, key_1, key_2, key_3};

bool
generate_fractal(Fractal *base, int fractal_size, bool output) {
  // Create polynomer.
  for (int removals=0; (int)base->size() < fractal_size;) {
    // Attempt to create monomer.
    base->create_monomer();
    // Successfully created new monomer.
    if (output) {
      cout << "Fractal Size: " << (int)base->size() 
           << " of " << fractal_size << endl;
    }
  }
	return true;
}
// Testing? --------------------------------------------------------------------
void
pre_programmed_thread(int cpuNum, int cpus) {
  const int Min_Size = 10, Max_Size = 500;
  const double minK = .9, maxK = 1.1, Kstep = 0.05;
  const double minD = 1.0, maxD = 3.0, Dstep = .01, Dtotal = (maxD - minD)/Dstep;
  const unsigned int Num_Trials = 100;

  ofstream outputStable, outputUnstable;
  Fractal *base;
  
  double k = 1.19;
  for(double D = minD; D < maxD; D+=Dstep) {
	for(unsigned int i = cpuNum; i < Num_Trials; i+=cpus) {
	  unsigned int N = (double)rand() / RAND_MAX * (Max_Size - Min_Size) + Min_Size;
	  //Start from nothing
	  base = new Fractal();
	  
	  base->set_Df(D);
	  base->set_kf(k);
	  
	  if( generate_fractal(base, N, false) ) //Create a fractal for the given parameters. 
	  {
		
		char fileStable[255];
		char fileUnstable[255];
		
		sprintf( fileStable, "%s_%g_%g_%03u_%03u.txt", "stable", k, D, N, i );
		outputStable.open(fileStable, ios::trunc);
		
		sprintf( fileUnstable, "%s_%g_%g_%03u_%03u.txt", "unstable", k, D, N, i );
		outputUnstable.open(fileUnstable, ios::trunc);
		
		base->orient_random(outputStable, 25, true); //Conduct Analysis
		
		base->orient_random(outputUnstable, 25, false); //Conduct Analysis
		
		outputStable.close();		
		outputUnstable.close();
		
		delete base;
	  }
	}
  }
}
// Testing? --------------------------------------------------------------------
void 
pre_programmed() {
  const int cpus = 4;
  int* pids = new int[cpus];

  // This is really rudimentary multithreading using fork.
  // Pthreads should likely be used in the future, but since the threads don't need to communicate, fork works well.

  for (int k=0; k<cpus; k++) {
    if ((pids[k] = fork()) == 0) {
      pre_programmed_thread(k, cpus);
      exit(3); 
    }
    sleep(1); // Different seeds
  }

  for (int k=0; k<cpus; k++) {
    int status = 0;
    do {
      waitpid(pids[k], &status, 0);
    } while(!WIFEXITED(status));
  }
}
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
// Get user input --------------------------------------------------------------
/*
int 
get_user_input(Fractal & base) {
	int key;
	print_menu(base);
	cin >> key;
	return key;
}
*/
// Parse user input. -----------------------------------------------------------
/*
int 
parse_input(int argc, char **argv, Fractal & f) {
	if (argc == 1 || argc < 4) {
		return -1;
    } else {
		cout << "Converting" << endl;
		double Df = atof(argv[1]);
        double kf = atof(argv[2]);
		int size = atoi(argv[3]);
		if (Df >= 1.0 && Df <= 3.0) {
			f.set_Df(Df);
		} else {
			print_input_error(argv[0],"Invalid Fractal Dimension.  Range: [1.0, 3.0]");
			return -1;
		}
		
		if (kf >= 1.0) {
			f.set_kf(kf);
		} else {
			print_input_error(argv[0],"Invalid Prefactor.  Range: [1.0, inf)");
			return -1;
		}
		
		if (size <= 0) {
			print_input_error(argv[0],"Invalid Size. Range: Integer > 0");
			return -1;
		} else {
			cout << "Successfully Returning Size." << endl;
			return size;
		}
	}
}
*/
// Generate fractal ------------------------------------------------------------
/*
void 
create_fractal(Fractal& base, int argc, char** argv) {
	int fractal_size;
	int n_argc = argc;
	char **n_argv;
	
	n_argv = (char **)malloc(sizeof(char *) * 4);
	for (int i = 0; i < 4; i++) {
		n_argv[i] = (char *) malloc(sizeof(char) * 128);
	}
	
	for (int i = 0; i < argc; i++)
		strcpy(n_argv[i], argv[i]);
	
	base.clear();
	
	while (!((fractal_size = parse_input(n_argc, n_argv, base)) > 0)) {
		char answer[128];
        for (;;) {
			cout << "Proceed with prearranged program?(yes/no)" << endl;
			cin >> answer;
			if(strncmp(answer, "yes", 3) == 0)
			{
				pre_programmed();
				exit(0);
			}
			else if(strncmp(answer, "no", 2) == 0)
			{
				cout << "Fractal Dimension? Range: [1.0, 3.0]" << endl;
				cin >> n_argv[1];
				cout << log_bold_white << "Prefactor? Range: [1.0, inf)" << endl;
				cin >> n_argv[2];
				cout << "Fractal Size? (Integer greater than 0)" << endl;
				cin >> n_argv[3];
				n_argc = 4;
				break;
			}
			else
			{
				cout << "Please answer \"yes\" or \"no\"." << endl;
			}
		}
	}
    
	generate_fractal(&base, fractal_size, true);
}
*/
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
// Fractal Creation ============================================================
void
fractal_params(double& df, double& kf, int& n) {

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
  if (n == -1.0) {
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
// Program entry point ---------------------------------------------------------
int
main(int argc, char **argv) {
  srand((unsigned int)time(NULL));

  Params p = Params(argc, argv);
  // Quit out if usage/help parameter is active.
  if (p.check_usage())
    return 0;
  // Verbose
  if (p.check_verbose()) {
    log_info = true;
    Log::info("Verbose mode ON");
  }

	Fractal base;
  double df = -1; // Fractal Dimension
  double kf = -1; // Prefactor
  int n = -1; // Monomer Count

  // Fractal Dimension
  if (p.check_df())
  // Prefactor
  if (p.check_kf())
    kf = p.get_kf();
  // Monomer Count
  if (p.check_n())
    n = p.get_n();
	
  // Program loop; on first run - new fractal
	for (int key = key_0;;) {
    switch (key)
    {
      case escape: // Quit
        return 0;
      case key_0: // New fractal
        // Validate / get params
        validate_df(df);
        validate_kf(kf);
        validate_n(n);
        // Generate fractal
        for (;(int)base.size() < n;) {
          base.create_monomer();
          // Log::info("Fractal size: " + std::to_string(base.size()) + "/" + std::to_string(n)); // TODO: figure out why c++11 is kicking in
        }
      case key_1: // Structure Factor
        struct_factor(base);
        break;
      case key_2: // Micrograph analysis
        micro_analysis(base);
        break;
      case key_3: // Help
        cout << "Help:" << endl;
        break;
      default: // Catch all invalid input
        Log::warn("Invalid menu option.\n");
        break;					
    }
    // Print main menu; get user input
    print_menu();
    cin >> key;
	}

  Log::info("Program terminated successfully.\n");
	return 0;
}
