#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cctype>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <random>
#include <cmath>
#include "account/account.h"

int main(){
    Account account("John Pork");
    
    if(account.checkConfigFile()){ //note to self: load config first, so that debugOutput works lol
        account.loadConfigFromFile();
    }
    if(account.checkAccountFile()){
        account.loadAccountFromFile();
    }
    if(account.getYear() < account.getCurrentYear() && account.getAccountExists()){
        account.calculateInterest(); //This.... could be bad? Unless it gives issues, ill ignore it ig
    }
    account.setYear(account.getCurrentYear()); //is this... like smart?? I gots no clue
    
    std::string input;
    while (true){
        std::cout << "\nBloo's banking service\n"
        << "| 1. Account" << (account.getAccountExists() ? (account.getLoggedIn() ? "\n" : " (login required)\n") : " (creation required)\n")
        << "| 2. Settings\n"
        << "| To exit, type 'end'\n";
        std::cout << ">> ";
        std::getline(std::cin, input);
        if(input == "1" && account.getAccountExists() && account.getLoggedIn()){
            while (input != "end" && input != "END"){
                std::cout << "\nHello, " << account.getName() << "!\n"
                << "| 1. Deposit\n"
                << "| 2. Withdraw\n"
                << "| 3. Account details\n"
                << "| 4. Banking history\n"
                << "| 5. Delete history\n"
                << "| To go back, type 'end'\n";
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
                    std::cout << "\nAccount details:\n\n"
                    << "Name: " << account.getName() << "\n"
                    << "Date of Birth: " << account.getFullDob() << "\n"
                    << "Balance: " << account.getMoney() << "$\n"
                    << "Interest Rate: " << account.getInterest() << "%\n\n";
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
            /*account.setName(name);
            account.setPassword(password);
            account.setDobDay(std::stoi(day));
            account.setDobMonth(std::stoi(month));
            account.setDobYear(std::stoi(year));
            account.setAccountExists(true);
            account.setLoggedIn(true); */
            Account account(name, password, {std::stoi(year), std::stoi(month), std::stoi(day)}, 0);
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
                std::cout << "\nSettings:\n"
                << "| 1. Change Name\n"
                << "| 2. Change Password\n"
                << "| 3. Change Date of Birth\n"
                << "| 4. Logout\n"
                << "| 5. Delete Account\n"
                << "| 6. Debug: currently " << (account.getDebug() ? "enabled\n" : "disabled\n")
                << (account.getDebug() ? "| 7. Simulate Interest\n" : "")
                << (account.getDebug() ? "| 8. Generate New Interest Rate\n" : "")
                << (account.getDebug() ? "| 9. Delete Log\n" : "")
                << "| To go back, type 'end'\n";
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
                    account.setName("John Pork");
                    account.setAccountExists(false);
                    account.setLoggedIn(false); 
                    std::ofstream acc(account.getAccountPath(), std::ofstream::trunc);
                    acc.close();
                    std::cout << "\nAccount deleted successfully!\n";
                    break;
                }
                else if(input == "6"){
                    account.setDebug(!account.getDebug());
                    std::cout << "\nDebug has been " << (account.getDebug() ? "enabled\n" : "disabled\n");
                }
                else if(input == "7" && account.getDebug()){
                    account.calculateInterest();
                }
                else if(input == "8" && account.getDebug()){
                    account.generateInterestRate();
                }
                else if(input == "9" && account.getDebug()){
                    std::ofstream logfile(account.getLogPath(), std::ofstream::trunc); //horrible, fix later
                    logfile.close();
                }
            }
        }
        else if(input == "end" || input == "END"){
            if(account.getAccountExists()) account.saveAccountToFile();
            account.saveConfigToFile();
            std::cout << "\nThank you for banking with us!\nGood bye!\n";
            break;
        }
    }
}