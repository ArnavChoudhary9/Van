#include "Console.hpp"

int main() {
    Console console("Test");
    
    std::vector<std::string> buffer = {""};
    int row = 0, column = 0;

    while(true) {
        console.Clear();
        console.PrintBuffer(buffer);
        console.MoveCursor(column, row);

        int key = _getch();

        if (key == 0 || key == 224) { // Arrow keys or special keys
            key = _getch(); // Get the second part of the key code
            if (key == KEY_UP && row > 0) {
                row--;
                column = std::min(column, static_cast<int>(buffer[row].size()));
            } else if (key == KEY_DOWN && row < static_cast<int>(buffer.size()) - 1) {
                row++;
                column = std::min(column, static_cast<int>(buffer[row].size()));
            } else if (key == KEY_LEFT && column > 0) {
                column--;
            } else if (key == KEY_RIGHT && column < static_cast<int>(buffer[row].size())) {
                column++;
            }
        } else if (key == KEY_BACKSPACE) { // Backspace
            if (column > 0) {
                buffer[row].erase(column - 1, 1);
                column--;
            } else if (row > 0) { // Merge lines
                column = buffer[row - 1].size();
                buffer[row - 1] += buffer[row];
                buffer.erase(buffer.begin() + row);
                row--;
            }
        } else if (key == KEY_ENTER) { // Enter key
            std::string newLine = buffer[row].substr(column);
            buffer[row] = buffer[row].substr(0, column);
            buffer.insert(buffer.begin() + row + 1, newLine);
            row++;
            column = 0;
        } else if (key == KEY_ESC) { // Escape key to exit
            break;
        } else { // Regular character input
            buffer[row].insert(column, 1, static_cast<char>(key));
            column++;
        }


        Sleep(10);
    }

    return 0;
}
