import cv2
import sys
import numpy as np
import cv2 as cv
import os
if(len(sys.argv) != 5):
    print("usage: getpix <pic> <r> <g> <b>")
else: 
    pic = sys.argv[1]
    r = int(sys.argv[2])
    g = int(sys.argv[3])
    b = int(sys.argv[4])

    img = cv.imread(pic, cv.IMREAD_COLOR)
    height, width, depth = img.shape

    for i in range(0, height):
        for j in range(0,  width ):
            if img[i,j,0] == b and img[i,j,1] == g and img[i,j,2] == r:
                print(f"{j}, {i}") 