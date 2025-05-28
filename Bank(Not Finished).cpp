#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cctype>

class Account{
private:
    std::string name;
    std::string password;
    typedef struct{
    int year; //dob = Date of Birth
    int month;
    int day;
    } date;
    int money = 0;
public:
    Account(std::string name, std::string password, date dateOfBirth) : name(name), password(password), date(dateOfBirth){}
    ~Account(){} 

    std::string getName(){return name;}
    std::string getPassword(){return password;}
    int getDobYear(){return date.year;}
    int getDobMonth(){return date.month;}
    int getDobDay(){return date.day;}
    int getMoney(){return money;}

    void setName(std::string sName){name = sName;}
    void setPassword(std::string sPassword){password = sPassword;}
    int setDobYear(int sDobYear){date.year = sDobYear;}
    int setDobMonth(int sDobMonth){dobMonth = sDobMonth;}
    int setDobDay(int sDobDay){dobDay = sDobDay;}

    std::string getFullDob(){return std::to_string(this->getDobDay()) + "/" + std::to_string(this->getDobMonth()) + "/" + std::to_string(this->getDobYear());}
};

int main(){
    Account account("Himothy", "CoolSigma69696969696969", 2025, 2, 7)
}