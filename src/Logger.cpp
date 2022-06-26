#include <iostream>
#include "Logger.h"

log::Logger *log::Logger::s_loggerPtr = nullptr;
std::mutex log::Logger::s_mutex;

log::Logger *log::Logger::get()
{
    if (!s_loggerPtr)
    {
        std::lock_guard<std::mutex> lock1(s_mutex);
        if (!s_loggerPtr)
            s_loggerPtr = new Logger();
    }

    return s_loggerPtr;
}

void log::Logger::deleteInstance()
{
    std::lock_guard<std::mutex> lock2(s_mutex);
    if (s_loggerPtr)
    {
        delete s_loggerPtr;
        s_loggerPtr = nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
std::mutex log::Logger5::s_mutex;
log::Logger5 *log::Logger5::s_loggerPtr = nullptr;
std::once_flag log::Logger5::s_once;

log::Logger5 *log::Logger5::get()
{
    std::call_once(s_once, [&]()
                   {
                    if(!s_loggerPtr)
                     s_loggerPtr = new Logger5(); });
    return s_loggerPtr;
}

void log::Logger5::deleteInstance()
{
    std::lock_guard<std::mutex> lock(s_mutex);

    if (s_loggerPtr)
    {
        delete s_loggerPtr;
        s_loggerPtr = nullptr;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////

log::Logger4 *log::Logger4::s_loggerPtr = new log::Logger4();
std::mutex log::Logger4::s_mutex;

log::Logger4 *log::Logger4::get()
{
    return s_loggerPtr;
}

void log::Logger4::deleteInstance()
{
    std::lock_guard<std::mutex> lock(s_mutex);

    if (s_loggerPtr)
    {
        delete s_loggerPtr;
        s_loggerPtr = nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
std::mutex log::Logger3::s_mutex;
log::Logger3 *log::Logger3::s_log = nullptr;

log::Logger3 *log::Logger3::get()
{
    std::lock_guard<std::mutex> lock1(s_mutex);
    if (!s_log)
    {
        s_log = new Logger3();
    }

    return s_log;
}

void log::Logger3::deleteInstance()
{
    std::lock_guard<std::mutex> lock2(s_mutex);
    if (!s_log)
    {
        delete s_log;
        s_log = nullptr;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////

std::mutex log::Logger2::s_mutex;

log::Logger2 &log::Logger2::get()
{
    // Inefficient as the mutex is needed only while the object creation
    std::lock_guard<std::mutex> lock1(s_mutex);
    static log::Logger2 log;
    return log;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

log::Logger1 log::Logger1::s_log;

log::Logger1 &log::Logger1::get()
{
    return s_log;
}