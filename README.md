# TartVer – Weight-Based Automatic Mixing Scale System

**TartVer** is an open-source weight-based automatic mixing and dispensing system designed for custom scale projects. It utilizes load cells for precise weight measurement, servo motors for mechanical control, and a built-in web interface for configuration and control.

## 🚀 Features

- Dual **HX711** load cell support for accurate weight sensing
- Web-based interface using **HTML, CSS, and JavaScript**
- **ESP8266**-based control with Wi-Fi AP mode
- Servo motor control for dispensing/mixing operations
- Fully customizable and extendable hardware/software
- Lightweight and portable design, with optional 3D-printed components

## 🛠️ Hardware Requirements

- 1x ESP8266 (NodeMCU or similar)
- 2x HX711 load cell amplifiers
- 2x Load cells (e.g., 1kg or 5kg)
- 2x Servo motors (e.g., SG90 or MG90S)
- Wires, breadboard or custom PCB
- Optional: 3D-printed gate/pulley dispensing parts

## 🧱 Mechanical Design (3D Printing)

The mechanical components of TartVer were designed in **SolidWorks** and are included in the project repository. These files can be used to 3D-print parts such as:

- Gate-style dispensers (string-controlled flaps)
- Servo brackets and holders
- Mounting bases for load cells

You can modify these CAD files according to your dispenser size or container shape. STL export is supported for direct slicing.

## 💻 Software

Developed in Arduino C++, the firmware includes:

- `ESP8266WiFi.h` for networking  
- `ESP8266WebServer.h` for local web control  
- `HX711.h` for load cell reading  
- `Servo.h` for PWM control  
- Web interface embedded as string literals (`index.h` style)

### Web Interface Features:

- Live weight readings from load cells
- Manual or automatic servo activation
- Target weight input and start button
- Lightweight, responsive UI built from scratch

## 🔧 Setup & Usage

1. **Hardware Setup**  
   Connect load cells to HX711 modules and wire them to ESP8266. Connect servos to digital PWM pins (e.g., D5/D6). Power servos using external 5V supply if needed.

2. **Flashing Code**  
   Open the main `.ino` file in Arduino IDE (e.g., `tartver.ino`). Install required libraries and upload the code to your ESP8266.

3. **Access the Interface**  
   After powering up, ESP8266 creates a Wi-Fi access point (AP mode). Connect to the AP using your device and open the IP address shown in Serial Monitor (typically `192.168.4.1`).

4. **Calibrate & Test**  
   Use known weights to determine your `SCALE_FACTOR` values in the code. Adjust servo timings as needed.

> **Note:** This project assumes the user is familiar with Arduino development. It is intended for customization and educational purposes.

## 📂 File Structure

- `./electronic/electronic.ino` – Main firmware
- `./ui/index.html` – Web interface (HTML/CSS/JS)
- `./mechanic` – SolidWorks CAD files for 3D-printed parts

## 📄 License

This project is licensed under the **MIT License**.  
You are free to use, modify, and distribute it as you wish.

## 👤 Author

Developed by **Yusuf Eren Han**  
If you use this project, a mention or star is appreciated!

---

