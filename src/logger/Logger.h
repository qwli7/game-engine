#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

enum LogLevel
{
    INFO,
    ERR,
};

class Logger
{
public:
    static void LogErr(const std::string &message);
    static void LogInfo(const std::string &message);
};

#endif