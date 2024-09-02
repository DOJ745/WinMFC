#pragma once
#include <fstream>
#include <string>
#include <windows.h>

class Log
{
private:
    Log();

    ~Log();
    
    // ������ ������������ �����������
    Log(const Log&);

    // ������ �����������
    Log& operator=(const Log&);

    std::string GetCurrentDateTime();

    std::ofstream logFile;
    CRITICAL_SECTION logCriticalSection;

public:
    static Log& GetInstance();

    // ������ ���� (� ��������� �������)
    void WriteMsg(const std::string& message);
};

