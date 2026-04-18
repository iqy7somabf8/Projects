#include "account.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <ctime>
#include <string>
#include "../logger/logger.h"

Logger logger;

Account::Account(std::string tempName) : name(tempName) {}

Account::Account(std::string name, std::string password, dob dateOfBirth, int initialMoney) : name(name), password(password), dateOfBirth(dateOfBirth), accountExists(true), loggedIn(true), money(initialMoney){
        this->generateInterestRate();
        std::ofstream history(HISTORY_PATH);
        if(!history.is_open()){
            std::cerr << "Error creating history file!\n";
            logger.log("Error opening history file!", ERROR);
        }
        else {
            this->debugOutput("History file found!");
            logger.log("History file found", INFO);
            history.close();
        }
        logger.log("Account created for " + this->name, INFO);
        this->saveAccountToFile();
    }

    Account::~Account(){}

std::string Account::getName(){return name;}
std::string Account::getPassword(){return password;}
int Account::getDobYear(){return dateOfBirth.year;}
int Account::getDobMonth(){return dateOfBirth.month;}
int Account::getDobDay(){return dateOfBirth.day;}
int Account::getMoney(){return money;}
bool Account::getAccountExists(){return accountExists;}
bool Account::getLoggedIn(){return loggedIn;}
bool Account::getDebug(){return debug;}
int Account::getYear(){return year;}
double Account::getInterest(){return interest;}
time_t Account::getCurrentTime(){return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());}
int Account::getCurrentYear(){
    std::time_t time = std::time(nullptr);
    std::tm* tm = std::localtime(&time);
    return tm->tm_year + 1900;
}

void Account::setName(std::string sName){name = sName;}
void Account::setPassword(std::string sPassword){password = sPassword;}
void Account::setDobYear(int sDobYear){dateOfBirth.year = sDobYear;}
void Account::setDobMonth(int sDobMonth){dateOfBirth.month = sDobMonth;}
void Account::setDobDay(int sDobDay){dateOfBirth.day = sDobDay;}
void Account::setAccountExists(bool sAccountExists){accountExists = sAccountExists;}
void Account::setLoggedIn(bool sLoggedIn){loggedIn = sLoggedIn;}
void Account::setDebug(bool sDebug){debug = sDebug;}
void Account::setYear(int sYear){year = sYear;}


void Account::deposit(int amount){money += amount; logger.log("Deposit called", INFO);}
void Account::withdraw(int amount){money -= amount; logger.log("Withdraw called", INFO);}

