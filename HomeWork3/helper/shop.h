#pragma once
#include <vector>
#include <string>


namespace shop{
	
	int inputShoppingCartSize(int maxSize);
	void inputPurchase(std::string& name, int& amount, const std::vector<std::string>& names);
	double costCalculate(double amount, double price);
	double discCostCalculate(double cost, double discount);
	double totalCalculate(const std::vector<double>& costs);
	std::vector<std::string> findMaxCost(const std::vector<std::string>& names, const std::vector<double>& costs);
	void printMaxDiscount(const std::vector<std::string>& names);
	void printOffer(const std::vector<std::string>& names);
	std::vector<std::string> findMinDiscountNames(const std::vector<std::string>& maxCostsNames, const std::vector<std::string>& names, const std::vector<double> discounts);
	std::string inputAnswer(const std::vector<std::string>& names);
	size_t findNamePosition(const std::vector<std::string>& names, const std::string& name);

	void printShoppingCart(const std::vector<std::string>& names, const std::vector<double>& prices);
	void printShoppingCart(const std::vector<std::string> prNames, const std::vector<int>& prNumbers, 
					const std::vector<double>& prSums, const std::vector<double>& discountingAmount, double total, 
					const std::vector<std::string>& names, const std::vector<double>& prices);
	void printFinalResult(double total);

}