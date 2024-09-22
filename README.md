# ZenseIOT

# Voice Recognition Based Home Automation with Power Saving Modes

This repository contains the code and documentation for a voice-controlled home automation system built using Arduino. The project demonstrates energy-efficient control of home appliances like a fan and light bulb, with features for voice command control and power-saving modes. The system is designed to reduce energy consumption by adjusting the brightness of lights based on ambient light conditions and detecting room occupancy through a PIR sensor.

## Features

- **Voice Control**:
  - Turn the fan and light on/off.
  - Control fan speed and bulb brightness through voice commands.
  
- **Energy-Saving Mode**:
  - The brightness of the light bulb dynamically adjusts based on ambient light conditions using an LDR sensor. If the external lighting is dim, the bulb will glow brighter to maintain optimal lighting.

- **Rest Mode**:
  - Lights automatically turn off when no motion is detected in the room (using the PIR sensor).
  - Lights turn on automatically when motion is detected in the room.

- **IoT Integration**:
  - Power consumption graphs are displayed via the Blynk IoT interface to visualize energy savings and usage.

## Components Used

- **Arduino Microcontroller**: Controls the sensors and processes voice commands.
- **PIR Sensor**: Detects motion to control the lights in rest mode.
- **LDR Sensor**: Measures ambient light conditions for adjusting the brightness of the bulb in power-saving mode.
- **Relay Module**: Used to control the fan and light.
- **Fan**: Simulates a home fan controlled via voice commands.
- **Light Bulb**: Simulates a light bulb controlled via voice commands and ambient light conditions.
- **Blynk IoT Interface**: Displays real-time power consumption graphs and savings.

## Modes of Operation

1. **Power Saving Mode**:
   - Adjusts the brightness of the light bulb based on ambient light levels. When the background light is dim, the bulb increases in brightness to ensure adequate lighting.
   
2. **Rest Mode**:
   - When no motion is detected in the room, the system turns off the lights automatically to save power. When motion is detected, the lights turn on.

## Objective

The primary objective of this project is to demonstrate the potential for energy savings by automating control over home appliances using voice commands and smart sensors. By utilizing the power-saving and rest modes, the system significantly reduces unnecessary power consumption.

## Power Consumption Monitoring

Using the Blynk IoT platform, power consumption graphs are displayed to provide a clear visualization of energy usage and savings, allowing for real-time monitoring and adjustments.

