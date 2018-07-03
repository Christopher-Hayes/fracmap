/* log.hpp
 * Created: Chris Hayes (06/26/18)
 */
#pragma once
#include <iostream>

// Terminal text color highlighting. TODO: Replace with robust library.
static const std::string log_reset   = "\033[0m";
static const std::string log_black   = "\033[30m"; /* Black */
static const std::string log_red     = "\033[31m"; /* Red */
static const std::string log_green   = "\033[32m"; /* Green */
static const std::string log_yellow  = "\033[33m"; /* Yellow */
static const std::string log_blue    = "\033[34m"; /* Blue */
static const std::string log_magenta = "\033[35m"; /* Magenta */
static const std::string log_cyan    = "\033[36m"; /* Cyan */
static const std::string log_white   = "\033[37m"; /* White */
static const std::string log_bold_black   = "\033[1m\033[30m"; /* Bold Black */
static const std::string log_bold_green   = "\033[1m\033[32m"; /* Bold Green */
static const std::string log_bold_yellow  = "\033[1m\033[33m"; /* Bold Yellow */
static const std::string log_bold_blue    = "\033[1m\033[34m"; /* Bold Blue */
static const std::string log_bold_magenta = "\033[1m\033[35m"; /* Bold Magenta */
static const std::string log_bold_cyan    = "\033[1m\033[36m"; /* Bold Cyan */
static const std::string log_bold_white   = "\033[1m\033[37m"; /* Bold White */
static const std::string log_bold_red     = "\033[1m\033[31m"; /* Bold Red */

class Log
{
  public:
    static Log& get_instance() { static Log instance; return instance; }

    // core logging
    void info(std::string s) {
      if (_info)
        std::cout << log_blue << " INFO: " << s << log_reset << std::endl;
    }

    void warn(std::string s) {
      if (_warn)
        std::cout << log_yellow << " WARNING: " << s << log_reset << std::endl;
    }

    void fatal(std::string s) {
      if (_fatal)
        std::cout << log_red << " ERROR: " << s << log_reset << std::endl;
      exit(0);
    }

    // setters
    void set_info(bool b)  { _info = b;  }
    void set_warn(bool b)  { _warn = b;  }
    void set_fatal(bool b) { _fatal = b; }

  private:
    Log() {}
    bool _info = false, _warn = true, _fatal = true;
  public:
    Log(Log const&)             = delete;
    void operator=(Log const&)  = delete;
};
