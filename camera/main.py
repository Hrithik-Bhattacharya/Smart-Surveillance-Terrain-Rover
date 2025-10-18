import cv2
import numpy as np
import urllib.request
from ultralytics import YOLO

model = YOLO("fire_and_smoke_model.pt")
print("Model loaded.")

stream_url = "YOUR_STREAM_URL" # Replace with your url

print("Connecting to stream...")
stream = urllib.request.urlopen(stream_url)
bytes_data = b''

cv2.namedWindow("Fire & Smoke Detection", cv2.WINDOW_NORMAL)
cv2.resizeWindow("Fire & Smoke Detection", 800, 600)

while True:
    try:
        bytes_data += stream.read(1024)
        a = bytes_data.find(b'\xff\xd8')
        b = bytes_data.find(b'\xff\xd9')

        if a != -1 and b != -1:
            jpg = bytes_data[a:b+2]
            bytes_data = bytes_data[b+2:]

            frame = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)

            results = model(frame, verbose=False)
            annotated_frame = results[0].plot()

            cv2.imshow("Fire & Smoke Detection", annotated_frame)

            if cv2.waitKey(1) & 0xFF == 27:
                break

    except Exception as e:
        print("Error:", e)
        break

cv2.destroyAllWindows()import cv2
import numpy as np
import urllib.request

stream_url = "YOUR_STREAM_URL" 

print("Connecting to stream...")
stream = urllib.request.urlopen(stream_url)
print("Connected!")

bytes_data = b''
cv2.namedWindow("ESP32-CAM", cv2.WINDOW_NORMAL)
cv2.resizeWindow("ESP32-CAM", 800, 600)

while True:
    bytes_data += stream.read(1024)
    a = bytes_data.find(b'\xff\xd8')
    b = bytes_data.find(b'\xff\xd9')

    if a != -1 and b != -1:
        jpg = bytes_data[a:b+2]
        bytes_data = bytes_data[b+2:]

        frame = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)
        if frame is not None:
            cv2.imshow("ESP32-CAM", frame)

        if cv2.waitKey(1) & 0xFF == 27:
            break

cv2.destroyAllWindows()#include <Wire.h>
