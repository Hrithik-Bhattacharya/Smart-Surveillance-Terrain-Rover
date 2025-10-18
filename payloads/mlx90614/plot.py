import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from collections import deque

# Adjust this to your Arduino's serial port
SERIAL_PORT = 'COM3'  # or '/dev/ttyUSB0' on Linux/Mac
BAUD_RATE = 9600

# Initialize serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

# Data buffer
max_points = 100
temps = deque([0]*max_points, maxlen=max_points)

# Setup plot
fig, ax = plt.subplots()
line, = ax.plot(range(max_points), temps)
ax.set_ylim(20, 50)  # Adjust based on expected temperature range
ax.set_title("Live MLX90614 Temperature Readings")
ax.set_xlabel("Time (s)")
ax.set_ylabel("Temperature (°C)")

def update(frame):
    try:
        raw = ser.readline().decode('utf-8').strip()
        temp = float(raw)
        temps.append(temp)
        line.set_ydata(temps)
    except:
        pass
    return line,

ani = FuncAnimation(fig, update, interval=1000)
plt.show()
