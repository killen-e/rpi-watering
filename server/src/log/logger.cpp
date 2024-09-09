#include "logger.hpp"

namespace Log
{
    void write(std::string msg, bool err)
    {
        std::cout << (err ? "ERROR: " : "INFO: ") << msg << std::endl;
    }
}