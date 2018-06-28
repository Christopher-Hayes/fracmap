/* log.hpp
 * Created: Chris Hayes (06/26/18)
 */
#pragma once
#include <iostream>
using namespace std;

// TODO: put this mess in a singleton

// Terminal text color highlighting. TODO: Replace with robust library.
static const string log_reset = "\033[0m";
static const string log_black = "\033[30m";   /* Black */
static const string log_red = "\033[31m";     /* Red */
static const string log_green = "\033[32m";   /* Green */
static const string log_yellow = "\033[33m";  /* Yellow */
static const string log_blue = "\033[34m";    /* Blue */
static const string log_magenta = "\033[35m"; /* Magenta */
static const string log_cyan = "\033[36m";    /* Cyan */
static const string log_white = "\033[37m";   /* White */
static const string log_bold_black = "\033[1m\033[30m";   /* Bold Black */
static const string log_bold_green = "\033[1m\033[32m";   /* Bold Green */
static const string log_bold_yellow = "\033[1m\033[33m";  /* Bold Yellow */
static const string log_bold_blue = "\033[1m\033[34m";    /* Bold Blue */
static const string log_bold_magenta = "\033[1m\033[35m"; /* Bold Magenta */
static const string log_bold_cyan = "\033[1m\033[36m";    /* Bold Cyan */
static const string log_bold_white = "\033[1m\033[37m";   /* Bold White */
static const string log_bold_red = "\033[1m\033[31m";     /* Bold Red */

// Output..
static bool log_info = false;
static bool log_warn = true;
static bool log_fatal = true;

struct Log
{
  // Info; verbose mode
  static void info(string s) {
    if (log_info)
      cout << log_blue << " INFO: " << log_reset << s << endl;
  }

  // Warning.
  static void warn(string s) {
    if (log_warn)
      cout << log_yellow << " WARNING: " << log_reset << s << endl;
  }

  // FATAL error; Exit program after printing message
  static void fatal(string s) {
    if (log_fatal)
      cout << log_red << " FATAL: " << log_reset << s << endl;
    exit(0);
  }
};

// TODO: output to file, special ostream handling
