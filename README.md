# 🚗 Basic Line Following Robot using 5 IR Sensor Array  

This project is a **basic Line Following Robot (LFR)** built using Arduino and a 5-channel IR sensor array. This is a very basic version, no PID or no edge cases like T junctions and more.

## Video 
- Video link : https://youtu.be/rwxvpG9fNpQ


## 🛠️ Components Used  

- Arduino Uno (or similar board)  
- L298N Motor Driver Module  
- 5-Channel Line Following IR Sensor Array  
- HC-06 Bluetooth Module *(for debugging)*  
- Car chassis with 2 DC motors (mechanical base)  
- 2 × 18650 3.7V batteries  
- Mini breadboard  
- Jumper wires  
- Power switch  

---

## ⚡ Features  

- Accurate line tracking with **5 IR sensors**  
- Array-based decision logic for movement control  
- PWM-based motor speed adjustment  
- Optional Bluetooth module for debugging and serial monitoring  
- Beginner-friendly and expandable for advanced control (PID, obstacle avoidance, etc.)  

---

## 🔌 Connections  

- **IR Sensor Array** → Arduino pins `3, 4, 5, 6, 7`  
- **Motor 1** → L298N → Arduino pins `8, 9` (direction), `10` (enable/PWM)  
- **Motor 2** → L298N → Arduino pins `12, 13` (direction), `11` (enable/PWM)  
- **Power**:  
  - Arduino `Vin` → L298N `5V`  
  - Arduino `GND` → L298N `GND`  
  - Battery pack `+` and `–` → L298N `Vin` and `GND` *(common ground with Arduino)*  
- **IR Sensor Power** → Arduino `3.3V` and `GND`  
- **Bluetooth Module**:  
  - `VCC` → Arduino `5V`  
  - `GND` → Arduino `GND`  
  - `TX` → Arduino `RX (0)`  
  - `RX` → Arduino `TX (1)`  

---

## 📝 Code Overview  

- Reads digital values from 5 IR sensors  
- Uses a simple array-based algorithm to detect line position  
- Controls motor direction and speed accordingly  
- Optional Bluetooth serial output for debugging sensor readings  

---
