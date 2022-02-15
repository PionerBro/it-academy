#include "../helper/shop.h"

#include <vector>
#include <string>

const std::vector<std::string> productNames_{ "bread", "white_bread", "milk", "butter", "sour_cream", "meat", "orange", "apple", "sugar", "pasta" };
const std::vector<double> productPrices_{ 0.9, 1.1, 1.3, 3.6, 1.8, 16.0, 3.0, 2.5, 2.05, 1.29 };
const std::vector<double> productDiscounts_{ 24.0, 24.0, 33.0, 33.0, 33.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
const double maxDiscount = 50;

int main() {
	shop::printShoppingCart(productNames_, productPrices_);
	int cartSize = shop::inputShoppingCartSize(static_cast<int>(productNames_.size()));
	shop::printShoppingCart(productNames_, productPrices_);

	std::vector<std::string> purchaseNames;
	std::vector<int> purchaseAmounts;
	std::vector<double> purchaseCosts, purchaseDiscCosts;

	std::string name;
	int amount = 0;
	double cost = 0, discCost = 0, total = 0;
	size_t pos = 0;
	for (int i = 0; i < cartSize; ++i) {
		shop::inputPurchase(name, amount, productNames_);
		
		pos = shop::findNamePosition(productNames_, name);
		
		cost = shop::costCalculate(amount, productPrices_[pos]);
		discCost = shop::discCostCalculate(cost, productDiscounts_[pos]);

		pos = shop::findNamePosition(purchaseNames, name);
		if (-1 == pos) {
			purchaseNames.push_back(name);
			purchaseAmounts.push_back(amount);
			purchaseCosts.push_back(cost);
			purchaseDiscCosts.push_back(discCost);
		}
		else {
			purchaseAmounts[pos] += amount;
			purchaseCosts[pos] += cost;
			purchaseDiscCosts[pos] += discCost;
			--i;
		}

		total = shop::totalCalculate(purchaseDiscCosts);
		shop::printShoppingCart(purchaseNames, purchaseAmounts, purchaseCosts, purchaseDiscCosts, total, productNames_, productPrices_);
	}
	std::vector<std::string> maxCostNames = shop::findMaxCost(purchaseNames, purchaseCosts);
	std::string answer;
	if (maxCostNames.size() > 1) {
		shop::printMaxCosts(maxCostNames);
		std::vector<std::string> offerNames = shop::findMinDiscountNames(maxCostNames, productNames_, productDiscounts_);
		shop::printOffer(offerNames);
		answer = shop::inputAnswer(maxCostNames);
	}
	else {
		answer = maxCostNames[0];
	}
	pos = shop::findNamePosition(purchaseNames, answer);
	discCost = shop::discCostCalculate(purchaseCosts[pos], maxDiscount);
	purchaseDiscCosts[pos] = discCost;
	total = shop::totalCalculate(purchaseDiscCosts);
	shop::printShoppingCart(purchaseNames, purchaseAmounts, purchaseCosts, purchaseDiscCosts, total, productNames_, productPrices_);
	shop::printFinalResult(total);

	return 0;
}