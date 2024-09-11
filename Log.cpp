#include "StdAfx.h"
#include "Log.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <Windows.h>

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
    // Option 1
    /*std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "[%d-%m-%Y %H:%M:%S] ");
    return oss.str(); */

    // Option 2
    /*std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);

    SYSTEMTIME st;
    GetSystemTime(&st);

    char buffer[32];
    sprintf_s(
        buffer,
        sizeof(buffer),
        "[%02d-%02d-%04d %02d:%02d:%02d.%03d] ",
        localTime.tm_mday,
        localTime.tm_mon + 1,
        localTime.tm_year + 1900,
        localTime.tm_hour,
        localTime.tm_min,
        localTime.tm_sec,
        st.wMilliseconds);

    return std::string(buffer);*/

    // Option 3
    SYSTEMTIME st;
    GetLocalTime(&st);

    char buffer[32];
    sprintf_s(
        buffer, 
        sizeof(buffer), 
        "[%02d-%02d-%04d %02d:%02d:%02d.%03d] ",
        st.wDay, 
        st.wMonth, 
        st.wYear,
        st.wHour, 
        st.wMinute, 
        st.wSecond, 
        st.wMilliseconds);

    return std::string(buffer);
}