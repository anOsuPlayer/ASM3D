#ifndef TEXT_H
    #define TEXT_H

    #include "common.h"

    BOOL CanInput();

    void SetInput();
    void StopInput();

    CHAR* GetText();
    CHAR* GetConfirmedText();

    UINT GetTextSize();
    UINT GetConfirmedSize();

    void AppendChar(CHAR c);
    void EraseChar();

    void ConfirmText();

    void ClearText();
    void ClearConfirmed();

#endif