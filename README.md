# SleepyWake

This project creates an educational day/night clock for children using an Arduino microcontroller,
designed to help kids learn about the passage of time without an audible alarm. Instead, it displays
a comforting nighttime image during sleep hours and transitions to a daytime image when it's time to
wake up. The clock uses a TFT screen for displaying images, with low brightness settings at night to
avoid disturbance.

## Features

* Displays day and night images based on pre-set time intervals.
* No sound alarm, only visual transitions, making it suitable for young children and sensitive sleepers.
* Real-time clock (RTC) integration for accurate timekeeping.
* Push-button controls for debug.

## Components required

* Arduino board (e.g., Arduino Uno, Nano)
* TFT display (compatible with Adafruit GFX library)
* RTC module (DS3231 or similar)
* Push buttons for time setting and control
* Dupont cables and resistors
* Optional: Breadboard for prototyping, or PCB for final assembly

## Getting Started

### 1. Clone the repository:

```bash
git clone https://github.com/LePtitDev/SleepyWake.git
```

### 2. Upload the code to your Arduino:

* Open the code in the Arduino IDE.
* Connect your Arduino to the computer.
* Select the correct board and port under "Tools."
* Click "Upload" to transfer the code to the Arduino.

### 3. Assemble the hardware.
### 4. Run and test the project.
