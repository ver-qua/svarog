#ifndef LLOG_H_
#define LLOG_H_

#include <iostream>
#include <fstream>

namespace svarog
{
    class Log
    {
        // Путь до файла журнала
        std::string path = "";
        
    public:

        // Конструкторы
        Log();
        
        Log(std::string path);

        // Установка пути до файла журнала
        void SetPath(std::string path);

        // Запись в журнал
        void Write(std::string text, std::string caller);
    };

    Log::Log()
    {
        this->path = "";
    }

    Log::Log(std::string path)
    {
        std::ifstream file(path, std::ios::app);
        file.close();

        this->path = path;  
    }

    void Log::SetPath(std::string path)
    {
        std::ifstream file(path, std::ios::app);
        file.close();     
        
        this->path = path;
    }

    void Log::Write(std::string text, std::string caller = "Anonymous")
    {
        std::ofstream file(this->path, std::ios::app);

        time_t now = time(0);
        char *date = ctime(&now);
        
        file << caller << " called log. " << date << text << std::endl << std::endl;

        file.close();
    }

}



#endif