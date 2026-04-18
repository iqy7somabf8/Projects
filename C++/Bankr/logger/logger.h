#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <filesystem>

enum logLevel { INFO, WARN, ERROR }; 

class Logger{
private:
const std::string LOG_PATH = "data/log.txt";

std::string getLogPath();

public:
    Logger();
    ~Logger();
    
    void log(std::string msg, logLevel logLevel);

    std::string levelToString(logLevel logLevel);

    time_t getCurrentTime();

    void deleteLog();
};

#endif