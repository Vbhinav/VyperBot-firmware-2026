# VyperBot

VyperBot is a WiFi-controlled differential drive robot built using the **ESP8266 (NodeMCU)**.  
It was designed as a **workshop project** to demonstrate practical robotics concepts including wireless control, sensor integration, and real-time scoring systems.

The project includes both the **final robot firmware** and **individual testing programs** used to verify each hardware subsystem before integration.

---

# System Overview

The robot connects to a WiFi network and receives joystick control commands using **UDP packets**.  
These packets contain X and Y joystick values which are converted into **differential motor speeds** to drive the robot.

An **LDR (Light Dependent Resistor)** acts as a gameplay sensor. When the sensor detects a light value above a threshold, the robot registers a score and sends it to a **leaderboard server via UDP**.

---

# Hardware Used

- ESP8266 NodeMCU
- TB6612FNG Motor Driver
- 2x DC Gear Motors
- LDR (Light Dependent Resistor)
- Voltage Divider Resistor
- Battery Pack (Li-ion / LiPo)
- Custom PCB

Optional testing components (used on breadboard during development):

- LED indicator
- Test mode switch

---

# Repository Structure

```
VyperBot/
│
├── final_code/
│   └── vyperbot_main.ino
│
├── testing_codes/
│   ├── joystick_udp_test.ino
│   ├── ldr_serial_test.ino
│   └── ldr_leaderboard_test.ino
│
├── docs/
│   └── workshop_manual.md
│
└── README.md
```

---

# Features

## WiFi Robot Control

The ESP8266 connects to a WiFi network and listens for UDP packets containing joystick coordinates.

Controller devices send packets to the robot, which interprets them and drives the motors accordingly.

---

## UDP Joystick Communication

Joystick data is sent in CSV format:

```
X,Y
```

Example:

```
120,200
```

The robot parses these values and calculates motor speeds.

---

## Differential Drive Motor Control

The robot uses **differential drive**, meaning the left and right motors run at different speeds to control steering.

Basic control logic:

```
speed = forward/backward motion
turn  = left/right steering

leftMotor  = speed - turn
rightMotor = speed + turn
```

This allows smooth movement and turning.

---

## LDR Gameplay Sensor

The LDR sensor connected to the **A0 analog pin** continuously reads light intensity.

When the LDR value crosses a defined threshold:

1. The robot stops.
2. A score is generated.
3. The score is sent to the leaderboard system using UDP.

---

# Testing Programs

Before running the final firmware, each subsystem can be tested individually.

---

## 1. UDP Joystick Test

Purpose:

Verify that the ESP8266 receives joystick packets correctly.

This test prints received UDP packets to the **Serial Monitor**.

File:

```
testing_codes/joystick_udp_test.ino
```

---

## 2. LDR Serial Test

Purpose:

Verify that the LDR sensor produces valid analog readings.

The program continuously prints LDR values to the **Serial Monitor**.

File:

```
testing_codes/ldr_serial_test.ino
```

---

## 3. LDR Leaderboard Test

Purpose:

Verify that LDR triggers correctly send score packets to the leaderboard server.

File:

```
testing_codes/ldr_leaderboard_test.ino
```

---

# Running the Project

## 1. Upload the Firmware

Upload the final robot firmware using the Arduino IDE.

File:

```
final_code/vyperbot_main.ino
```

Board Settings:

```
Board: NodeMCU 1.0 (ESP-12E Module)
Upload Speed: 115200
```

---

## 2. Connect to the Robot Network

Connect your controller device to the robot's WiFi network.

Example:

```
SSID: aragogBot
Password: 12345678
```

---

## 3. Send Control Packets

Send UDP packets to the robot:

```
IP Address: 192.168.4.1
Port: 1234
```

Packet format:

```
X,Y
```

Example:

```
128,128
```

---

# Serial Debugging

Open the **Arduino Serial Monitor** with:

```
Baud Rate: 115200
```

The robot prints:

- UDP packet data
- Parsed joystick values
- Motor control outputs
- LDR sensor readings
- Score events

---

# Workshop Learning Goals

This project demonstrates:

- ESP8266 WiFi networking
- UDP communication
- Differential drive robot control
- Sensor-based interaction
- Embedded systems debugging
- Hardware testing before system integration

---

# License

This project is intended for **educational and workshop use**.
