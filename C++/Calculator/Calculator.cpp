#include <iostream>
#include <string>
#include <unordered_set>
#include <cmath>
#include <cctype>
#include <vector>
#include <climits>

class Calculator{
    private:
    int currentIndex;
    bool debug = false;
    //bool complexCalculation = true;
    std::vector<std::string> token;
    std::unordered_set<char> operators = {'+', '-', '/', '*', '^', 's'};
    public:
        Calculator(){}
        ~Calculator(){}


        //Generic methods
        /*bool getComplexCalc(){return complexCalculation;}
        void setComplexCalc(){if(complexCalculation)complexCalculation = false; else complexCalculation = true;}*/
        bool getDebug(){return debug;}
        void setDebug(){if(debug)debug = false; else debug = true;}

        void debugOutput(std::string msg, int index, double result){
            if(debug && index != -1) std::cout << msg << index << "\n";
            else if (debug && result != -1)std::cout << msg << result << "\n";
            else if (debug) std::cout << msg << "\n";
        }

        void debugVectorOutput(std::vector<std::string>& token, bool preCleanup){
            if(debug && preCleanup){
                std::cout << "Pre Cleanup: ";
                for(std::string c : token) std::cout << c << ", ";
                std::cout << "\n";
            }
            else if (debug && !preCleanup){
                std::cout << "Post Cleanup: ";
                for(std::string c : token) std::cout << c << ", ";
                std::cout << "\n";
            }
        }

        std::vector<std::string> cleanup(std::vector<std::string>& token, int& index, double& result, bool isSquareRoot){
            token[index-(isSquareRoot ? 0 : 1)] = std::to_string(result);
            this->debugVectorOutput(token, true);
            token.erase(token.begin() + index + (isSquareRoot ? 1 : 0), token.begin() + index + 2);
            --index;
            this->debugVectorOutput(token, false);
            return token;
        }

        void clearCin(){std::cin.clear(); std::cin.ignore(INT_MAX, '\n');}

        //In-order executed methods
        void Menu(){
            std::cout << "Calculator\n"
                      //<< "|1.Complex calculations| current: " << ((complexCalculation) ? "true\n" : "false\n")
                      << "|1. Help\n"
                      << "|2. Debug >> currently " << (debug ? "Enabled\n" : "Disabled\n")
                      << "|To exit type 'end'\n"
                      << ">>";
        }

        bool validateInput(const std::string& input){
            if(input.empty()) return false;
            else if(operators.find(input.front()) != operators.end() && input[0] != 's' || operators.find(input.back()) != operators.end()) return false;
            else{
                for(int i=0;i<input.size()-1;i++){
                    if(input[i] == 's' && std::stoi(input.substr(i+1)) < 1){std::cout << "Finding the square root of a negative number is impossible.\n"; return false;}
                    //else if(input[i] == '^' && !complexCalculation || input[i] == 's' && !complexCalculation)){std::cout << "Calculation of power is done only if 'Complex calculations' = true\n"; return false;} 
                }
            }
            return true;
        }
        
        double evaluateInput(const std::string& input){
            if(this->validateInput(input)){
                std::vector<std::string> token = this->tokenize(input);
                return loopProblem(token);
            }
            std::cout << "Encountered error whilst validating input. Try again.\n";
            this->clearCin();
            return false;
        }

        //tokenize the input all into one vector
        std::vector<std::string> tokenize(const std::string& input){
            std::vector<std::string> token;
            std::string currentNum = "";
            
            for(char c : input){
                if(isdigit(c) || c == '.') currentNum += c;

                //Check if its an operator, then add the currentNum to our vector if its not empty and then we add the operator by passing it as a temp class
                else if(operators.find(c) != operators.end()){
                    if(!currentNum.empty()){
                        token.push_back(currentNum); 
                        currentNum = "";
                    }
                    token.push_back(std::string(1, c));                
                }
            }
            
            //Double check
            if(!currentNum.empty()) token.push_back(currentNum);
            return token;
        }


