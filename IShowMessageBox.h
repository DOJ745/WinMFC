#pragma once
#include <afxwin.h>
class IShowMessageBox
{
public:
    virtual void ShowMsgBox() = 0;
    /*virtual void ShowMsgBox()
    {
        MessageBoxA(NULL,
            "Message box from interface",
            "SOLID Principles",
            MB_OK | MB_ICONINFORMATION);
    }*/
    virtual ~IShowMessageBox() 
    {
        TRACE("\n\t=== IShowMessageBox destructor ===\t\n");
    }
};

class MessageDisplayer : public IShowMessageBox
{
public:
    MessageDisplayer() {}
    ~MessageDisplayer() 
    {
        TRACE("\n\t=== MessageDisplayer destructor ===\t\n");
    }
    void ShowMsgBox() override
    {
        MessageBoxA(NULL, 
            "Message box from interface", 
            "SOLID Principles", 
            MB_OK | MB_ICONINFORMATION);
    } 
};