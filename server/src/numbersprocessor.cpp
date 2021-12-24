#include "numbersprocessor.h"

#include <cctype>
#include <iostream>
#include <numeric>
#include <regex>
#include <vector>

namespace {

void extractNumbers(const std::string& message, std::vector<int>& numbers)
{
    std::regex rgx("[^\\d]+");

    std::sregex_token_iterator iter(message.begin(),
                                    message.end(),
                                    rgx,
                                    -1);
    std::sregex_token_iterator end;

    for (; iter != end; ++iter)
    {
        std::string numStr = *iter;
        if (numStr.size() > 0)
            numbers.push_back(std::stoi(numStr));
    }
}

} // namespace

/**
 * @brief Обрабатывает строку от клиента
 * 
 * @param message то что прислал клиент
 * @return std::pair<std::string, std::string> first - отсортированные числа, second - их сумма.
 *  при отсутствии чисел возвращается пара {"-1", "-1"} 
 */
std::pair<std::string, std::string> NumbersProcessor::process(const std::string &message)
{
    std::vector<int> numbers;
    extractNumbers(message, numbers);

    if (numbers.size() == 0)
        return {"-1", "-1"};
    
    std::sort(numbers.begin(), numbers.end());
    
    std::stringstream ss;
    for(auto it = numbers.cbegin(); it != numbers.cend(); it++)
    {
        ss << std::to_string(*it);
        if (it != numbers.cend() - 1)
            ss << " ";
    }

    std::string sum = std::to_string(std::accumulate(numbers.begin(), numbers.end(), 0));

    return {ss.str(), sum};
}