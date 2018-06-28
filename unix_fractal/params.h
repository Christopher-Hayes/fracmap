/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *  params.hpp
 *  Author:  Chris Hayes
 *  Created:   Dec 2017
 */
#pragma once
#include <iostream>
#include <getopt.h>
#include "log.hpp"

class Params
{
public:
  // Constructors, Deconstructors
  Params() {}
  Params(int, char**);
  // Print usage comment
  static void printUsage(int);
  // Check if param active
  inline bool check_df() const { return _df; }
  inline bool check_kf() const { return _kf; }
  inline bool check_n() const { return _n; }
  inline bool check_output() const { return _output; }
  inline bool check_verbose() const { return _verbose; }
  inline bool check_usage() const { return _usage; }
  // Get param value
  inline int get_df() const { return _df_v; }
  inline int get_kf() const { return _kf_v; }
  inline int get_n() const { return _n_v; }
  inline const char* get_output() const { return _output_file; }

private:
  // Option values
  const char* _output_file = ""; // const for c++11+ compat.
  int _df_v, _kf_v, _n_v;
  bool _verbose, _output, _df, _kf, _n, _usage;

  // Long CLI options
  struct option LONG_OPTS[8] = {
    { "verbose",            no_argument,        NULL,  'v' },
    { "output",             required_argument,  NULL,  'o' },
    { "fractal_dimension",  required_argument,  NULL,  'd' },
    { "prefactor",          required_argument,  NULL,  'k' },
    { "monomer_count",      required_argument,  NULL,  'n' },
    { "help",               no_argument,        NULL,  'h' },
    { "usage",              no_argument,        NULL,  'h' },
    { NULL,                 0,                  NULL,   0  }
  };

};
