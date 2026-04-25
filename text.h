#ifndef TEXT_H
    #define TEXT_H

    #include "common.h"

    static BOOL CAN_INPUT = TRUE;

    BOOL CanInput();

    void SetInput();
    void StopInput();

    static CHAR TEXT[500];
    static CHAR CONFIRMED[500];

    CHAR* GetText();
    CHAR* GetConfirmedText();
    
    static UINT TEXT_SIZE = 0;
    static UINT CONFIRMED_SIZE = 0;

    UINT GetTextSize();
    UINT GetConfirmedSize();

    void AppendChar(CHAR c);
    void EraseChar();

    void ConfirmText();

    void ClearText();
    void ClearConfirmed();

#endif