#define MAIN 1
#if MAIN
#include <iostream>
#include "Logger.h"

int main(int argc, char *argv[])
{
    log::Logger::logInfo("Hello World!");
    log::Logger::logWarning("Hello World!");
    log::Logger::logError("Hello World!");
    return 0;
}
#endif