        double loopProblem(std::vector<std::string>& token){
            for(int i=0;i<token.size()+1;i++){
                    if(token[i] == "^") token = this->calculatePower(token, i); //Orginally wanted to do a switch statement, but jeez did it start screaming at me
                    else if(token[i] == "*") token = this->multiply(token, i);
                    else if(token[i] == "/") token = this->divide(token, i);
                    else if(token[i] == "s") token = this->squareRoot(token, i);
            }
            return this->addAndSubtract(token);
        }

        std::vector<std::string> calculatePower(std::vector<std::string>& token, int& index){  
            this->debugOutput("Power of Calculation", -1, -1);
            double result = 1;
            double base = std::stod(token[index-1]);
            double exponent = std::stod(token[index+1]);
            while(exponent > 0){
                --exponent;
                result *= base;
            }
            this->debugOutput("Power inbetween result: ", -1, result);
            return this->cleanup(token, index, result, false);
        }

        std::vector<std::string> squareRoot(std::vector<std::string>& token, int& index){
            this->debugOutput("Square Root Calculation", -1, -1);
            double tolerance = 1e-6;
            double squareNumber = std::stod(token[index+1]);
            double result = squareNumber;

            while(std::abs(result * result - squareNumber) > tolerance){
                result = 0.5 * (result + squareNumber / result);
            }
            this->debugOutput("Inbetween result: ", -1, result);
            this->debugOutput("Index: ", index, -1);
            return this->cleanup(token, index, result, true);
        }

        std::vector<std::string> divide(std::vector<std::string>& token, int& index){
            this->debugOutput("Division", -1, -1);
            double result = std::stod(token[index - 1]) / std::stod(token[index + 1]);
            this->debugOutput("Inbetween result: ", -1, result);
            this->debugOutput("Index: ", index, -1);
            return this->cleanup(token, index, result, false);
        }
            

        std::vector<std::string> multiply(std::vector<std::string>& token, int& index){
            this->debugOutput("Multiplication", -1, -1);
            double result = std::stod(token[index-1]) * std::stod(token[index+1]);
            this->debugOutput("Inbetween result: ", -1, result);
            this->debugOutput("Index: ", index, -1);
            return this->cleanup(token, index, result, false);
        }

        double addAndSubtract(std::vector<std::string>& token){
            this->debugOutput("Addition and Subtraction", -1, -1);
            double result = std::stod(token[0]);
            if(token.size() > 1){
                result = std::stod(token[0]);
                for(std::size_t i=1;i<token.size();i += 2){
                    char op = token[i][0];
                    double num = std::stod(token[i+1]);

                    if(op == '+') result += num;
                    else if(op == '-') result -= num;
                }
            }
            return result;
        }
};

int main(){
    Calculator calc;
    std::string input;
    while(true){
        calc.Menu();
        std::getline(std::cin, input);
        //if(input == "1"){calc.setComplexCalc(); std::cout << "Complex calculation set to " << ((calc.getComplexCalc()) ? "true\n" : "false\n"); continue;}
        if(input == "1"){
            std::cout << "Help:\n"
                      << "This calculator supports the following operations: +, -, *, /, ^ (power of), s (square root)\n"
                      << "To calculate the power of a number, use the '^' operator. For example, to calculate 2 raised to the power of 3, you would input '2^3', which will give you the result of 8.\n"
                      << "To calculate the square root of a number, use the 's' operator followed by the number. For example, to calculate the square root of 16, you would input 's16', which will give you the result of 4.\n"
                      << "You can also combine these operations in a single input. For example, '2^3 + s16' will first calculate 2 raised to the power of 3 (which is 8) and then add it to the square root of 16 (which is 4), resulting in a final output of 12.\n";
            continue;
        }
        else if(input == "2"){calc.setDebug(); std::cout << "Debug has been " << (calc.getDebug() ? "Enabled\n" : "Disabled\n"); continue;}
        if(input == "end" || input == "End" || input == "END"){std::cout << "Stopping...\n"; break;}
        std::cout << "Result: " << (calc.getDebug() ? "\n" : "") << calc.evaluateInput(input) << "\n";
    }
    return -1;
}