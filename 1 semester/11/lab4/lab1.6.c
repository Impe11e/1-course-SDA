#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

int min(int a, int b);
void draw(int x, int y);

int main()
{
    initscr();
    noecho();
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);

    int m, n;
    getmaxyx(stdscr, m, n);

    int yn = m - 1;
    int xn = n - 1;
    for (int p = 0; p < min(m, n) / 2; p++)
    {
        // Moving down
        for (int i = p; i < yn - p; i++)
        {
            draw(i, xn - p);
        }
        // Moving left
        for (int j = xn - p; j > p; j--)
        {
            draw(yn - p, j);
        }
        // Moving up
        for (int i = yn - p; i > p; i--)
        {
            draw(i, p);
        }
        // Moving right
        for (int j = p; j < xn - p; j++)
        {
            draw(p, j);
        }
    }

    if (min(m, n) % 2 != 0)
    {
        if (m < n)
        {
            for (int j =  min(m, n) / 2; j <= xn -  min(m, n) / 2; j++) {
                draw(m / 2, j);
            }
        } else if (m >= n) {
            for (int i =  min(m, n) / 2; i <= yn - min(m, n) / 2; i++) {
                draw(i, n / 2);
            }
        }
    }
getch();
endwin();
    return 0;
}

int min(int a, int b)
{
return a < b ? a : b;
}

void draw(int x, int y)
{
    attron(COLOR_PAIR(1));
    mvaddch(x, y, '#');
    refresh();
    usleep(20000);
}



