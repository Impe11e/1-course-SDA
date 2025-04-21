import math
import tkinter as tk
import random

n3 = 2
n4 = 0
vertexes = n3 + 10

variant = 4220
random.seed(variant)

k = 1 - n3 * 0.01 - n4 * 0.005 - 0.05

def calculate_element(k): 
    return math.floor(random.random() * 2 * k)

matrix_dir = [[0] * vertexes for _ in range(vertexes)]
matrix_undir = [[0] * vertexes for _ in range(vertexes)]

for i in range(vertexes):
    for j in range(vertexes):
        matrix_dir[i][j] = calculate_element(k)

for i in range(vertexes):
    for j in range(vertexes):
        matrix_undir[i][j] = matrix_dir[i][j] or matrix_dir[j][i]

root = tk.Tk()
root.title("Graph")

canvas = tk.Canvas(root, width=800, height=800, bg="white")
canvas.pack()

mid_x = mid_y = 400
angle = math.pi * 2 / vertexes
R = 20

def get_x(i): 
    return mid_x + math.sin(i * angle) * 300

def get_y(i): 
    return mid_y - math.cos(i * angle) * 300

def rotate_around_center(x, y, cx, cy, theta):
    x -= cx
    y -= cy
    new_x = x * math.cos(theta) - y * math.sin(theta) + cx
    new_y = x * math.sin(theta) + y * math.cos(theta) + cy
    return new_x, new_y

def draw_graph(matrix, paths, weights): 
    vertexes = len(matrix)
    
    for i in range(vertexes):
        x = get_x(i) - R
        y = get_y(i) - R

        canvas.create_oval(x, y, x + 2 * R, y + 2 * R, fill="white")
        canvas.create_text(x + R, y + R, text=str(i + 1), font=("Montserrat", 12))

    for i in range(vertexes):
        for j in range(vertexes):
            if matrix[i][j] == 1 and i <= j:
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

                    canvas.create_line(p1[0], p1[1], p2[0], p2[1], width=2)
                    canvas.create_line(p2[0], p2[1], p3[0], p3[1], width=2)
                    canvas.create_line(p3[0], p3[1], p4[0], p4[1], width=2)
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

                    canvas.create_line(x1, y1, x2, y2, width=2, tags="arr")

                    if weights[i][j] != 0:
                        if abs(i - j) == vertexes / 2:
                            mx = (x1 + x2) / 2
                            my = (y1 + y2) / 2

                            dx = x2 - x1
                            dy = y2 - y1

                            length = math.sqrt(dx ** 2 + dy ** 2)
                            dx /= length
                            dy /= length

                            offset = 5 * R / 2
                            mx += dx * offset
                            my += dy * offset
                        else:
                            mx = (x1 + x2) / 2
                            my = (y1 + y2) / 2
                        size = 9
                        canvas.create_text(mx, my, text=str(weights[i][j]), font=("Montserrat", size), fill="black", tags="bgt")
                        canvas.create_rectangle(mx - size - 1, my - size - 1, mx + size + 1, my + size + 1, fill="#DDDDDD", outline="black", tags="bg")
                        canvas.tag_raise("bgt", "bg")
                        canvas.tag_lower("arr")

    visited_vertices = [False] * vertexes

    def highlight_path(k, total, total_text_id):
        if k < len(paths):
            i = paths[k][0]
            j = paths[k][1]
            
            total += weights[i][j]
            
            canvas.delete(total_text_id)
            
            total_text_id = canvas.create_text(5*R, R, text=f"Total weight: {total}", font=("Montserrat", 12), fill="black")
            
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

            canvas.create_line(x1, y1, x2, y2, width=2.5, fill="orange", tags="arr")

            visited_vertices[i] = True 
            x = get_x(i) - R
            y = get_y(i) - R
            canvas.create_oval(x, y, x + 2 * R, y + 2 * R, fill="orange")
            canvas.create_text(x + R, y + R, text=str(i + 1), font=("Montserrat", 12))

            if abs(i - j) == vertexes / 2:
                mx = (x1 + x2) / 2
                my = (y1 + y2) / 2

                dx = x2 - x1
                dy = y2 - y1

                length = math.sqrt(dx ** 2 + dy ** 2)
                dx /= length
                dy /= length

                offset = 5 * R / 2
                mx += dx * offset
                my += dy * offset
            else:
                mx = (x1 + x2) / 2
                my = (y1 + y2) / 2

            size = 9

            canvas.create_rectangle(mx - size - 1, my - size - 1, mx + size + 1, my + size + 1, fill="orange", outline="black", tags="bg")
            canvas.create_text(mx, my, text=str(weights[i][j]), font=("Montserrat", size), fill="black", tags="bgt")
            canvas.tag_raise("bgt", "bg")
            canvas.tag_lower("arr")

            visited_vertices[j] = True 
            x = get_x(j) - R
            y = get_y(j) - R
            canvas.create_oval(x, y, x + 2 * R, y + 2 * R, fill="orange")
            canvas.create_text(x + R, y + R, text=str(j + 1), font=("Montserrat", 12))

            canvas.update()
            canvas.after(1000, highlight_path, k + 1, total, total_text_id)

        return total_text_id


    total = 0
    total_text_id = canvas.create_text(5*R, R, text=f"Total weight: {total}", font=("Montserrat", 12), fill="black")
    highlight_path(0, total, total_text_id)



    root.mainloop()

