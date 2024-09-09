#ifndef LOG_LOGGER_H
#define LOG_LOGGER_H

#include <iostream>
#include <string>

namespace Log
{
    void write(std::string msg, bool err);
}

#endif