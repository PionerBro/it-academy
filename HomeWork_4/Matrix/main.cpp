#include <iostream>
#include "src/Matrix.h"


int main() {

	Matrix m;
	Matrix m1(2, 2);
	const Matrix m2(2, 2, { 1.1,2.2,3.2,4.4 });

	try {
		m1.at(0, 0) = m2.at(2, 2);
		std::cout << m1[0][0] << "\n";
	}
	catch (std::out_of_range const& e) {
		std::cout << e.what() << "\n";
	}


	std::cout << m << "\n" << m1 << "\n" << m2 << "\n";
	std::cout << "========================================\n";

	//std::cin >> m >> m1 >> m2;
	//std::cout << m << "\n" << m1 << "\n" << m2 << "\n";

	//std::cout << std::boolalpha << (m1 == m2) << "\n";

	//m += 1.1;
	//m1 += 1.1;
	//m2 += 1.1;
	//std::cout << m << "\n" << m1 << "\n" << m2 << "\n";

	//m -= 1.1;
	//m1 -= 1.1;
	//m2 -= 1.1;
	//std::cout << m << "\n" << m1 << "\n" << m2 << "\n";

	//m *= 1.1;
	//m1 *= 1.1;
	//m2 *= 1.1;
	//std::cout << m << "\n" << m1 << "\n" << m2 << "\n";

	//if (m1.isAdded(m2)) {
	//	std::cout << m1 + m2 << "\n";
	//}

	//if (m1.isMultiplied(m2)) {
	//	std::cout << m1 * m2 << "\n";
	//}

	return 0;
}






























