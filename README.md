# REVERSE-PARKING-ASSISTANCE-USING-CAN
**Reverse car Parking Assistance Using CAN**
This project implements a reverse parking assistance system using the HC-SR04 ultrasonic sensor module and the CAN (Controller Area Network) protocol on an ARM-7-based LPC2129 microcontroller board.

Objective: To create a system that detects obstacles while reversing a vehicle and provides visual and audio feedback.

Components:
HC-SR04 Ultrasonic Sensor: Measures distance to obstacles.
LPC2129 Microcontroller: Handles data processing and CAN communication.
CAN Protocol: Facilitates communication between two LPC2129 nodes.
Buzzer and LEDs: Provide feedback based on proximity.

System Design
NODE A ECU: Connected to the vehicle's reverse gear switch, this node activates the reverse mode and controls the buzzer and LEDs.
NODE B ECU: Connected to the HC-SR04 sensor, this node measures the distance to obstacles and sends the data to the NODE A via CAN.
Common Files: Includes headers such as UART0 and CAN drivers.

Simulation and Development
Development Environment: Keil uVision Version 5.0.
Simulation: The system's CAN message transmission and reception were simulated using custom debug scripts.
Hardware Setup
Development Board: ARM-7-based LPC2129 by Rhydolabz.
CAN Peripheral: CAN2 is used for communication between the nodes.
