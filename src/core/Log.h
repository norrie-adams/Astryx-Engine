#pragma once
#include <string>

class Log
{
public:
    static void info(const std::string& msg);
    static void error(const std::string& msg);
};