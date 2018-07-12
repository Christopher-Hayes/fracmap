/* log.cpp
 * Modified: (07/11/18) Chris Hayes
 */
#include "log.h"
#include <ostream>

namespace attrs   = boost::log::attributes;
namespace expr    = boost::log::expressions;
namespace logging = boost::log;

void coloring_formatter(
    logging::record_view const& rec, logging::formatting_ostream& strm)
{
    auto severity = rec[logging::trivial::severity];
    if (severity)
    {
        // Set the color
        switch (severity.get())
        {
        case logging::trivial::severity_level::info:
            strm << "\033[32m";
            break;
        case logging::trivial::severity_level::warning:
            strm << "\033[33m";
            break;
        case logging::trivial::severity_level::error:
        case logging::trivial::severity_level::fatal:
            strm << "\033[31m";
            break;
        default:
            break;
        }
    }

    // Format the message here...
    strm << rec[logging::expressions::smessage];

    if (severity)
    {
        // Restore the default color
        strm << "\033[0m";
    }
}

// Credit: @Shiftee https://stackoverflow.com/a/22068278/2096769
// Defines a global logger initialization routine
BOOST_LOG_GLOBAL_LOGGER_INIT(my_logger, logger_t) {
  logger_t lg;

  logging::add_common_attributes();

  // File logger
  boost::posix_time::ptime now = boost::posix_time::second_clock::universal_time();

  std::string log_name(FormatTime(now));
  log_name = "./logs/" + log_name + ".txt";
  logging::add_file_log(
    boost::log::keywords::file_name = log_name,
    boost::log::keywords::format = (
      expr::stream << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
      << " [" << expr::attr< boost::log::trivial::severity_level>("Severity") << "]: "
      << expr::smessage
    )
  );

  // Console logger
  logging::add_console_log(
    std::cout,
    boost::log::keywords::format = (
      expr::stream << expr::format_date_time<boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
      << " [" << expr::attr<boost::log::trivial::severity_level >("Severity") << "]: "
      << expr::smessage << log_reset
    )
  );

  return lg;
}
