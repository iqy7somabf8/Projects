#include "Calculator.h"

#include <iostream>
#include <string>

int main() {
    Calculator calc;
    std::string input;
    while (true) 
    {
        calc.Menu();
        std::getline(std::cin, input);

        if (input == "h" || input == "H")
        {
            std::cout << "Help:\n"
                      << "This calculator supports the following operations: +, -, *, /, ^ (power of), s (square root)\n"
                      << "To calculate the power of a number, use the '^' operator. For example, to calculate 2 raised to the power of 3, you would input '2^3', which will give you the result of 8.\n"
                      << "To calculate the square root of a number, use the 's' operator followed by the number. For example, to calculate the square root of 16, you would input 's16', which will give you the result of 4.\n"
                      << "You can also combine these operations in a single input. For example, '2^3 + s16' will first calculate 2 raised to the power of 3 (which is 8) and then add it to the square root of 16 (which is 4), resulting in a final output of 12.\n";
            continue;
        }

        if (input == "d" || input == "D") { calc.setDebug(); std::cout << "Debug has been " << (calc.getDebug() ? "Enabled\n" : "Disabled\n"); continue; }

        if (input == "end" || input == "End" || input == "END") { std::cout << "Stopping...\n"; break; }

        std::cout << "Result: " << (calc.getDebug() ? "\n" : "") << calc.evaluateInput(input) << "\n";
    }
    return 0;
}