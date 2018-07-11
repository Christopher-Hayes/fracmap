/* log.hpp
 * Modified: (07/11/18) Chris Hayes
 */
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>

// An exception if logging fails to initialize.
class LoggingInitException : public std::exception {};

/*
  Class to set up logging as we want it in all services.

  Instantiate a Log object near the beginning of main().
*/
class Log {
   public:
    Log();
    ~Log();
};

// Logging macro that includes severity, filename, and line number.
// Copied and modified from
// https://stackoverflow.com/questions/24750218/boost-log-to-print-source-code-file-name-and-line-number
// Set attribute and return the new value
template <typename ValueType>
ValueType SetGetAttrib(const char* name, ValueType value) {
    auto attr = boost::log::attribute_cast<
        boost::log::attributes::mutable_constant<ValueType>>(
        boost::log::core::get()->get_global_attributes()[name]);
    attr.set(value);
    return attr.get();
}

// Convert file path to only the filename
std::string PathToFilename(const std::string& path);

// Shortcut to declare a log source.  To insert in each function that will call
// the LOG macro.
#define LOGGABLE                                                              \
    boost::log::sources::severity_logger<boost::log::trivial::severity_level> \
        slg;

#define LOG(sev)                                                 \
    BOOST_LOG_STREAM_WITH_PARAMS(                                \
        (slg),                                                   \
        (SetGetAttrib("FileName", PathToFilename(__FILE__)))(    \
            SetGetAttrib("LineNumber", (unsigned int)__LINE__))( \
            ::boost::log::keywords::severity = (boost::log::trivial::sev)))
