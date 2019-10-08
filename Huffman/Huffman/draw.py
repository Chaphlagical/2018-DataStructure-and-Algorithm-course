import cv2 as cv
import numpy as np
import os

r = 1

def uint_x(n, width):
    return width / 2 ** n

str = open("Tree.txt").read().split('\n')
tree = []
for i in str:
    tree.append(i.split(' '))
tree = tree[:-1]
deep = 0
for i in tree:
    if deep < len(i[1]):
        deep = len(i[1])
N = deep + 1

width = int((2 ** N + 1) / 10 ** 11 * 1.3)+100
height = int((2 ** (N - 1) + 2) / 10 ** 11 * 1.3) + 50
unit_y = height / (2 * deep)

def get_point(x, y):
    if x < 2 ** (y - 1):
        return (int((2 * x - 1) * (uint_x(y, width))), int(4*y * (unit_y)))
    else:
        return (int((2 * x - 1) * (uint_x(y, width))), int(4*y * (unit_y)))


def draw_circle(img, x, y):  # x:index y:deep
    R = r
    while (R > 0):
        cv.circle(img, get_point(x, y), R, (255, 0, 0), 1)
        R -= 1


def draw_line(img, x, y):
    if y > 1:
        cv.line(img, get_point(x, y), get_point(int((x - 1) / 2) + 1, y - 1), (255, 0, 0), 1)


def Huffman2point(code):
    if code != '':
        y = len(code) + 1
        x = 1
        for i in range(len(code)):
            x += int(code[i]) * 2 ** (len(code) - i - 1)
        return x, y


img = np.zeros((height, width, 3), np.uint8)

def get_x(code):
    x = 0
    for i in range(len(code)):
        x += int(code[i]) * 2 ** (len(code) - i - 1)
    x += 1
    return x

print("File compare:")
print("Run:")
print("comm -3 stdio.h stdio_decode.txt")
print("Result:")
os.system("comm -3 stdio.h stdio_decode.txt")
print("The same")
print("\nPress Enter to show the tree")
input()

draw_circle(img, 1, 1)
draw_line(img, 1, 1)



for i in tree:
    if i[1] != '':
        x = y = 1
        for j in i[1]:
            y += 1
            x = get_x(i[1][0:y - 1])
            draw_circle(img, x, y)
            draw_line(img, x, y)
        x, y = get_point(x, y)
        cv.putText(img, chr(int(i[0])), (x, y), cv.LINE_4, 0.4, (0, 255, 0), 1)

os.remove("Tree.txt")
cv.namedWindow("Tree", cv.WINDOW_AUTOSIZE)
cv.imshow("Tree", img)
cv.waitKey(0)
cv.destroyWindow("Tree")