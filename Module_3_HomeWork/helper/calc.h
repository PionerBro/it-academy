#pragma once
#include <string>

//���������� ��������� ���������
double calculate(const std::string& s, int* errCode = nullptr);

//���������� ����� ������
const std::string getCalcErrorText(int code);
