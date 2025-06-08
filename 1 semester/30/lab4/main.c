#include <stdio.h>
#include <windows.h>

int main()
{
    int x, y;
    int dx, dy;
    int heightMatrix;
    int widthMatrix;
    int startX, startY;
    int coefY;

    COORD coord;
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hout, &csbi);
    widthMatrix = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    heightMatrix = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    coefY = heightMatrix & 1;

    if (heightMatrix < widthMatrix)
    {
        y = (heightMatrix >> 1) - 1 + coefY;
        x = y;
    }

    startX = x;
    startY = y;

    dx = 1;
    dy = 0;

    while (x>=0 && y>=0 && x < widthMatrix && y < heightMatrix)
    {
        Sleep(1);
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        SetConsoleTextAttribute(hout, 5);
        printf("#");

        x += dx;
        y += dy;

        if (x == widthMatrix - startX + 1)
        {
            dx = 0;
            dy = -1;
            x--;
            y--;
            startX--;
        }
        else if (y == startY - 2)
        {
            x--;
            y++;
            dx = -1;
            dy = 0;
            startY--;
        }
        else if (x == startX - 1)
        {
            dx = 0;
            dy = 1;
            x++;
            y++;
        }
        else if (y == heightMatrix - startY - 1 + coefY)
        {
            dx = 1;
            dy = 0;
            x++;
            y--;
        }
    }
    return 0;
}
