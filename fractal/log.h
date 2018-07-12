/* log.hpp
 * Modified: (07/11/18) Chris Hayes
 */
#pragma once
// BOOST - DATE-TIME
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
// BOOST - FILESYSTEM
#include <boost/filesystem.hpp>
// BOOST - LOG
#include <boost/log/expressions.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

#include "settings.h"

// Terminal text color highlighting.
static const std::string log_reset   = "\033[0m";
static const std::string log_black   = "\033[30m"; /* Black */
static const std::string log_red     = "\033[31m"; /* Red */
static const std::string log_green   = "\033[32m"; /* Green */
static const std::string log_yellow  = "\033[33m"; /* Yellow */
static const std::string log_blue    = "\033[34m"; /* Blue */
static const std::string log_magenta = "\033[35m"; /* Magenta */
static const std::string log_cyan    = "\033[36m"; /* Cyan */
static const std::string log_white   = "\033[37m"; /* White */

#define INFO  BOOST_LOG_SEV(my_logger::get(), boost::log::trivial::info) << log_blue
#define WARN  BOOST_LOG_SEV(my_logger::get(), boost::log::trivial::warning) << log_yellow
#define ERROR BOOST_LOG_SEV(my_logger::get(), boost::log::trivial::error) << log_red
#define FATAL BOOST_LOG_SEV(my_logger::get(), boost::log::trivial::fatal) << log_red

#define SYS_LOGFILE "./logs/fracmap_test.log"

//Narrow-char thread-safe logger.
typedef boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> logger_t;

//declares a global logger with a custom initialization
BOOST_LOG_GLOBAL_LOGGER(my_logger, logger_t)
