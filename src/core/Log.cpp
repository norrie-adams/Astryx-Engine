#include "Log.h"
#include <iostream>

void Log::info(const std::string& msg)
{
    std::cout << "[INFO]" << msg << std::endl;
}

void Log::error(const std::string& msg)
{
    std::cout << "[ERROR]" << msg << std::endl;
}