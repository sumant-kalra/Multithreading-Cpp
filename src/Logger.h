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
        static std::mutex s_mutex;

        static Logger *s_loggerPtr;

        static Logger *get();

        Logger() = default;
        ~Logger() = default;

        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;

    public:
        static void deleteInstance();
    };

}

namespace log
{
    class Logger5
    {
    private:
        static std::mutex s_mutex;
        static std::once_flag s_once;

        static Logger5 *s_loggerPtr;

        static Logger5 *get();

        Logger5() = default;
        ~Logger5() = default;

        Logger5(const Logger5 &) = delete;
        Logger5 &operator=(const Logger5 &) = delete;

    public:
        static void deleteInstance();
    };

}

namespace log
{
    class Logger4
    {
    private:
        static std::mutex s_mutex;

        static Logger4 *s_loggerPtr;

        static Logger4 *get();

        Logger4() = default;
        ~Logger4() = default;

        Logger4(const Logger4 &) = delete;
        Logger4 &operator=(const Logger4 &) = delete;

    public:
        static void deleteInstance();
    };

}

namespace log
{
    class Logger3
    {
    private:
        static std::mutex s_mutex;
        static Logger3 *s_log;
        static Logger3 *get();

        Logger3() = default;
        ~Logger3() = default;
        Logger3(const Logger3 &) = delete;
        Logger3 &operator=(const Logger3 &) = delete;

    public:
        /// deleteInstance implementation is required to free the memory manually
        /// because m_loggerPtr is a static variable in the data segment that
        /// gets deleted only the end of the program, which means delete on
        /// the heap allocated memory is called only at the termination of the program.
        static void deleteInstance();
    };
}

namespace log
{
    class Logger2
    {
    private:
        static std::mutex s_mutex;
        static Logger2 &get();

        Logger2() = default;
        ~Logger2() = default;
        Logger2(const Logger2 &) = delete;
        Logger2 &operator=(const Logger2 &) = delete;
    };
}

namespace log
{
    // Does not need to be synchronized as the instance is created at the start of the program in the data segment,
    // before any thread calls the get() method
    class Logger1
    {
    private:
        static Logger1 s_log;
        static Logger1 &get();

        Logger1() = default;
        ~Logger1() = default;
        Logger1(const Logger1 &) = delete;
        Logger1 &operator=(const Logger1 &) = delete;
    };

}
