#pragma once
#include <vector>
#include <string>


namespace shop{
	
	//input positive integer in the range(>0 and <maxSize)
	int inputShoppingCartSize(int maxSize);
	//input name from vector 'names' and number of product
	void inputPurchase(std::string& name, int& amount, const std::vector<std::string>& names);
	double costCalculate(double amount, double price);
	double discCostCalculate(double cost, double discount);
	double totalCalculate(const std::vector<double>& costs);
	//search name of elements with max value in vector costs
	std::vector<std::string> findMaxCost(const std::vector<std::string>& names, const std::vector<double>& costs);
	//print names of max cost products
	void printMaxCosts(const std::vector<std::string>& names);
	//print offer to choose one of max cost products
	void printOffer(const std::vector<std::string>& names);
	//search products name with min discount in vector maxCostsNames 
	std::vector<std::string> findMinDiscountNames(const std::vector<std::string>& maxCostsNames, const std::vector<std::string>& names, const std::vector<double> discounts);
	//input one of 'names' elements 
	std::string inputAnswer(const std::vector<std::string>& names);
	//search position of name in vector 'names'
	size_t findNamePosition(const std::vector<std::string>& names, const std::string& name);


	void printShoppingCart(const std::vector<std::string>& names, const std::vector<double>& prices);
	void printShoppingCart(const std::vector<std::string> prNames, const std::vector<int>& prNumbers, 
					const std::vector<double>& prSums, const std::vector<double>& discountingAmount, double total, 
					const std::vector<std::string>& names, const std::vector<double>& prices);
	void printFinalResult(double total);

}