void Account::addHistory(std::string input){
    std::ofstream history(HISTORY_PATH, std::ios::app);
    if(!history.is_open()){
        std::cerr << "Error opening history file!\n";
        logger.log("Error opening history file", ERROR);
        return;
    }
    history << input << "\n";
    history.close();
    logger.log("History modified", INFO);
}

    void Account::deleteHistory(){
        std::ofstream history(HISTORY_PATH, std::ofstream::trunc);
        if(!history.is_open()){
            std::cerr << "Error opening history file!\n";
            logger.log("Error opening history file", ERROR);
            return;
        }
        logger.log("History deleted!", INFO);
        history.close();
        logger.log("History deleted!", INFO);
    }

    void Account::debugOutput(std::string message){
        if(this->debug){
            std::cout << "[DEBUG] " << message << "\n";
        }
    }

    void Account::outputHistory(){
        std::string output;
        std::ifstream history(HISTORY_PATH);
        while(std::getline(history, output)){
            std::cout << output << "\n";
        }
        history.close();
    }

    bool Account::checkAccountFile(){
        std::ifstream acc(ACCOUNT_PATH);
        if(!acc.is_open() || !acc.peek()){
            this->debugOutput("Account file not found / no data!");
            logger.log("Account file not found / no data!", WARN);
            return false;
        }
        acc.close();
        logger.log("Account file found!", INFO);
        return true;
    }

    void Account::saveAccountToFile(){
        std::ofstream acc(ACCOUNT_PATH);
        acc << "name=" << this->name << "\n" 
            << "password=" << this->password << "\n" 
            << "dob_day=" << this->dateOfBirth.day << "\n" 
            << "dob_month=" << this->dateOfBirth.month << "\n" 
            << "dob_year=" << this->dateOfBirth.year << "\n"
            << "balance=" << this->money << "\n"
            << "interest=" << this->interest << "\n"
            << "year=" << this->year << "\n";
        acc.close();
        this->debugOutput("Account data saved to file!");
        logger.log("Account data saved to file!", INFO);
    }

    void Account::loadAccountFromFile(){
        std::ifstream acc(ACCOUNT_PATH);
        if(!acc.is_open() || !acc.peek()){
            std::cerr << "Error opening acccount file!\n";
            logger.log("Error opening account file!", ERROR); 
            return;
        }
        std::string data;
        while(std::getline(acc, data)){
            auto pos = data.find('=');
            if(pos == std::string::npos) continue;

            std::string key = data.substr(0, pos);
            std::string value = data.substr(pos + 1);
            if(key == "name") this->name = value;
            else if(key == "password") this->password = value;
            else if(key == "dob_day") this->dateOfBirth.day = std::stoi(value);
            else if(key == "dob_month") this->dateOfBirth.month = std::stoi(value);
            else if(key == "dob_year") this->dateOfBirth.year = std::stoi(value);
            else if(key == "balance") this->money = std::stoi(value);
            else if(key == "interest") this->interest = std::stod(value);
            else if(key == "year") this->year = std::stoi(value);
        }
        this->accountExists = true;
        this->loggedIn = false;
        acc.close();
        this->debugOutput("Account data loaded from file!");
        logger.log("Account data loaded from file!", INFO);
    }

    void Account::saveConfigToFile(){
        std::ofstream config(CONFIG_PATH);
        if(!config.is_open()){
            std::cerr << "Error opening config file!\n";
            logger.log("Error opening config file", ERROR);
            return;
        }
        config << "debug=" << this->debug << "\n";
        config.close();
        this->debugOutput("Config saved to file!");
        logger.log("Config saved to file!", INFO);
    }

    void Account::loadConfigFromFile(){
        std::ifstream config(CONFIG_PATH);
        if(!config.is_open() || !config.peek()){
            std::cerr << "Error opening config file!\n";
            logger.log("Error opening config file!", ERROR);
            return;
        }
        std::string data;
        while(std::getline(config, data)){
            auto pos = data.find('=');
            if(pos == std::string::npos) continue;

            std::string key = data.substr(0, pos);
            std::string value = data.substr(pos + 1);
            if(key == "debug") this->debug = (value == "1" ? true : false);
        }
        config.close();
        this->debugOutput("Config loaded from file!");
        logger.log("Config loaded from file!", INFO);
    }

    bool Account::checkConfigFile(){
        std::ifstream config(CONFIG_PATH);
        if(!config.is_open() || !config.peek()){
            this-> debugOutput("Config file not found / no data!");
            logger.log("Config file not found / no data!", WARN);
            return false;
        }
        else {
            this->debugOutput("Config file found!");
            logger.log("Config file found!", INFO);
            config.close();
            return true;
        }
    }

    void Account::generateInterestRate(){
        static std::random_device rd; //Why ts gotta be so complicated
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.02, 1.04); //Pick random interest between 2% and 4%. ofc with 5 trillion decimals :/
        this->interest = dis(gen);
        this->debugOutput("Generated new interest rate: " + std::to_string(this->interest));
        logger.log("Generated new interest rate: " + std::to_string(this->interest), INFO);
    }

    void Account::calculateInterest(){
        this->money = money * interest;
        std::time_t time = this->getCurrentTime();
        this->addHistory("Interest of " + std::to_string(this->interest) + " applied on " + std::ctime(&time));
        this->debugOutput("Interest of " + std::to_string(this->interest) + " applied! New balance: " + std::to_string(this->money));
        logger.log("Interest applied!", INFO);
    }


    std::string Account::getFullDob(){return std::to_string(this->getDobDay()) + "/" + std::to_string(this->getDobMonth()) + "/" + std::to_string(this->getDobYear());}