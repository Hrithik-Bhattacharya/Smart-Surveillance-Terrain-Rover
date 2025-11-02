## 🛰️ Smart Surveillance Terrain Rover

A smart, Arduino-ESP32 powered terrain rover designed for surveillance in areas inaccessible to drones. It combines real-time sensor data, motor control, and wireless communication to navigate and monitor challenging environments.

---

### 📦 Features

- **Terrain Navigation**: Motor-controlled rover capable of traversing uneven surfaces.
- **Surveillance Camera**: Live video feed or image capture for remote monitoring.
- **Sensor Suite**: Real-time data from temperature, humidity, gas, and motion sensors.
- **Wireless Communication**: ESP32-based Wi-Fi or Bluetooth for remote control and data transmission.
- **Live Visualization**: Python-based dashboard for plotting sensor data in real time.
- **Modular Design**: Easily extendable hardware and software components.

---

### 🧠 System Architecture

```plaintext
[Arduino] ---> [Sensors] ---> [ESP32] ---> [Wi-Fi/Bluetooth] ---> [Python Dashboard]
     |              |               |               |                     |
     |              |               |               |                     |
 [Motor Driver]  [Camera]       [Data Logger]   [Remote Commands]   [Live Plotting]
```

---

### 🚀 Getting Started

#### 1. Clone the Repository

```bash
git clone https://github.com/Hrithik-Bhattacharya/Smart-Surveillance-Terrain-Rover.git
cd Smart-Surveillance-Terrain-Rover
```

#### 2. Hardware Setup

- Connect sensors to ESP32
- Connect motor driver to ESP32
- Connect ESP32 to laptop using USB
- Mount camera module (e.g., OV7670 or ESP32-CAM)

#### 3. Software Setup

- Flash Arduino with `main.py` or `motors/` control code
- Flash ESP32 with Wi-Fi/Bluetooth communication code
- Run `plot.py` for live visualization

```bash
python payloads/plot.py
```

---

### 🛠️ Folder Structure

```
Smart-Surveillance-Terrain-Rover/
├── camera/             # Camera integration and streaming
├── motors/             # Motor control logic
├── payloads/           # Sensor data visualization and logging
├── README.md           # Project overview
├── main.py             # Arduino control script
```

---

### 🧪 Live Sensor Visualization

Refactored `plot.py` supports real-time plotting of sensor data using `matplotlib` and `pyserial`. Easily extendable to support new sensors.

---


### Contributors

We welcome contributions of any kind to the enhancement of this project. Please make sure to create an issue and submit a pull request for the same.
