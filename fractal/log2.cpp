/* log.cpp
 * Modified: (07/11/18) Chris Hayes
 */
#include "log2.hpp"

using namespace std;
namespace logging  = boost::log;
namespace attrs    = boost::log::attributes;
namespace expr     = boost::log::expressions;
namespace src      = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks    = boost::log::sinks;

Log::Log() {
try {
    // The first thing we have to do to get using the library is
    // to set up the logging sinks - i.e. where the logs will be written to.
    logging::add_console_log(std::clog,
                 keywords::format = "%TimeStamp%: %_%",
                 keywords::auto_flush = true);

    // Create a text file sink
    typedef sinks::synchronous_sink<sinks::text_file_backend> file_sink;
    shared_ptr<file_sink> sink(new file_sink(
    // File name pattern.
    keywords::file_name = "%Y%m%d_%H%M%S_%5N.log",
    // Rotation size, in characters
    keywords::rotation_size = 16384,
    // Rotate daily if not more often.  The time is arbitrary.
    keywords::time_based_rotation =
        sinks::file::rotation_at_time_point(4, 33, 17),
    // Flush after write.
    keywords::auto_flush = true));

    // Set up where the rotated files will be stored.
    sink->locked_backend()->set_file_collector(sinks::file::make_collector(
    // Where to store rotated files.
    keywords::target = "logs",
    // Maximum total size of the stored files, in bytes.
    keywords::max_size = 16 * 1024 * 1024,
    // Minimum free space on the drive, in bytes.
    keywords::min_free_space = 100 * 1024 * 1024));

    // Upon restart, scan the target directory for files matching the
    // file_name pattern.
    sink->locked_backend()->scan_for_files();
    boost::log::register_simple_formatter_factory<
    logging::trivial::severity_level, char>("Severity");
    sink->set_formatter(expr::stream
            << expr::attr<boost::posix_time::ptime>("TimeStamp")
            << " " << logging::trivial::severity << "["
            << expr::attr<string>("FileName") << ":"
            << expr::attr<unsigned int>("LineNumber") << "] "
            << expr::smessage);
    // Add it to the core
    logging::core::get()->add_sink(sink);
    // Add some attributes too
    logging::add_common_attributes();
    logging::core::get()->add_global_attribute("TimeStamp",
                           attrs::local_clock());
    logging::core::get()->add_global_attribute(
    "LineNumber", attrs::mutable_constant<unsigned int>(5));
    logging::core::get()->add_global_attribute(
    "FileName", attrs::mutable_constant<string>(""));

    src::severity_logger<logging::trivial::severity_level> slg;
    slg.add_attribute("LineNumber",
              attrs::constant<unsigned int>(__LINE__));
    slg.add_attribute("FileName", attrs::constant<string>(__FILE__));
    for (unsigned int i = 0; i < 2; ++i) {
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Testing log, #" << i;
    }
} catch (std::exception& e) {
    std::cerr << "Failed to establish logging: " << e.what() << std::endl;
    throw LoggingInitException();
}
}

Log::~Log() { boost::log::core::get()->remove_all_sinks(); }

string PathToFilename(const string& path) {
string sub_path = path.substr(path.find_last_of("/\\") + 1);
return sub_path;
}
