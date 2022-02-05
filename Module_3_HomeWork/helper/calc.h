#pragma once
#include <string>

//возврашает результат выражения
double calculate(const std::string& s, int* errCode = nullptr);

//возвращает текст ошибки
const std::string getCalcErrorText(int code);
