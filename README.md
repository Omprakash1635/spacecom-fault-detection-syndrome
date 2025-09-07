# SpaceCom Fault Detection using Syndrome

[![License: CC BY 4.0](https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)

This repository contains the Arduino code and documentation for the project 
**“SpaceCom Fault Detection using Syndrome”**, published in **IJERT**.

📄 Paper link: [View on IJERT](https://www.ijert.org/an-overview-on-syndrome-based-fault-detection-and-error-mapping-systems)  
👥 Authors: Madhan N,V Om Prakash.
📅 Year: 2024  

spacecom-fault-detection-syndrome/
├─ README.md 
├─ LICENSE 
├─ arduino/
│ └─ fault_detection.ino 



---

## Arduino Code

The main code is in [`arduino/fault_detection.ino`](arduino/fault_detection.ino).  
It performs **syndrome-based fault detection** using 4 push buttons, calculates parity checks, and provides feedback using:  

- **OLED display (SSD1306, I2C)** → displays syndrome, latitude, and longitude.  
- **DFPlayer Mini MP3 module** → plays corresponding audio messages.  
- **Serial Monitor** → logs all outputs.  

---

## Hardware Setup

- Arduino Board (e.g., Uno, Nano, or Mega)  
- 4 Push Buttons  
- 0.96" or 1.3" OLED Display (SSD1306, I2C, address `0x3C`)  
- DFPlayer Mini MP3 Module + MicroSD card with audio files (`0001.mp3`, `0002.mp3`, etc.)  
- Speaker connected to DFPlayer Mini  

### Pin Connections

#### Buttons
- Button D1 → Pin 2  
- Button D2 → Pin 3  
- Button D3 → Pin 4  
- Button D4 → Pin 5  

#### OLED (I2C)
- **SDA** → A4 (on Arduino Uno)  
- **SCL** → A5 (on Arduino Uno)  

#### DFPlayer Mini
- **DFPlayer TX → Arduino Pin 10 (RX)**  
- **DFPlayer RX → Arduino Pin 11 (TX)**  
- **VCC → 5V, GND → GND**  

---

## Required Libraries

Install the following libraries via **Arduino IDE Library Manager**:

- [Wire](https://www.arduino.cc/en/Reference/Wire) *(built-in)*  
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)  
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)  
- [DFRobotDFPlayerMini](https://github.com/DFRobot/DFRobotDFPlayerMini)  

### Installing Libraries
1. Open Arduino IDE  
2. Go to **Sketch → Include Library → Manage Libraries**  
3. Search and install: **Adafruit GFX**, **Adafruit SSD1306**, **DFRobotDFPlayerMini**  

---

## How to Upload the Code

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).  
2. Clone or download this repository.  
3. Open `arduino/fault_detection.ino` in Arduino IDE.  
4. Select your Arduino **Board** and **Port** under *Tools*.  
5. Install the required libraries (see above).  
6. Insert a microSD card into DFPlayer Mini with audio files (`0001.mp3`, `0002.mp3`, etc.).  
7. Click **Upload** to flash the code.  
8. Open **Serial Monitor** (set baud rate to `9600`) to view logs.  

---
