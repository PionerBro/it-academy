#include "shop.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

namespace shop {

	bool inputInteger(int& number) {
		std::cin >> number;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
		if (std::cin.get() != '\n') {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
		return true;
	}

	int inputShoppingCartSize(int maxSize) {
		int number = 0;
		while (true)
		{
			std::cout << "Enter number of product names, less than or equals " << maxSize << ": ";
			if (!inputInteger(number)) {
				std::cout << "Incorrect input. Number must be an positive integer!\n";
				continue;
			}
			if (number <= 0 || number > maxSize) {
				std::cout << "Wrong input. Number must be less than or equals " << maxSize << ", but greater than zero!\n";
				continue;
			}
			break;
		}
		return number;
	}

	void printTitle() {
		std::cout << "Shopping cart:\t\t\t\t\t\t| List of goods:\n"
			"Name:\t\tNumber: Price: Cost: Discount Cost: \t| Name\r\t\t\t\t\t\t\t\t\tPrice\n"
			"--------------------------------------------------------|---------------------\n";
	}

	void printProduct(int pos, const std::vector<std::string>& names, const std::vector<double>& prices) {
		if (pos < names.size())
			std::cout << "\r\t\t\t\t\t\t\t| " << names[pos] << "\r\t\t\t\t\t\t\t\t\t" << prices[pos];
		std::cout << "\n";
	}

	void printShoppingCart(const std::vector<std::string>& names, const std::vector<double>& prices) {
		system("cls");
		std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
		printTitle();
		for (int pos = 0; pos < names.size(); ++pos)
			printProduct(pos, names, prices);
		std::cout << "\n" << "\n";
	}

	void printTotal(double total, int it) {
		std::cout << "Total: \r\t\t\t\t\t" << total;
	}

	size_t findNamePosition(const std::vector<std::string>& names, const std::string& name) {
		auto it = std::find(names.begin(), names.end(), name);
		return (it != names.end()) ? it - names.begin() : -1;
	}

	void printShoppingCart(const std::vector<std::string> prNames, const std::vector<int>& prNumbers, const std::vector<double>& prSums, const std::vector<double>& discountingAmount, double total, const std::vector<std::string>& names, const std::vector<double>& prices) {
		system("cls");
		printTitle();
		int it = 0;
		for (; it < prNumbers.size(); ++it) {
			size_t pos = findNamePosition(names, prNames[it]);
			std::cout << it + 1 << ". " << prNames[it] << "\r\t\t" << prNumbers[it] << "\t" << prices[pos] << '\t';
			std::cout << prSums[it] << "\t" << discountingAmount[it];
			printProduct(it, names, prices);
		}
		printTotal(total, it);
		printProduct(it, names, prices);
		++it;
		for (it; it < names.size(); ++it)
			printProduct(it, names, prices);
		std::cout << "\n" << "\n";
	}

	bool inputName(std::string& name, const std::vector<std::string>& names) {
		std::cin >> name;
		if (-1 == findNamePosition(names, name)) {
			std::cout << "Name is not defined!\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
		return true;
	}

	bool inputAmount(int& amount) {
		if (!inputInteger(amount)) {
			std::cout << "Incorrect input. Amount must be a positive integer!\n";
			return false;
		}
		if (amount <= 0) {
			std::cout << "Wrong input. Amount must be greater than zero!\n";
			return false;
		}
		return true;
	}

	void inputPurchase(std::string& name, int& amount, const std::vector<std::string>& names) {
		while (true) {
			std::cout << "Enter product name and amount: ";
			if (!inputName(name, names))
				continue;
			if (!inputAmount(amount))
				continue;
			break;
		}
	}

	double costCalculate(double amount, double price) {
		return amount * price;
	}

	double discCostCalculate(double cost, double discount) {
		return cost - cost * discount / 100;
	}

	double totalCalculate(const std::vector<double>& costs) {
		double total = 0;
		for (auto cost : costs)
			total += cost;
		return total;
	}

	std::vector<std::string> findMaxCost(const std::vector<std::string>& names, const std::vector<double>& costs) {
		double max = *(std::max_element(costs.begin(), costs.end()));
		std::vector<std::string> maxCosts;
		for (int i = 0; i < costs.size(); ++i) {
			if (costs[i] == max) {
				maxCosts.push_back(names[i]);
			}
		}
		return maxCosts;
	}

	void printMaxDiscount(const std::vector<std::string>& names) {
		std::cout << "Max costs purchases: ";
		size_t lastElement = names.size() - 1;
		for (size_t i = 0; i < lastElement; ++i) {
			std::cout << names[i] + ", ";
		}
		std::cout << names[lastElement] + ".\n";
	}

	void printOffer(const std::vector<std::string>& names)
	{
		std::cout << "You may choose one of this, but we recommend: ";
		size_t lastElement = names.size() - 1;
		for (size_t i = 0; i < lastElement; ++i) {
			std::cout << names[i] + ", ";
		}
		std::cout << names[lastElement] + ".\n";
	}

	std::vector<std::string> findMinDiscountNames(const std::vector<std::string>& maxCostsNames, const std::vector<std::string>& names, const std::vector<double> discounts) {
		size_t pos = findNamePosition(names, maxCostsNames[0]);
		double minDisc = discounts[pos];
		for (int i = 1; i < maxCostsNames.size(); ++i) {
			pos = findNamePosition(names, maxCostsNames[i]);
			if (discounts[pos] < minDisc)
				minDisc = discounts[pos];
		}

		std::vector<std::string> minDiscountCostsNames;
		for (int i = 0; i < maxCostsNames.size(); ++i) {
			pos = findNamePosition(names, maxCostsNames[i]);
			if (discounts[pos] == minDisc)
				minDiscountCostsNames.push_back(maxCostsNames[i]);
		}
		return minDiscountCostsNames;
	}

	std::string inputAnswer(const std::vector<std::string>& names) {
		std::string name;
		while (!inputName(name, names)) {
			std::cout << "Enter a name: ";
		}
		return name;
	}

	void printFinalResult(double total) {
		std::cout << "Total cost of payment: " << total << "\n";
	}
}