#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

class Log {
    public:
        template<typename... Args>
        static void Info(Args... args) {
            (std::cout << "\033[32m[INFO] " << ... << args) << "\033[0m\n";
        }

        template<typename... Args>
        static void Warn(Args... args) {
            (std::cout << "\033[33m[WARN] " << ... << args) << "\033[0m\n";
        }

        template<typename... Args>
        static void Error(Args... args) {
            (std::cout << "\033[31m[ERROR] " << ... << args) << "\033[0m\n";
        }

        template<typename... Args>
        static void Fatal(Args... args) {
            (std::cout << "\033[91m[FATAL] " << ... << args) << "\033[0m\n";
            std::abort();
        }
};