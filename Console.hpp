#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_BACKSPACE 8
#define KEY_ENTER 13
#define KEY_ESC 27

enum Colors {
    BLUE=1,
    GREEN=2,
    RED=4,
    YELLOW=6,
    WHITE=7,
    LIGHT_BLUE=9,
    LIGHT_RED=12,
    LIGHT_YELLOW=14,
    LIGHT_WHITE=15
};

class Console {
    private:
        HANDLE m_Handle;

    public:
        Console(const std::string& name) {
            m_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTitle(name.c_str());

            Clear();
            SetTextColor(WHITE);
        }

        ~Console() {
            Clear();
            SetTextColor(WHITE);
        }

        inline void SetTextColor(const int color) const {
            SetConsoleTextAttribute(m_Handle, color);
        }

        void Clear() const {
            DWORD charsWritten;
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            DWORD consoleSize;

            // Get the number of character cells in the current buffer.
            if (!GetConsoleScreenBufferInfo(m_Handle, &csbi)) {
                return;
            }
            consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

            // Fill the entire screen with blanks.
            FillConsoleOutputCharacter(m_Handle, ' ', consoleSize, {0, 0}, &charsWritten);

            // Reset the cursor to the top left.
            MoveCursor(0, 0);
        }

        void MoveCursor(const int x, const int y) const {
            COORD coord = {static_cast<short>(x), static_cast<short>(y)};
            SetConsoleCursorPosition(m_Handle, coord);
        }

        void PrintBuffer(const std::vector<std::string>& buffer) {
            for (size_t i = 0; i < buffer.size(); ++i) {
                std::cout << buffer[i] << std::endl;
            }
        }
};
