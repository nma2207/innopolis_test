#pragma once

#include "stringprocessor.h"

class NumbersProcessor : public StringProcessor
{
    public:
    std::pair<std::string, std::string> process(const std::string&) override;
};