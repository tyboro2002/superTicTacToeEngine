#include <Windows.h>
#include <stdio.h>

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the console text color to red
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);

    // Unicode character for a shaded rectangle (▓)
    wchar_t unicodeChar = L'\x2588';

    // Write the Unicode character to the console
    DWORD charsWritten;
    WriteConsoleW(hConsole, &unicodeChar, 1, &charsWritten, NULL);

    // Reset console text color
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    return 0;
}
