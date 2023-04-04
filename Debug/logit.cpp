#ifndef _LOGIT_H_
#define _LOGIT_H_

#include<iostream>
#include<string>
#include<fstream>

namespace svg
{
    void logit(const std::string& message, const std::string& caller = "Anonymus") // объявление функции logit с двумя аргументами: сообщение и имя вызывающего (по умолчанию - "Anonymus")
    {
        time_t now = time(0); // получаем текущее время в формате типа time_t
        char *date = ctime(&now); // преобразуем текущее время в строку
    
        std::cout << '|' << date << "|>" << "From " << caller << ": " << message << '\n' << std::endl; // выводим отформатированное сообщение в консоль
    }
}

#endif