#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const char ProgName[] = "Lab 3";
const int vert = 12;
int variant;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
  AllocConsole();
  FILE* fp;
  freopen_s(&fp, "CONOUT$", "w", stdout);
  freopen_s(&fp, "CONIN$", "r", stdin);

  printf("Enter number of variant: 1 for directed graph, 2 for undirected\n");
  scanf("%i", &variant);

  WNDCLASS w;
  w.lpszClassName = ProgName;
  w.hInstance = hInstance;
  w.lpfnWndProc = WndProc;
  w.hCursor = LoadCursor(NULL, IDC_ARROW);
  w.hIcon = 0;
  w.lpszMenuName = 0;
  w.hbrBackground = WHITE_BRUSH;
  w.style = CS_HREDRAW | CS_VREDRAW;
  w.cbClsExtra = 0;
  w.cbWndExtra = 0;
  if (!RegisterClass(&w)) return 0;

  HWND hWnd;
  MSG lpMsg;
  hWnd = CreateWindow(
    ProgName, "",
    WS_OVERLAPPEDWINDOW, 100, 100, 1000, 700,
    NULL, NULL, hInstance, NULL
  );
  ShowWindow(hWnd, nCmdShow);

  while (GetMessage(&lpMsg, NULL, 0, 0)) {
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
  }
  return (lpMsg.wParam);
}

HDC hdc;
PAINTSTRUCT ps;

void arrow(HDC hdc, int x1, int y1, int x2, int y2, int radius) {
  double dx = x2 - x1, dy = y2 - y1;
  int arrowLength = 10;
  double arrowAngle = 36.0 * 3.14 / 180.0;
  double angle = atan2(dy, dx);
  double xIntersec = x2 - radius * cos(angle);
  double yIntersec = y2 - radius * sin(angle);
  double x3 = xIntersec - arrowLength * cos(angle - arrowAngle);
  double y3 = yIntersec - arrowLength * sin(angle - arrowAngle);
  double x4 = xIntersec - arrowLength * cos(angle + arrowAngle);
  double y4 = yIntersec - arrowLength * sin(angle + arrowAngle);

  MoveToEx(hdc, x3, y3, NULL);
  LineTo(hdc, xIntersec, yIntersec);
  LineTo(hdc, x4, y4);
}

double **makeGraph(int n) {
  srand(4227);
  double **graph = (double **) malloc(n * sizeof(double *));
  for (int i = 0; i < n; i++) {
    graph[i] = (double *) malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      graph[i][j] = ((double) rand() / RAND_MAX) * 2.0;
    }
  }
  return graph;
}

double **formatGraph(double **arr, int vertices, int n3, int n4) {
  double multiplier = (1.0 - n3 * 0.02 - n4 * 0.005 - 0.25);
  for (int i = 0; i < vertices; i++) {
    for (int j = 0; j < vertices; j++) {
      arr[i][j] *= multiplier;
      arr[i][j] = arr[i][j] < 1.0 ? 0 : 1;
    }
  }
  return arr;
}

double **mirrorGraph(double **arr, int vertices) {
  double **undirected = (double **) malloc(vertices * sizeof(double *));
  for (int i = 0; i < vertices; i++) {
    undirected[i] = (double *) malloc(vertices * sizeof(double));
    for (int j = 0; j < vertices; j++) {
      undirected[i][j] = arr[i][j];
    }
  }

  for (int i = 0; i < vertices; i++) {
    for (int j = 0; j < vertices; j++) {
      if (undirected[i][j] != undirected[j][i]) {
        undirected[i][j] = 1;
        undirected[j][i] = 1;
      }
    }
  }
  return undirected;
}

void deleteMatrix(double **arr, int vertices) {
  for (int i = 0; i < vertices; i++) {
    free(arr[i]);
  }
  free(arr);
}

void printGraph(double **arr, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%.0f ", arr[i][j]);
    }
    printf("\n");
  }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
  switch (messg) {
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      double **directed = formatGraph(makeGraph(vert), vert, 1, 6);
      double **undirected = mirrorGraph(directed, vert);

      printf("\nDirected matrix:\n");
      printGraph(directed, vert);
      printf("\nUndirected matrix:\n");
      printGraph(undirected, vert);

      char *nn[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
      int nx[12], ny[12] = {};
      int dx = 16, dy = 16, dtx = 5;
      int Xcenter = 500, Ycenter = 300, R = 250;

      for (int i = 0; i < 11; i++) {
        double angle = i * (360.0 / 11.0);
        nx[i] = Xcenter + (int)(R * sin(angle * (3.14 / 180)));
        ny[i] = Ycenter - (int)(R * cos(angle * (3.14 / 180)));
      }
      nx[11] = Xcenter;
      ny[11] = Ycenter;

      HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
      HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
      SelectObject(hdc, KPen);

      for (int i = 0; i < vert; i++) {
        for (int j = (variant == 1 ? 0 : i); j < vert; j++) {
          BOOL left = (nx[j] < Xcenter);
          if (variant == 1 && directed[i][j] == 1 && j != i) {
            MoveToEx(hdc, nx[i], ny[i], NULL);
            LineTo(hdc, nx[j], ny[j]);
            arrow(hdc, nx[i], ny[i], nx[j], ny[j], dx);
          }
          if (variant == 2 && undirected[i][j] == 1 && j != i) {
            MoveToEx(hdc, nx[i], ny[i], NULL);
            LineTo(hdc, nx[j], ny[j]);
          }
          if ((i == j) && ((variant == 1 && directed[i][j]) || (variant == 2 && undirected[i][j]))) {
            if (left) {
              Ellipse(hdc, nx[i] - 2 * dx, ny[i] - 2 * dy, nx[i], ny[i]);
            } else {
              Ellipse(hdc, nx[i], ny[i], nx[i] + 2 * dx, ny[i] + 2 * dy);
            }
          }
        }
      }

      SelectObject(hdc, BPen);
      for (int i = 0; i < vert; i++) {
        Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
        TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], strlen(nn[i]));
      }

      EndPaint(hWnd, &ps);
      deleteMatrix(directed, vert);
      deleteMatrix(undirected, vert);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      return DefWindowProc(hWnd, messg, wParam, lParam);
  }
  return 0;
}
