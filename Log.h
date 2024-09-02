#pragma once
#include <fstream>
#include <string>
#include <windows.h>

class Log
{
private:
    Log();

    ~Log();
    
    // Запрет конструктора копирования
    Log(const Log&);

    // Запрет копирования
    Log& operator=(const Log&);

    std::string GetCurrentDateTime();

    std::ofstream logFile;
    CRITICAL_SECTION logCriticalSection;

public:
    static Log& GetInstance();

    // Запись лога (с переводом каретки)
    void WriteMsg(const std::string& message);
};

