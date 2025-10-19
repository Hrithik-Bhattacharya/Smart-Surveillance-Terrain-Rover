import serial
import time
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

# Serial connection
ser = serial.Serial('COM3', 9600, timeout=1) #Update with your COM port
time.sleep(2) # Allow Arduino/ESP32 to reset

# Data storage
max_len = 100 # How many data points to show on graph
data = deque([0]*max_len, maxlen=max_len) # Rolling buffer

# Plot setup
fig, ax = plt.subplots()
line, = ax.plot(data)
ax.set_ylim(0, 100) # Adjust Y-axis range to your sensor values
ax.set_title("Live Sensor Data")
ax.set_xlabel("Time (latest on right)")
ax.set_ylabel("Sensor Value")

# Animation function
def update(frame):
    if ser.in_waiting > 0:
        try:
            value = ser.readline().decode('utf-8').strip()
            if value:
                val_float = float(value)
                data.append(val_float)
                line.set_ydata(data)
                line.set_xdata(range(len(data)))
        except:
            pass
    return line,

# Start animation
ani = animation.FuncAnimation(fig, update, interval=100)
plt.show()

# Close serial on exit
ser.close()

# Close serial on exit
ser.close()
