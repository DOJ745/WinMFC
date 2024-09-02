#pragma once
#include <fstream>
#include <string>
#include <windows.h>

class Log
{
private:
    Log();

    ~Log();
    //Log(const Log&) = delete;
    //Log& operator=(const Log&) = delete;

    std::string GetCurrentDateTime();

    std::ofstream logFile;
    CRITICAL_SECTION logCriticalSection;

public:
    static Log& GetInstance();

    // Запись лога (с переводом каретки)
    void WriteMsg(const std::string& message);
};

