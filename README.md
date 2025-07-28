# RescueRover – Embedded C++ Autonomous Rover (2025–Ongoing)

RescueRover is a real-world autonomous rover under development, designed to assist users stranded in signal-dead zones by scanning for connectivity and reporting GPS coordinates once signal is found.

This project is built in embedded C++ and will run on physical hardware using Arduino-compatible components.

---

## Project Goal

To autonomously explore areas without signal, detect the direction with the strongest connectivity (Wi-Fi or GSM), and transmit the user’s location once signal is acquired.

---

## Core Capabilities

### • Signal-Driven Exploration  
Rotates a directional antenna on a servo to detect signal strength in multiple directions and navigate toward the strongest one.

### • Real-Time Obstacle Avoidance  
Uses ultrasonic and TOF sensors to detect nearby objects and dynamically reroute in real time.

### • Path Logging and Return-to-Home  
Every move is recorded into a movement stack, enabling full autonomous reverse navigation to the starting point.

### • Apology Mechanism (Collision Response)  
If physical sensors detect an impact (e.g., joystick sensors), the rover reacts with a short sound or signal and adjusts direction accordingly.

---

## Current Modules Overview

- `MovementManager` - Coordinates signal scanning, directional movement, and obstacle negotiation.
- `MotorDriver` – Low-level control interface for the rover's motors (planned for integration with hardware).
- `RoverController` – High-level manager for exploration, stack-based return logic, and state control.
- `SimpleObstacleAvoidance` – Basic distance-based avoidance logic (pluggable module).
- `Utils` – Common utility functions.
- `ObstacleAvoidance` – Interface for custom obstacle handling strategies.

---

## Technologies

**Software:**  
- C++ (modular architecture)
- Git

**Hardware (Planned/Partially Integrated):**  
- ESP32 Board with Small DeepSeek AI LLM for Real Time Spoken Commands  
- GPS module  
- Ultrasonic & TOF distance sensors  
- GSM/Wi-Fi antenna on servo  
- Joystick bump sensors  
- LCD display

---

## Status

The rover is currently under active development.  
Core logic is being implemented in C++ and will be deployed to real hardware once complete.

> The project aim to develop into a fully physical autonomous rover project. Aimed at practical deployment using embedded C++.
