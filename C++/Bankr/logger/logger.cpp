#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "logger.h"

Logger::Logger(){
    std::ofstream logfile(LOG_PATH, std::ios::app);
    if(!logfile.is_open()){
        std::cerr << "Error creating log file!\n";
    }
    else{
        logfile << "----- New Session -----\n"; 
        logfile.close();
    }
}

Logger::~Logger(){
    std::ofstream logfile(LOG_PATH, std::ios::app);
    if(!logfile.is_open()){
        std::cerr << "Error creating log file!\n";
    }
    else{
        logfile << "----- Session Ended -----\n"; 
        logfile.close();
    }
}

void Logger::log(std::string msg, logLevel logLevel){
    std::ofstream logfile(LOG_PATH, std::ios::app);
    if(!logfile.is_open()){
        std::cerr << "Error opening log file!\n";
        return;
    }
    else{
        time_t time = this->getCurrentTime();
        std::string timestamp = std::ctime(&time);
        timestamp.pop_back();
        logfile << "[" << this->levelToString(logLevel) << "] " << msg << " (" << timestamp << ")\n";
        logfile.close();
    }
}

std::string Logger::levelToString(logLevel logLevel){
    switch(logLevel){
        case INFO: return "INFO";
        case WARN: return "WARN";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

time_t Logger::getCurrentTime(){
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

void Logger::deleteLog(){
    std::ofstream logfile(LOG_PATH, std::ofstream::trunc);
    if(!logfile.is_open()){
        std::cerr << "Error opening log file!\n";
    }
    else{
        logfile.close();
    }
}