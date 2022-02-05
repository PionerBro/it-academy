#include "calc.h"
#include <iostream>
#include <list>
#include <iterator>

#include "math.h"

class OpData {
public:
	double firstOperand = 0;
	double secondOperand = 0;
	char op = '\0';

	OpData() {}
};

class OpPriority {
public:
	int priority;
	std::list<OpData*>::iterator it;

	OpPriority(int prior, std::list<OpData*>::iterator iter) : priority(prior), it(iter) {}
};

int priority(unsigned char c) {
	switch (c)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
	case '%':
		return 2;
	case '^':
	case 'r':
		return 3;
	case 'l':
	case 'f':
	case 'n':
		return 4;
	case '(':
	case ')':
	case '|':
		return 5;
	case '.':
		return 0;
	default:
		return isdigit(c) ? 0 : -1;
	}
}

double getResult(const OpData* tmp, int& errCode) {
	if (tmp->op == '+')
		return addition(tmp->firstOperand, tmp->secondOperand);
	if (tmp->op == '/') {
		if (!tmp->secondOperand) {
			errCode = 2;
			return 0;
		}
		return division(tmp->firstOperand, tmp->secondOperand);
	}
	if (tmp->op == '*')
		return multiplication(tmp->firstOperand, tmp->secondOperand);
	if (tmp->op == '-')
		return subtraction(tmp->firstOperand, tmp->secondOperand);
	if (tmp->op == '%')
	{
		if (!tmp->secondOperand) {
			errCode = 2;
			return 0;
		}
		return mod(tmp->firstOperand, tmp->secondOperand);
	}
	if (tmp->op == '^')
		return pow(tmp->firstOperand, tmp->secondOperand);
	if (tmp->op == 'r') {
		if (!tmp->secondOperand) {
			errCode = 3;
			return 0;
		}
		if (tmp->firstOperand < 0 && !(static_cast<int>(tmp->secondOperand) % 2)) {
			errCode = 4;
		}
		return root(tmp->firstOperand, tmp->secondOperand);
	}
	if (tmp->op == 'l') {
		if (tmp->firstOperand <= 0) {
			errCode = 5;
			return 0;
		}
		return log10(tmp->firstOperand);
	}
	if (tmp->op == 'n') {
		if (tmp->firstOperand <= 0) {
			errCode = 5;
			return 0;
		}
		return log(tmp->firstOperand);
	}
	if (tmp->op == 'f') {
		if (tmp->firstOperand < 0 || (tmp->firstOperand - static_cast<int>(tmp->firstOperand)) != 0) {
			errCode = 6;
			return 0;
		}
		return factorial(static_cast<int>(tmp->firstOperand));
	}
	if (tmp->op == '|') {
		return std::abs(tmp->firstOperand);
	}
	return -1;
}

double getNumber(const std::string& str, size_t first, size_t count) {
	return count ? std::stod(str.substr(first, count)) : 0;
}

void add_to_priorList(std::list<OpPriority*>& list, OpPriority* tmp) {
	/*
		���� ������, ���� ������ ��������� �������, �����
		��������� � ������� �������� ����������,
		���� ��������� ���������� ��������� ��������� � ����� �����������
	*/
	if (!list.size())
		list.push_back(tmp);
	else {
		bool flag = false;
		std::list<OpPriority*>::iterator it = list.begin();
		for (; it != list.end(); ++it) {
			if ((*it)->priority < tmp->priority) {
				list.emplace(it, tmp);
				flag = true;
				break;
			}
		}
		if (!flag)
			list.push_back(tmp);
	}
}

