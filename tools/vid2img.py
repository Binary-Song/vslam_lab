import cv2
import sys
import os
if(len(sys.argv) < 2):
    print("usage: vid2img <videoInput>")
else:
    if not os.path.exists(f"{sys.argv[1]}/../captures"):
        os.mkdir(f"{sys.argv[1]}/../captures")
    
    vidcap = cv2.VideoCapture(sys.argv[1]) 
    fps = vidcap.get(cv2.CAP_PROP_FPS)      # OpenCV2 version 2 used "CV_CAP_PROP_FPS"
    frame_count = int(vidcap.get(cv2.CAP_PROP_FRAME_COUNT))
    duration = frame_count/fps

    print(f"fps: {fps}")
    print(f"frame_count: {frame_count}")
    print(f"duration: {duration}")
 
    i=0
    while(vidcap.isOpened()):
        ret, frame = vidcap.read()
        if ret == False:
            break
        cv2.imwrite(f"{sys.argv[1]}/../captures/{i}.jpg",frame)
        i+=1
        print(f"writing frame...   {int(i/frame_count*100)}%")