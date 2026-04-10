#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cctype>
#include <chrono>
#include <fstream>
#include <filesystem>

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
    int money = 0;
    bool accountExists = false;
    bool loggedIn = false;
    bool debug = true;

public:
    Account(std::string tempName) : name(tempName){}

    Account(std::string name, std::string password, dob dateOfBirth, int initialMoney = 0) : name(name), password(password), dateOfBirth(dateOfBirth), accountExists(true), loggedIn(true), money(initialMoney){
        std::ifstream history("history.txt");
        if(!history.is_open()){
            this->debugOutput("Error creating history file!");
        }
        else {
            this->debugOutput("History file found!");
            history.close();
        }
            this->saveAccountToFile();
    }

    ~Account(){}                  

    std::string getName(){return name;}
    std::string getPassword(){return password;}
    int getDobYear(){return dateOfBirth.year;}
    int getDobMonth(){return dateOfBirth.month;}
    int getDobDay(){return dateOfBirth.day;}
    int getMoney(){return money;}
    bool getAccountExists(){return accountExists;}
    bool getLoggedIn(){return loggedIn;}
    bool getDebug(){return debug;}
    time_t getCurrentTime(){return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());}
    

    void setName(std::string sName){name = sName;}
    void setPassword(std::string sPassword){password = sPassword;}
    void setDobYear(int sDobYear){dateOfBirth.year = sDobYear;}
    void setDobMonth(int sDobMonth){dateOfBirth.month = sDobMonth;}
    void setDobDay(int sDobDay){dateOfBirth.day = sDobDay;}
    void setAccountExists(bool sAccountExists){accountExists = sAccountExists;}
    void setLoggedIn(bool sLoggedIn){loggedIn = sLoggedIn;}
    void setDebug(bool sDebug){debug = sDebug;}


    void deposit(int amount){money += amount;}
    void withdraw(int amount){money -= amount;}

    void addHistory(std::string input){
        std::ofstream history("history.txt", std::ios::app);
        history << input << "\n";
        history.close();
    }

    void deleteHistory(){
        std::ofstream history("history.txt", std::ofstream::trunc);
        history.close();
    }

    void debugOutput(std::string message){
        if(this->debug){
            std::cout << "[DEBUG] " << message << "\n";
        }
    }

    void outputHistory(){
        std::string output;
        std::ifstream history("history.txt");
        while(std::getline(history, output)){
            std::cout << output << "\n";
        }
        history.close();
    }

    bool checkAccountFile(){
        std::ifstream acc("Account.txt");
        if(!acc.is_open() || std::filesystem::is_empty("Account.txt")){
            this->debugOutput("Account file not found / no data!");
            return false;
        }
        acc.close();
        return true;
    }

    void saveAccountToFile(){
        std::ofstream acc("Account.txt");
        acc << "name=" << name << "\n" 
            << "password=" << password << "\n" 
            << "dob_day=" << dateOfBirth.day << "\n" 
            << "dob_month=" << dateOfBirth.month << "\n" 
            << "dob_year=" << dateOfBirth.year << "\n"
            << "balance=" << money << "\n";
        acc.close();
        this->debugOutput("Account data saved to file!");
    }

    void loadAccountFromFile(){
        std::ifstream acc("Account.txt");
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
        }
        this->accountExists = true;
        this->loggedIn = false;
        acc.close();
        this->debugOutput("Account data loaded from file!");
    }

    void saveConfigToFile(){
        std::ofstream config("config.txt");
        config << "version=1\n";
        config << "debug=" << this->debug << "\n";
        config.close();
        this->debugOutput("Config saved to file!");
    }

    void loadConfigFromFile(){
        std::ifstream config("config.txt");
        std::string data;
        int version;
        while(std::getline(config, data)){
            auto pos = data.find('=');
            if(pos == std::string::npos) continue;

            std::string key = data.substr(0, pos);
            std::string value = data.substr(pos + 1);
            if(key == "version") version = std::stoi(value);
            else if(key == "debug") this->debug = (value == "true" ? true : false);
        }
        config.close();
        this->debugOutput("Config loaded from file!");
    }

    bool checkConfigFile(){
        std::ifstream config("config.txt");
        if(!config.is_open() || std::filesystem::is_empty("config.txt")){
            this-> debugOutput("Config file not found / no data!");
            return false;
        }
        else {
            this->debugOutput("Config file found!");
            config.close();
            return true;
        }
    }


    std::string getFullDob(){return std::to_string(this->getDobDay()) + "/" + std::to_string(this->getDobMonth()) + "/" + std::to_string(this->getDobYear());}
};

