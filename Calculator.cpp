#include <iostream>
#include <string>
#include <unordered_set>
#include <cctype>
#include <vector>
#include <climits>



/*
During update log:
-Completely reworked the calculation pipeline
-Removed the 5+ different for-loops and replaced it with 1 central loop
-Reworked evaluateInput and all calculation functions to accomodate this new pipeline design
-Removed the complexCalculations bool setting in the menu as this new design only calculates it if it is present
*/





/*
Keywords: '^' is for power of calculation| 's' is for square root calcualtion

sample input:
213*5+23 (Also works with spaces)
sample output:
Result: 1088
*/

/*28/01/25|V1
-Initial version. Allows for multiple operation inputs and simple operands (+, -, /, *)

30/01/25|V1.1
-Added support for power of calculation (like squaring or cubing and higher)
-Updated Menu to make it look better
-Added toggleable to calculate more complex stuff (eg. power of and square root)
-Will soon add square root

03/02/25|V1.2
-Added support for square root calculation (example: s144 | result: 12) with 's' being the keyword for it
-Cleaned up some code to make it somewhat more optimised. There are way too many for-loops so it probably won't matter
-Cleaned up the validateInput function in the for-loop section to stop it from making weird and stupid checks
*/

class Calculator{
    private:
    int currentIndex;
    bool complexCalculation = true;
    std::vector<std::string> token;
    std::unordered_set<char> operators = {'+', '-', '/', '*', '^', 's'};
    public:
        Calculator(){}
        ~Calculator(){}


        //Generic methods
        bool getComplexCalc(){return complexCalculation;}
        void setComplexCalc(){if(complexCalculation){complexCalculation = false;} else complexCalculation = true;}
        std::vector<std::string> cleanup(std::vector<std::string>& token, int& index, double result){
            token[index] = std::to_string(result);
            token.erase(token.begin() + index + 1, token.begin() + index + 2);
            --index;
            return token;
        }

        void clearCin(){std::cin.clear(); std::cin.ignore(INT_MAX, '\n');}

        //In-order executed methods
        void Menu(){
            std::cout << "Calculator\n"
                      << "|1.Complex calculations| current: " << ((complexCalculation) ? "true\n" : "false\n")
                      << "|To exit type 'end'\n"
                      << ">>";
        }

        bool validateInput(const std::string& input){
            if(input.empty()) return false;
            else if(operators.find(input.front()) != operators.end() && input[0] != 's' || operators.find(input.back()) != operators.end()) return false;
            else{
                for(std::size_t i=0;i<input.size()-1;i++){
                    if(input[i] == 's' && input[i+1] < 0){std::cout << "Finding the square root of a negative number is impossible.\n"; return false;}
                    else if((input[i] == '^' && !complexCalculation || input[i] == 's') && !complexCalculation){std::cout << "Calculation of power is done only if 'Complex calculations' = true\n"; return false;} 
                }
            }
            return true;
        }
        
        double evaluateInput(const std::string& input){
            if(this->validateInput(input)){
                std::vector<std::string> token = this->tokenize(input);
                return loopProblem(token);
            }
            std::cout << "Encountered error whilst validating input. Try again." << std::endl;
            this->clearCin();
            return -1;
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
            
            //last check to make certain we've actually got everything in there (think like packing and organising a suitcase, you always gotta double check)
            if(!currentNum.empty()) token.push_back(currentNum);
            return token; //and now we return it
        }


        double loopProblem(std::vector<std::string>& token){
            for(int i=0;i<token.size()+1;++i){
                if(!isdigit(i)){
                    switch(i){
                        case "^":
                        token = this->calculatePower(token, i);
                        break;

                        case "*":
                        token = this->multiply(token, i);
                        break;

                        case "/":
                        token = this->divide(token, i);
                        break;

                        case "s":
                        token = this->squareRoot(token, i);
                        break;
                    }
                }
            }
            return this->addAndSubtract(token);
        }

        std::vector<std::string> calculatePower(std::vector<std::string>& token, int& index){  
            int result = 1;
            int base = std::stoi(token[index-1]);
            int exponent = std::stoi(token[index+1]);
            while(exponent > 0){
                --exponent;
                result *= base;
            }
            return this->cleanup(token, index, result);
        }

        std::vector<std::string> squareRoot(std::vector<std::string>& token, int& index){
            double tolerance = 1e-6;
            double squareNumber = std::stod(token[index+1]);
            double result = squareNumber;

            while(std::abs(result * result - squareNumber) > tolerance){
                result = 0.5 * (result + squareNumber / result);
            }
            return this->cleanup(token, index, result);
        }

        std::vector<std::string> divide(std::vector<std::string>& token, int& index){
            int result = std::stoi(token[index - 1]) / std::stoi(token[index + 1]);
            return this->cleanup(token, index, result);
        }
            

        std::vector<std::string> multiply(std::vector<std::string>& token, int& index){
            int result = std::stoi(token[index-1]) * std::stoi(token[index+1]);
            return this->cleanup(token, index, result);
        }

        double addAndSubtract(std::vector<std::string>& token){
            int result = std::stod(token[0]);
            for(std::size_t i=1;i<token.size();i += 2){
                char op = token[i][0];
                double num = std::stod(token[i+1]);

                if(op == '+') result += num;
                else if(op == '-') result -= num;
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
        if(input == "1"){calc.setComplexCalc(); std::cout << "Complex calculation set to " << ((calc.getComplexCalc()) ? "true\n" : "false\n"); continue;}
        else if(input == "end" || input == "End" || input == "END"){std::cout << "Stopping...\n"; break;}
        std::cout << "Result: " << calc.evaluateInput(input) << "\n";
    }
    return -1;
}