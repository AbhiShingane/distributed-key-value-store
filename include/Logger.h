#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

class Logger
{
public:
    static bool isDebugEnabled()
    {
        static bool enabled = []()
        {
            const char* value = std::getenv("KVSTORE_DEBUG");

            if (value == nullptr)
            {
                return false;
            }

            std::string str(value);

            return str == "1" ||
                   str == "true" ||
                   str == "TRUE" ||
                   str == "on";
        }();

        return enabled;
    }

    template<typename T>
    static void debug(const T& message)
    {
        if (isDebugEnabled())
        {
            std::cout << "[DEBUG] "
                      << message
                      << std::endl;
        }
    }

    template<typename T>
    static void info(const T& message)
    {
        std::cout << message << std::endl;
    }

    template<typename T>
    static void error(const T& message)
    {
        std::cerr << "[ERROR] "
                  << message
                  << std::endl;
    }
};