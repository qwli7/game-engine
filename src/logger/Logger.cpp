#include "Logger.h"

void Logger::LogInfo(const std::string &message)
{
    std::cout << "INFO: " << message << std::endl;
}
void Logger::LogErr(const std::string &message)
{
    std::cerr << "ERROR: " << message << std::endl;
}