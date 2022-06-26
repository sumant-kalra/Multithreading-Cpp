/**
 * @file Logger.h
 * @author Sumant Kalra (sumantkalra@outlook.com)
 * @brief  Logger class
 * Note that it is assumed that the standard output is accessed only via Log class
 * No other method in the program accesses the standard output directly
 * This class is thread safe with the assumption that no other part of the program uses standard ouput
 * @version 0.1
 * @date 2022-06-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <string>
#include <mutex>

namespace log
{
    class Logger
    {
    private:
        static Logger *m_loggerPtr;

        Logger() = default;
        ~Logger() = default;

        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;

        static Logger *get();

        /// deleteInstance implementation is required to free the memory manually
        /// because m_loggerPtr is a static variable in the data segment that
        /// gets deleted only the end of the program, which means delete on
        /// the heap allocated memory is called only at the termination of the program.
        void logINFO(const std::string &message);
        void logWARNING(const std::string &message);
        void logERROR(const std::string &message);

    public:
        static void logInfo(const std::string &message);
        static void logWarning(const std::string &message);
        static void logError(const std::string &message);
        static void deleteInstance();
    };

}

#if 0
// Object created on Data Segment
namespace log
{
    class Logger
    {
    private:
        static std::mutex m_mutex;

        Logger() = default;
        ~Logger() = default;
        static Logger &get();

        void logINFO(const std::string &message);
        void logWARNING(const std::string &message);
        void logERROR(const std::string &message);

    public:
        static void logInfo(const std::string &message);
        static void logWarning(const std::string &message);
        static void logError(const std::string &message);
    };

}
#endif