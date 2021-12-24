#pragma once

#include "stringprocessor.h"

/**
 * @brief Класс который реализует необходимую логику : извлекает числа, сортирует, считает сумму.
 * 
 */
class NumbersProcessor : public StringProcessor
{
public:
    std::pair<std::string, std::string> process(const std::string &) override;
};