int checkExprString(const std::string& str) {
	int bktCount = 0, modCount = 0;
	bool dotFlag = false, modFlag = false;
	size_t itOnLastElement = str.size() - 1;
	std::list<int> bktCountOnModTrue;
	for (size_t i = 0; i <= itOnLastElement; ++i) {
		int curElPriority = priority(str[i]);

		/*
		* ���� ��� ������������� ������, ���������� ������
		*/
		if (curElPriority == -1)
			return -1;

		if (curElPriority)
			dotFlag = false;

		if (str[i] == '|') {
			int nextElPriority = -1;
			if (i == 0 || (((nextElPriority = priority(str[i - 1])) != 0) && nextElPriority != 4 && nextElPriority != 5) || (str[i - 1] == '(' || (modFlag && str[i - 1] == '|'))) {
				if (i != itOnLastElement && (priority(str[i + 1]) == 0 || priority(str[i + 1]) == 1 || str[i + 1] == '(' || str[i + 1] == '|')) {
					modFlag = true;
					bktCountOnModTrue.push_front(bktCount);
					++modCount;
					continue;
				}
				return -1;
			}
			if (i == itOnLastElement || (priority(str[i + 1]) >= 1 && priority(str[i + 1]) <= 4) || str[i + 1] == ')' || str[i + 1] == '|') {
				if (--modCount < 0)
					return -1;
				if (bktCountOnModTrue.front() != bktCount) {
					bktCountOnModTrue.clear();
					return -1;
				}
				bktCountOnModTrue.pop_front();
				modFlag = false;
				continue;
			}
			return -1;
		}

		modFlag = false;

		/*
			���� � ����� ������ ����� �����, ����� ������ ��� ����� ���������,
			����� � ������ ������ �� ���������� ������, ���������� ������
		*/
		if (str[i] == '.') {
			if (dotFlag || i == 0 || i == itOnLastElement || !isdigit(str[i - 1]) || !isdigit(str[i + 1]))
				return -1;
			dotFlag = true;
			continue;
		}

		/*
			��������� '+' � '-': ���� �������� ��������� ������� ������ ���
			��������� ������ �������� ����������, ���������� ������
		*/
		if (curElPriority == 1) {
			if (i == itOnLastElement)
				return -1;
			int nextElPriority = priority(str[i + 1]);
			if (nextElPriority >= 1 && nextElPriority <= 4)
				return -1;
			continue;
		}

		/*
			��������� '*','/','%','r','^': ���� �������� ������ ��� ��������� ������� ������ ���
			��������� ������ �������� ����������, ���������� ������
		*/
		if (curElPriority >= 2 && curElPriority <= 3) {
			if (i == 0 || i == itOnLastElement)
				return -1;
			int nextElPriority = priority(str[i + 1]);
			if (nextElPriority >= 1 && nextElPriority <= 4)
				return -1;
			continue;
		}

		/*
			��������� 'f', 'l', 'n': ���� �������� ������ ������� ������ ���
			��������� ������ �������� ������ ��� ����������, ��� �������� ����� ������, ���������� ������
		*/
		if (curElPriority == 4) {
			if (i == 0)
				return -1;
			if (i != itOnLastElement) {
				int nextElPrior = priority(str[i + 1]);
				if (nextElPrior == 0 || nextElPrior == 3 || nextElPrior == 4)
					return -1;
			}
			continue;
		}

		/*
			���� ����� �� ����������� ������ �����, ������ ��������� �������,
			��������� ������� ����������� ������ ��� ��������, ����� '+' � '-',
			���������� ������
		*/
		if (str[i] == '(') {
			if ((i != 0 && (priority(str[i - 1]) == 0 || priority(str[i - 1]) == 4)) || i == itOnLastElement)
				return -1;
			int nextElPrior = priority(str[i + 1]);
			if (str[i + 1] == ')' || (nextElPrior >= 2 && nextElPrior <= 4))
				return -1;

			++bktCount;
			continue;
		}

		/*
			���� ������ �� ����������� ������ �����, ������ ������ �������,
			���������� ������� ����������� ������ ��� ��������, ����� �������,
			���������� ������
			����� ���� ������� ������ ������ ����, ���������� ������
		*/
		if (str[i] == ')') {
			if ((i != itOnLastElement && priority(str[i + 1]) == 0) || i == 0)
				return -1;
			int prevElPrior = priority(str[i - 1]);
			if (str[i - 1] == '(' || (prevElPrior >= 1 && prevElPrior <= 3))
				return -1;
			if (--bktCount < 0)
				return -1;
			continue;
		}
	}
	/*
	* ���� ������� �� ����� ����, ���������� ������
	*/
	if (bktCount || modCount)
		return -1;
	return 0;
}

