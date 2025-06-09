#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <math.h>

enum SIDE {
  left,
  right
};

enum SYMBOLS {
  head = '*',
  vert = '|',
  start = '#',
  right_top = '\\',
  right_bottom = '/',
  left_top = '/',
  left_bottom = '\\'
};

enum COLORS {
  arrow = 4,
  entry = 2,
  tail = 7
};

const int width = 80;
const int height = 24;
const useconds_t delay = 10000;

enum SYMBOLS get_symbol(const int iteration) {
  if (iteration == 0) {
    return start;
  }

  if (iteration == width * height / 2 - 1) {
    return vert;
  }

  const int temp = (int)floor((double)iteration / height);

  if (temp % 2 == 0) {
    if (iteration % height == 0) {
      return right_top;
    }

    if (iteration % height == height - 1) {
      return left_bottom;
    }
  } else {
    if (iteration % height == 0) {
      return left_top;
    }

    if (iteration % height == height - 1) {
      return right_bottom;
    }
  }

  return vert;
}

void mutate_pos(
  COORD* pos,
  const int iteration,
  const enum SIDE side
) {
  const int temp = (int)floor((double)iteration / height);

  pos->Y = temp % 2 == 0
    ? side == left
      ? height - iteration % height - 1
      : iteration % height
    : side == left
      ? iteration % height
      : height - iteration % height - 1;

  switch (side) {
    case left:
      pos->X = width / 2 - temp - 1;
      break;
    case right:
      pos->X = width / 2 + temp;
      break;
  }
}

int main(void) {
  const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;

  for (int i = 0; i <= width * height / 2; i++) {
    if (i != width * height / 2) {
      SetConsoleTextAttribute(h_console, arrow);

      mutate_pos(&pos, i, left);
      SetConsoleCursorPosition(h_console, pos);
      printf("%c", head);

      mutate_pos(&pos, i, right);
      SetConsoleCursorPosition(h_console, pos);
      printf("%c", head);
    }

    if (i != 0) {
      SetConsoleTextAttribute(h_console, i - 1 == 0 ? entry : tail);

      mutate_pos(&pos, i - 1, left);
      SetConsoleCursorPosition(h_console, pos);
      printf("%c", get_symbol(i - 1));

      mutate_pos(&pos, i - 1, right);
      SetConsoleCursorPosition(h_console, pos);
      printf("%c", get_symbol(i - 1));
    }

    usleep(delay);
  }

  usleep(delay * delay);

  return 0;
}