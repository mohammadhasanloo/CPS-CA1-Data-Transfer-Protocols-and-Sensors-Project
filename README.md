# Data Transfer Protocols and Sensors Project

## Project Overview

This project revolves around creating an Internet of Things (IoT) plant watering system using Arduino boards. The primary goal is to develop a system that can monitor soil conditions and water plants accordingly. The system comprises three key components:

- **Central Node**: This central control unit is responsible for processing data received from sensors, making irrigation decisions, and displaying information on an LCD screen.

- **Sensor Node**: Placed inside a plant pot, this node collects data about soil humidity and temperature. It is equipped with a humidity and temperature sensor (25SHT) and communicates with the central node via Bluetooth. Whenever the soil's humidity deviates by 5% from the last recorded value, this node sends updates to the central node.

- **Actuator Node**: This node is designed to control the water supply to the plants. It features an electric motor connected to a water valve (or a PWM-controlled stepper motor). The central node sends commands to the actuator node, regulating the water flow as needed.

## Project Goals

The main objectives of this project are as follows:

- Gain hands-on experience with Arduino development.
- Understand data transfer protocols, especially serial communication (UART).
- Familiarize yourself with various types of sensors.
- Create a functional IoT system for plant care.

## Implementation Details

### Sensor Node

The sensor node is placed within a plant pot and is equipped with a 25SHT sensor to measure soil humidity and temperature. It communicates with the central node via Bluetooth, sending sensor data whenever there is a significant change in soil conditions. The node also periodically observes the plant's status and sends updates to the central node.

### Actuator Node

The actuator node controls the water supply to the plants through an electric motor connected to a water valve (or a PWM-controlled stepper motor). It receives control commands from the central node via Bluetooth and adjusts the water flow accordingly.

### Central Node

The central node is the heart of the system. It receives data from the sensor node and processes it to make decisions about watering the plants. The central node displays relevant information, including temperature, humidity, and irrigation decisions, on an LCD screen. It communicates with both the sensor and actuator nodes via Bluetooth.

## Communication Protocols

The central node communicates with the sensor and actuator nodes using Bluetooth, which allows for wireless data transfer. This communication is similar to serial communication, but it eliminates the need for physical wires. The project aims to seamlessly send data between the Arduino boards using Bluetooth.

## Getting Started

Before beginning the project, it is essential to have a good understanding of the C2I and UART protocols, which are used for communication between the nodes.

For simulation and development, we use Proteus and PlatformIO. PlatformIO is a convenient platform that integrates with the VSCode editor.

To implement each node, create a separate folder for it within the PlatformIO project directory.

## Project Requirements

The central node makes irrigation decisions based on soil conditions. Here are the rules for irrigation:

- If soil humidity is above 30%, no irrigation is needed.
- If soil humidity is between 20% and 30%:
  - If the temperature is below 25°C, no irrigation is needed.
  - If the temperature is above 25°C, irrigation occurs at a rate of 10 ml per minute.
- If soil humidity is between 10% and 20%, irrigation occurs at a rate of 15 ml per minute.
- If soil humidity is below 10%, irrigation occurs at a rate of 20 ml per minute.

## Project Notes

- To ensure successful implementation, study the C2I and UART protocols in detail.
- Utilize the Proteus simulation environment and PlatformIO for development.
- Understand that Bluetooth communication effectively replaces wired serial communication.
- Establish virtual connections for Bluetooth modules in Proteus.
- Verify proper functionality by connecting virtual COM ports for communication between nodes.