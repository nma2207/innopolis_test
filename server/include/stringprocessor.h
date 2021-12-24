#pragma once

#include <string>
#include <utility>

/**
 * @brief Абстрактный класс для обработки сообщений от клиента
 * (используется паттерн стратегия)
 * 
 */
class StringProcessor
{
    public:
    virtual std::pair<std::string, std::string> process(const std::string&) = 0;
};