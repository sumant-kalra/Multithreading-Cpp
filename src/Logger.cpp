#include <iostream>
#include "Logger.h"

log::Logger *log::Logger::m_loggerPtr = nullptr;

log::Logger *log::Logger::get()
{
    if (!m_loggerPtr)
        m_loggerPtr = new Logger();
    return m_loggerPtr;
}

void log::Logger::deleteInstance()
{
    if (m_loggerPtr)
    {
        delete m_loggerPtr;
        m_loggerPtr = nullptr;
    }
}

void log::Logger::logINFO(const std::string &message)
{
    std::cout << "[INFO] " << message << "\n";
}

void log::Logger::logWARNING(const std::string &message)
{
    std::cout << "[WARNING] " << message << "\n";
}

void log::Logger::logERROR(const std::string &message)
{
    std::cout << "[ERROR] " << message << "\n";
}

void log::Logger::logInfo(const std::string &message)
{
    log::Logger::get()->logINFO(message);
}

void log::Logger::logWarning(const std::string &message)
{
    log::Logger::get()->logWARNING(message);
}

void log::Logger::logError(const std::string &message)
{
    log::Logger::get()->logERROR(message);
}

#if 0

// Object created on Data segment

std::mutex log::Logger::m_mutex;

log::Logger &log::Logger::get()
{
    static Logger log;
    return log;
}

void log::Logger::logINFO(const std::string &message)
{
    std::cout << "[INFO] " << message << "\n";
}

void log::Logger::logWARNING(const std::string &message)
{
    std::cout << "[WARNING] " << message << "\n";
}

void log::Logger::logERROR(const std::string &message)
{
    std::cout << "[ERROR] " << message << "\n";
}

void log::Logger::logInfo(const std::string &message)
{
    std::lock_guard<std::mutex> lock1(m_mutex);
    log::Logger::get().logINFO(message);
}

void log::Logger::logWarning(const std::string &message)
{
    std::lock_guard<std::mutex> lock2(m_mutex);
    log::Logger::get().logWARNING(message);
}

void log::Logger::logError(const std::string &message)
{
    std::lock_guard<std::mutex> lock3(m_mutex);
    log::Logger::get().logERROR(message);
}

#endif