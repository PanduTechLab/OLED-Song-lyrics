# OLED-Song-lyrics

A lightweight, text-based lyric display project designed for the ESP32 microcontroller and a 128x64 SSD1306 OLED display. This project demonstrates I2C communication and dynamic text rendering without the need for complex graphical assets.

## Features
- **Smooth Text Rendering:** Automatic text centering and formatting.
- **Configurable:** Easily edit the `lyrics` array to display any text content.
- **Optimized:** Clean, efficient code structure for reliable performance on standard ESP32 boards.

## Hardware Requirements
- **Microcontroller:** ESP32 (DevKit V1 or similar)
- **Display:** 0.96" or 1.3" SSD1306 OLED Display (I2C)
- **Connecting Wires:** Jumper wires

## Wiring Diagram
Connect the OLED display to your ESP32 as follows:

| OLED Pin | ESP32 Pin |
| :--- | :--- |
| **GND** | GND |
| **VCC** | 3.3V |
| **SCL** | GPIO 22 |
| **SDA** | GPIO 21 |

## Software Requirements
You will need the following libraries installed in the Arduino IDE:
1. **Adafruit_SSD1306**
2. **Adafruit_GFX Library**

## Usage
1. Open the project in Arduino IDE.
2. Update the `lyrics` array in the code to your desired song or text.
3. Upload the code to your ESP32.
4. The device will automatically begin cycling through the text array.

## Configuration
You can adjust the display speed and text size by modifying the constants at the top of the sketch:
- `CHAR_DELAY`: Adjust speed of typing.
- `HOLD_DELAY`: Adjust how long the full text stays on screen.
- `TEXT_SIZE`: Change font scaling.

## Author
**Pandu's Tech Lab**
*Electronics & Embedded Systems Portfolio*# OLED-Song-lyrics
A smooth, text-only lyric scrolling project for ESP32 and SSD1306 OLED displays. This project uses the Adafruit GFX and SSD1306 libraries to center and display text dynamically, optimized for a clean, distraction-free visual experience.
