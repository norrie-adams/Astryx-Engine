// Log
//
// Simple console logging system used to centralize debug output.
// Replaces scattered std::cout usage with a consistent interface.
//
// Current features:
// - Console output only (no file logging)
// - Two log levels: info and error
// - Synchronous (blocking) output via std::cout
//
// Intended for development debugging only.
// Will be expanded in future versions (levels, file output, filtering)

#include "Log.h"
#include <iostream>

// Prints general engine/runtime information to console
void Log::info(const std::string& msg)
{
    std::cout << "[INFO]" << " " << msg << std::endl;
}

// Prints error messages to console for debugging issues
void Log::error(const std::string& msg)
{
    std::cout << "[ERROR]" << " " << msg << std::endl;
}