double calculate(const std::string& str, int* errorCode) {

	//��������� ������ �� ������������ �����	
	if (checkExprString(str)) {
		if (errorCode)
			*errorCode = 1;
		return 0;
	}


	std::list<OpData*> list;			//������ ������ �������� � ����� �� ������� ��� � ���������	
	std::list<OpPriority*> priorList;	//������ ������ ��������� ��������� ������ list � ������� ���������� �������� 
	size_t posT = 0;					//������� � ������� ���������� �����	
	OpData* tmp = nullptr;
	int incPriority = 0;				//���������� ��� ���������� ���������� �������� ����������� � �������
	bool modFlag = false;				//���� ���� ������ �����������, �������� true
	for (size_t i = 0; i < str.size(); ++i) {
		
		/*
		* ���������� ����� ������ ������: ����������� ��� �����������
		* ���� ����������� �� ������� ������ � ��������� ������,
		* ��������� ����� ������ ���� ��� � ��������� �������� ������ ����� ������, �� ���� ��� � �������� ��� ������,
		* ������� �� ����������� ����� ���� �������� ����������� � ������
		*/
		if (str[i] == '|') {
			if (i == 0 || (priority(str[i - 1]) != 0 && priority(str[i - 1]) != 4 && priority(str[i - 1]) != 5)) {
				modFlag = true;
				incPriority += 5;
				posT = i + 1;
				continue;
			}
			if (str[i - 1] == '(' || (modFlag && str[i - 1] == '|')) {
				modFlag = true;
				incPriority += 5;
				posT = i + 1;
				continue;
			}
			modFlag = false;
			incPriority -= 5;
			double number = getNumber(str, posT, i - posT);
			if (tmp)
				tmp->secondOperand = number;
			tmp = new OpData();
			tmp->firstOperand = number;
			tmp->op = str[i];
			list.push_back(tmp);
			add_to_priorList(priorList, new OpPriority(priority(str[i]) + incPriority, std::prev(list.end(), 1)));
			if (priority(str[i - 1]) == 4)
				posT = i + 1;
			continue;
		}

		modFlag = false;

		if (str[i] == '(') {
			incPriority += 5;
			posT = i + 1;
			continue;
		}

		if (str[i] == ')') {
			if (priority(str[i - 1]) == 4)
				posT = i + 1;
			incPriority -= 5;
			continue;
		}

		if (!isdigit(str[i]) && str[i] != '.') {
			//�������� �����, ������� ��� ����� �������� �������� ������ ���������, � ��� ������ ������
			double number = getNumber(str, posT, i - posT);
			if (tmp)
				tmp->secondOperand = number;
			tmp = new OpData();
			tmp->firstOperand = number;
			tmp->op = str[i];
			list.push_back(tmp);
			add_to_priorList(priorList, new OpPriority(priority(str[i]) + incPriority, std::prev(list.end(), 1)));
			posT = i + 1;
		}
	}
	if (tmp && posT <= str.size() - 1)
		tmp->secondOperand = getNumber(str, posT, str.size() - posT);

	/*
		� ������� ���������� ��������� ��������� ������ ��������,
		���� ������, ���������� ��� ������ � ������� �� �����,
		����� �� ��������� ������ � ������� �������� ��������� � ������� ���������
		����������� ��������� ������� �������� ����������� �������� 
		� ������� �������� ���������� ��������, ���� ��� �������� ����.
		������� ��� ������� �� ������
	*/
	double res = 0;
	int errCode = 0;
	for (auto& el : priorList) {
		res = getResult(*el->it, errCode);
		if (errCode) {
			if (errorCode)
				*errorCode = errCode;
			break;
		}
		if (el->it != list.begin()) {
			auto pv = std::prev(el->it, 1);
			(*pv)->secondOperand = res;
		}
		auto nt = std::next(el->it, 1);
		if (nt != list.end()) {
			(*nt)->firstOperand = res;
		}
		delete* el->it;
		list.erase(el->it);
	}

	if (!list.empty()) {
		for (auto& el : list) {
			delete el;
		}
		list.clear();
	}

	for (auto& el : priorList) {
		delete el;
	}
	priorList.clear();

	return res;
}

const std::string printCalcErrorText(int code) {
	switch (code)
	{
	case 1:
		return "Incorrect expression!";
	case 2:
		return "Division by zero is not defined!";
	case 3:
		return "Zero power root is not defined!";
	case 4:
		return "Root of a negative number with an even power is not defined!";
	case 5:
		return "Logarithm of 'x': 'x' must be a positive number!";
	case 6:
		return "Factorial of 'x': 'x' must be a positive integer or zero!";
	default:
		return "Wrong input!";
	}
}