int main(){
    Account account("John Pork");

    if(account.checkAccountFile()){ //Create account from file if found
        account.loadAccountFromFile();
    }
    if(account.checkConfigFile()){ //Load config data from file if found
        account.loadConfigFromFile();
    }

    
    std::string input;
    while (true){
        std::cout << "\nBloo's banking service\n";
        std::cout << "| 1. Account" << (account.getAccountExists() ? (account.getLoggedIn() ? "\n" : " (login required)\n") : " (creation required)\n");
        std::cout << "| 2. Settings\n";
        std::cout << "| To exit, type 'end'\n";
        std::cout << ">> ";
        std::getline(std::cin, input);
        if(input == "1" && account.getAccountExists() && account.getLoggedIn()){
            while (input != "end" && input != "END"){
                std::cout << "\nHello, " << account.getName() << "!\n";
                std::cout << "| 1. Deposit\n";
                std::cout << "| 2. Withdraw\n";
                std::cout << "| 3. Account details\n";
                std::cout << "| 4. Banking history\n";
                std::cout << "| 5. Delete history\n";
                std::cout << "| To go back, type 'end'\n";
                std::cout << ">> ";
                std::getline(std::cin, input);
                if(input == "1"){
                    std::cout << "\nHow much would you like to deposit? >> ($)\n";
                    std::cout << ">> ";
                    std::string amount;
                    std::getline(std::cin, amount);
                    account.deposit(std::stoi(amount));
                    time_t time = account.getCurrentTime();
                    account.addHistory("Deposited " + amount + "$ on " + std::ctime(&time));
                    std::cout << "\nDeposit successful!\nYour new balance is: " << account.getMoney() << "$\n\n";
                }
                else if(input == "2"){
                    std::cout << "\nHow much would you like to withdraw? >> ($)\n";
                    std::cout << ">> ";
                    std::string amount;
                    std::getline(std::cin, amount);
                    if (std::stoi(amount) > account.getMoney()){
                        std::cout << "\nInsufficient funds!\nYour balance has not changed.\n\n";
                        continue;
                    }
                    account.withdraw(std::stoi(amount));
                    time_t time = account.getCurrentTime();
                    account.addHistory("Withdrew " + amount + "$ on " + std::ctime(&time));
                    std::cout << "\nWithdrawal successful!\nYour new balance is: " << account.getMoney() << "$\n\n";
                }
                else if(input == "3"){
                    std::cout << "\nAccount details:\n\n";
                    std::cout << "Name: " << account.getName() << "\n";
                    std::cout << "Date of Birth: " << account.getFullDob() << "\n";
                    std::cout << "Balance: " << account.getMoney() << "$\n\n";
                }
                else if(input == "4"){
                    std::cout << "\nBanking History:\n\n";
                    account.outputHistory();
                    std::cout << "\n";
                }
                else if(input == "5"){
                    account.deleteHistory();
                    std::cout << "\nHistory deleted\n\n";
                }
            }
        }
        else if(input == "1" && !account.getAccountExists()){
            std::cout << "\nEnter your name: ";
            std::string name;
            std::getline(std::cin, name);
            std::cout << "Enter your password: ";
            std::string password;
            std::getline(std::cin, password);
            std::cout << "Enter your full date of birth (dd/mm/yyyy): ";
            std::string dob;
            std::getline(std::cin, dob);
            std::string day, month, year;
            for(char c : dob){
                if(std::isdigit(c) && day.size() < 2){
                    day += c;
                }
                else if(std::isdigit(c) && month.size() < 2){
                    month += c;
                }
                else if(std::isdigit(c) && year.size() < 4){
                    year += c;
                }
            }
            account = Account(name, password, {std::stoi(year), std::stoi(month), std::stoi(day)}, 0);
            std::cout << "\nAccount created successfully!\nWelcome to Bloo's banking service, " << account.getName() << "!\n";
        }
        else if(input == "1" && account.getAccountExists() && !account.getLoggedIn()){
            std::string name_password = "";
            while(name_password != "end" && name_password != "END"){
                std::cout << "\nEnter your name: ";;
                std::getline(std::cin, name_password);
                if(name_password != account.getName()){
                    std::cout << "\nAccount not found!\n";
                    continue;
                }
                std::cout << "Enter your password: ";
                std::getline(std::cin, name_password);
                if(name_password != account.getPassword()){
                    std::cout << "\nIncorrect password!\n";
                    continue;
                }
                account.setLoggedIn(true);
                std::cout << "\nLogin successful!\nWelcome back, " << account.getName() << "!\n";
                break;
            }
        }
        else if(input == "2"){
            while(input != "end" && input != "END"){
                std::cout << "\nSettings:\n";
                std::cout << "| 1. Change Name\n";
                std::cout << "| 2. Change Password\n";
                std::cout << "| 3. Change Date of Birth\n";
                std::cout << "| 4. Logout\n";
                std::cout << "| 5. Delete Account\n";
                std::cout << "| 6. Debug: currently " << (account.getDebug() ? "enabled" : "disabled") << " (No functionality yet, still deciding on how I want to implement it.)\n";
                std::cout << "| To go back, type 'end'\n";
                std::cout << ">> ";
                std::getline(std::cin, input);
                if(input == "1"){
                    std::cout << "\nEnter your new name: ";
                    std::string newName;
                    std::getline(std::cin, newName);
                    account.setName(newName);
                    std::cout << "\nName changed successfully! Hello, " << account.getName() << "!\n\n";
                }
                else if(input == "2"){
                    std::cout << "\nEnter your new password: ";
                    std::string newPassword;
                    std::getline(std::cin, newPassword);
                    account.setPassword(newPassword);
                    std::cout << "\nPassword changed successfully!\n\n";
                }
                else if(input == "3"){
                    std::cout << "\nEnter your new full date of birth (dd/mm/yyyy): ";
                    std::string dob;
                    std::getline(std::cin, dob);
                    std::string day, month, year;
                    for(char c : dob){
                        if(std::isdigit(c) && day.size() < 2){
                            day += c;
                        }
                        else if(std::isdigit(c) && month.size() < 2){
                            month += c;
                        }
                        else if(std::isdigit(c) && year.size() < 4){
                            year += c;
                        }
                    }
                    account.setDobDay(std::stoi(day));
                    account.setDobMonth(std::stoi(month));
                    account.setDobYear(std::stoi(year));
                    std::cout << "\nDate of Birth changed successfully! Your new Date of Birth is: " << account.getFullDob() << "\n\n";
                }
                else if(input == "4"){
                    account.setLoggedIn(false);
                    std::cout << "\nSuccessfully logged out!\n";
                    break;
                }
                else if(input == "5"){
                    account = Account("John Pork");
                    std::ofstream acc("Account.txt", std::ofstream::trunc);
                    acc.close();
                    std::cout << "\nAccount deleted successfully!\n";
                    break;
                }
                else if(input == "6"){
                    account.setDebug(!account.getDebug());
                    std::cout << "\nDebug has been " << (account.getDebug() ? "enabled\n" : "disabled\n");
                }
            }
        }
        else if(input == "end" || input == "END"){
            account.saveAccountToFile();
            account.saveConfigToFile();
            std::cout << "\nThank you for banking with us!\nGood bye!\n";
            break;
        }
    }
}