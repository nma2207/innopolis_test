#pragma once

#include <string>
#include <utility>

class StringProcessor
{
    public:
    virtual std::pair<std::string, std::string> process(const std::string&) = 0;
};