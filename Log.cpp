#include "StdAfx.h"
#include "Log.h"
#include <ctime>
#include <sstream>
#include <iomanip>

Log::Log()
{
    InitializeCriticalSection(&logCriticalSection);
    logFile.open("log.txt", std::ios::app);

    if (!logFile.is_open())
    {
        throw std::runtime_error("Не удалось открыть файл лога");
    }
}

Log::~Log()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
    DeleteCriticalSection(&logCriticalSection);
}

Log& Log::GetInstance()
{
    static Log instance;
    return instance;
}

void Log::WriteMsg(const std::string& msg)
{
    EnterCriticalSection(&logCriticalSection);
    logFile << GetCurrentDateTime() << msg << std::endl;
    LeaveCriticalSection(&logCriticalSection);
}

std::string Log::GetCurrentDateTime()
{
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "[%d-%m-%Y %H:%M:%S] ");
    return oss.str();
}