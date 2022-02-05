#pragma once
#include <string>

//возврашает результат выражения
double calculate(const std::string& s, int* errCode = nullptr);

//выводит текст ошибки
const std::string printCalcErrorText(int code);
