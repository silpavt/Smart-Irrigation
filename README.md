# Iot Based Smart-Irrigation-System-Using-ESP32

### TEAM NAME: ELECTROBOTS

### TEAM MEMBERS
- Member 1: SRAVYA SH- NSSCE,Palakkad 
- Member 2: SILPA VT - NSSCE,Palakkad
- Member 3: SHAHINA S - NSSCE,Palakkad

Hosted Project Link
[mention your project hosted project link here]

## Project Description
This project automates plant watering using an ESP32, a soil moisture sensor, a water level sensor, and a relay to control a pump. An OLED display is used to show real-time moisture and water level data.

## The Problem statement
Inefficient irrigation systems often lead to excessive water usage or inadequate watering, resulting in crop damage, resource wastage, and increased operational costs for farmers. 

## The Solution
This system automates watering based on soil moisture levels while ensuring the water tank has enough water. It displays real-time data on an OLED screen and can also be monitored via Blynk.

## Technical Details

### Technologies/Components Used

#### For Software:
- Languages: C++
- Frameworks: Arduino IDE
- Libraries Used:
  - Wire.h (for I2C communication)
  - U8g2lib.h (for OLED display)
  - BlynkSimpleEsp32.h (for remote monitoring)
- Tools:
  - Arduino IDE
  - Blynk IoT platform

#### For Hardware:
- ESP32 (Microcontroller)
- Soil Moisture Sensor (Analog Input)
- HW-038 Water Level Sensor (Analog Input)
- Relay Module (Controls Water Pump)
- Water Pump (Runs when soil is dry)
- OLED Display (SH1106) (Shows real-time data)
- Jumper Wires & Breadboard
- 12V Power Supply (for the pump)
