#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <memory>
#include "../logger/logger.h"

class Account{
private:
    std::string name;
    std::string password;
    typedef struct{
    int year; //dob = Date of Birth
    int month;
    int day;
    } dob;
    dob dateOfBirth;
    bool accountExists = false;
    bool loggedIn = false;
    int money = 0;
    bool debug = false;
    double interest = 0;
    int year = 67; //so unfunny tho
    const std::string ACCOUNT_PATH = "data/account.txt";
    const std::string HISTORY_PATH = "data/history.txt";
    const std::string CONFIG_PATH  = "data/config.txt";

public:
    Account(std::string tempName);
    Account(std::string name, std::string password, dob dateOfBirth, int initialMoney = 0);
    ~Account();

    std::string getName();
    std::string getPassword();
    int getDobYear();
    int getDobMonth();
    int getDobDay();
    int getMoney();
    bool getAccountExists();
    bool getLoggedIn();
    bool getDebug();
    int getYear();
    double getInterest();
    time_t getCurrentTime();
    int getCurrentYear();

    void setName(std::string sName);
    void setPassword(std::string sPassword);
    void setDobYear(int sDobYear);
    void setDobMonth(int sDobMonth);
    void setDobDay(int sDobDay);
    void setAccountExists(bool sAccountExists);
    void setLoggedIn(bool sLoggedIn);
    void setDebug(bool sDebug);
    void setYear(int sYear);

    void deposit(int amount);
    void withdraw(int amount);

    void addHistory(std::string input);

    void deleteHistory();

    void debugOutput(std::string message);

    void outputHistory();

    bool checkAccountFile();

    void saveAccountToFile();

    void loadAccountFromFile();

    void saveConfigToFile();

    void loadConfigFromFile();

    bool checkConfigFile();

    void generateInterestRate();

    void calculateInterest();


    std::string getFullDob();
};

#endif