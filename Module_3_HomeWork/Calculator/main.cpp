#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

#include "../helper/calc.h"

void printWelcomeText() {
	std::cout << "================ Calculator v1.0 ================\n"
		"Supports operations such as: '+', '-', '*', '/', '^', '%', '(', ')', '|',\n"
		"		N-th root - 'r'\n"
		"		Factorial - 'f'\n"
		"	Decimal logarithm - 'l'\n"
		"	Natural logarithm - 'n'\n"
		"Enter 'clear' to reset the result\n"
		"Enter 'quit' to exit the program\n"
		"================================================\n";
}

int main() {
	
	printWelcomeText();
	double result = 0;
	std::string str;
	bool resetFlag = true, errorFlag = true;
	while(true) {
		std::cout << "Enter expression: ";
		std::cin >> str;
		if (str == "quit")
			break;
		else if (str == "clear") {
			system("cls");
			printWelcomeText();
			result = 0;
			resetFlag = true;
			continue;
		}

		if (!resetFlag && !errorFlag)
			str = std::to_string(result) + str;
		else {
			resetFlag = false;
			errorFlag = false;
		}
		
		int errCode = 0;
		result = calculate(str, &errCode);
		
		if (!errCode)
			std::cout << "Result: " << str << " = " << result << "\n";
		else {
			std::cout << printCalcErrorText(errCode) << '\n';
			errorFlag = true;
			result = 0;
		} 
	}
	return 0;
}