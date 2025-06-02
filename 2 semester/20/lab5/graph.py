import math
import tkinter as tk
import random

n3 = 2
n4 = 0
vertexes = n3 + 10

variant = 4220
random.seed(variant)

k = 1 - n3 * 0.01 - n4 * 0.005 - 0.15

def calculate_element(k): 
    return math.floor(random.random() * 2 * k)

matrix_dir = [[0] * vertexes for _ in range(vertexes)]

for i in range(vertexes):
    for j in range(vertexes):
        matrix_dir[i][j] = calculate_element(k)

root = tk.Tk()
root.title("Graph")

canvas = tk.Canvas(root, width=800, height=800, bg="white")
canvas.pack()

mid_x = mid_y = 400
angle = math.pi * 2 / vertexes
R = 20

def get_x(i): 
    return mid_x + math.sin(i * angle) * 200

def get_y(i): 
    return mid_y - math.cos(i * angle) * 200

def rotate_around_center(x, y, cx, cy, theta):
    x -= cx
    y -= cy
    new_x = x * math.cos(theta) - y * math.sin(theta) + cx
    new_y = x * math.sin(theta) + y * math.cos(theta) + cy
    return new_x, new_y

def draw_graph(matrix, paths): 
    vertexes = len(matrix)
    width_regular = 1
    width_highlight = 3
    
    for i in range(vertexes):
        x = get_x(i) - R
        y = get_y(i) - R
        if(i == 0):
            canvas.create_oval(x, y, x + 2 * R, y + 2 * R, fill="magenta")
        else:
            canvas.create_oval(x, y, x + 2 * R, y + 2 * R, fill="white")
        canvas.create_text(x + R, y + R, text=str(i + 1), font=("Montserrat", 12))

    for i in range(vertexes):
        for j in range(vertexes):
            if matrix[i][j] == 1:
                if i == j:
                    cx, cy = get_x(i), get_y(i)
                    theta = i * angle 

                    cx += R * math.sin(theta)
                    cy -= R * math.cos(theta)

                    dx = 3 * R / 4
                    dy = R * (1 - math.sqrt(7)) / 4

                    p1 = (cx - dx, cy - dy)
                    p2 = (cx - 3 * dx / 2, cy - R / 2)
                    p3 = (cx + 3 * dx / 2, cy - R / 2)
                    p4 = (cx + dx, cy - dy)

                    p1 = rotate_around_center(p1[0], p1[1], cx, cy, theta)
                    p2 = rotate_around_center(p2[0], p2[1], cx, cy, theta)
                    p3 = rotate_around_center(p3[0], p3[1], cx, cy, theta)
                    p4 = rotate_around_center(p4[0], p4[1], cx, cy, theta)

                    canvas.create_line(p1[0], p1[1], p2[0], p2[1], width=width_regular)
                    canvas.create_line(p2[0], p2[1], p3[0], p3[1], width=width_regular)
                    canvas.create_line(p3[0], p3[1], p4[0], p4[1], width=width_regular, arrow=tk.LAST)
                else:
                    x1, y1 = get_x(i), get_y(i)
                    x2, y2 = get_x(j), get_y(j)

                    dx, dy = x2 - x1, y2 - y1
                    length = math.sqrt(dx ** 2 + dy ** 2)

                    dx /= length
                    dy /= length

                    x1 += dx * R
                    y1 += dy * R
                    x2 -= dx * R
                    y2 -= dy * R

                    canvas.create_line(x1, y1, x2, y2, width=width_regular, arrow=tk.LAST)

    visited_vertices = [False] * vertexes

    def highlight_path(k):
        if k < len(paths):
            i = paths[k][0]

            j = paths[k][1]
            x1, y1 = get_x(i), get_y(i)
            x2, y2 = get_x(j), get_y(j)

            dx, dy = x2 - x1, y2 - y1
            length = math.sqrt(dx ** 2 + dy ** 2)

            dx /= length
            dy /= length

            x1 += dx * R
            y1 += dy * R
            x2 -= dx * R
            y2 -= dy * R

            canvas.create_line(x1, y1, x2, y2, width=width_highlight, arrow=tk.LAST, fill="magenta")
            canvas.update()
            canvas.after(1000, highlight_path, k + 1)

            visited_vertices[i] = True 

            x = get_x(j) - R
            y = get_y(j) - R
            canvas.create_oval(x, y, x + 2 * R, y + 2 * R, fill="magenta")
            canvas.create_text(x + R, y + R, text=str(j + 1), font=("Montserrat", 12))

    highlight_path(0)

    root.mainloop()

