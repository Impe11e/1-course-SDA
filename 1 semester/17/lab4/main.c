#include <stdio.h>
#include <windows.h>

void Print(HANDLE hout, const int x, const int y) {
    SetConsoleCursorPosition(hout, (COORD){x, y});
    SetConsoleOutputCP(CP_UTF8);
    printf("%c", '+');
    Sleep(2);
}

void SnakeDiagonalTraverse(HANDLE hout, const int rows, const int columns) {
    for (int d = 0; d < rows + columns - 1; d++) {
        if ((d & 1) == 0) {  //Парний: зверху вниз. Непарний: знизу вверх
            for (int row = max(0, d - columns + 1), col = d - row; row < rows && col >= 0; row++, col--) {
                Print(hout, col, row);
            }
        } else {
            for (int row = d < rows ? d : rows - 1, col = d - row; row >= 0 && col < columns; row--, col++) {
                Print(hout, col, row);
            }
        }
    }
}

int main(void) {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hout, &csbi);
    // int rows = csbi.srWindow.Bottom - csbi.srWindow.Top;
    // int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int rows = 24;
    int columns = 80;

    SnakeDiagonalTraverse(hout, rows, columns);

    return 0;
}