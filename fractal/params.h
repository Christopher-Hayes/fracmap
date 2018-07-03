/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *  params.hpp
 *  Author:  Chris Hayes
 *  Created:   Dec 2017
 */
#pragma once
#include <iostream>
#include <getopt.h>

#include "settings.h"

class Params
{
public:
  // Constructors, Deconstructors
  Params() {}
  Params(int, char**);
  // Print usage comment
  static void print_usage(int err = -1);
  // Extract optarg safely
  double extract_double(std::string parameter);
  int extract_int(std::string parameter);
  // Check if param active
  inline bool check_df() const { return _df; }
  inline bool check_kf() const { return _kf; }
  inline bool check_n() const { return _n; }
  inline bool check_k() const { return _k; }
  inline bool check_e() const { return _e; }
  inline bool check_output() const { return _output; }
  inline bool check_verbose() const { return _verbose; }
  inline bool check_usage() const { return _usage; }
  // Get param value
  inline double get_df() const { return _df_v; }
  inline double get_kf() const { return _kf_v; }
  inline int get_n() const { return _n_v; }
  inline double get_k() const { return _k_v; }
  inline double get_e() const { return _e_v; }
  inline const char* get_output() const { return _output_file; }

private:
  // Option values
  const char* _output_file = ""; // const for c++11+ compat.
  double _df_v, _kf_v, _k_v, _e_v;
  int _n_v;
  bool _verbose, _output, _df, _kf, _n, _k, _e, _usage;

  // Long CLI options
  struct option LONG_OPTS[11] = {
    { "verbose",            no_argument,        NULL,  'b' },
    { "output",             required_argument,  NULL,  'o' },
    { "fractal_dimension",  required_argument,  NULL,  'd' },
    { "prefactor",          required_argument,  NULL,  'p' },
    { "monomers",           required_argument,  NULL,  'n' },
    { "overlap",            required_argument,  NULL,  'k' },
    { "epsilon",            required_argument,  NULL,  'e' },
    { "help",               no_argument,        NULL,  'h' },
    { "usage",              no_argument,        NULL,  'h' },
    { "version",            no_argument,        NULL,  'v' },
    { NULL,                 0,                  NULL,   0  }
  };

};
