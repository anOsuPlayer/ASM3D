#include "text.h"

BOOL CanInput() {
    return CAN_INPUT;
}

void SetInput() {
    CAN_INPUT = TRUE;
}

void StopInput() {
    CAN_INPUT = FALSE;
}

CHAR* GetText() {
    return TEXT;
}

CHAR* GetConfirmedText() {
    return CONFIRMED;
}

UINT GetTextSize() {
    return TEXT_SIZE;
}

UINT GetConfirmedSize() {
    return CONFIRMED_SIZE;
}

void AppendChar(CHAR c) {
    if (TEXT_SIZE < 200) {
        TEXT[TEXT_SIZE++] = c;
        TEXT[TEXT_SIZE] = '\0';
    }
}

void EraseChar() {
    if (TEXT_SIZE > 0) {
        TEXT[--TEXT_SIZE] = '\0';
    }
}

void ConfirmText() {
    strcpy(CONFIRMED, TEXT);
    CONFIRMED_SIZE = TEXT_SIZE;
    
    ClearText();
}

void ClearText() {
    TEXT_SIZE = 0;
    TEXT[0] = '\0';
}

void ClearConfirmed() {
    CONFIRMED_SIZE = 0;
    CONFIRMED[0] = '\0';
}