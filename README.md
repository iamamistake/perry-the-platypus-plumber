# Perry The Platypus Plumber

## Overview

This project enables bidirectional data communication between an ATmega328P microcontroller (MCU) and a PC via a UART bus. It adopts an event-driven architecture to manage asynchronous events and tasks effectively. The project encompasses various drivers, components and additional functionalities, all developed from scratch, starting from the register level up to the application layer. Well, as far as the project name goes, it's in reference to the playful string data being sent, inspired by the famous undercover agent ツ.

## Hardware Setup

As mentioned before, the entire thing is implemented on an AVR microcontroller ATmega328P featuring 32KB of FLASH and 2KB of RAM and its clock is sourced from an on-board external 16MHz crystal oscillator. Due to the non-availability of any hardware having an externally interfaced EEPROM as well as a USB/Serial converter to communicate with the PC, I settled down for the Arduino Nano board since it has an onboard USB/Serial converter chip as well as an internal EEPROM memory so yeah, that's a big win.

## Drivers

1. **UART Driver**: Implements UART functionality for communication with the PC. Currently, the baud rate is configured to 2400 along with 1 start bit, 8 data bits, 0 parity bits and 1 stop bit format. The driver has been implemented with a non-blocking interrupt-based approach.
   
2. **Internal EEPROM Driver**: Implements functionality for reading from and writing to the internal EEPROM of the ATmega328P microcontroller.

3. **Watchdog Timer Driver**: Implements the watchdog timer functionality, featuring initialization as well as monitoring of the entire system.

## Components

1. **Scheduler**: Implements a task scheduler for managing as well as scheduling asynchronous events and tasks within the system. It has been developed as a prerequisite for implementing a fully event-driven system that ensures timely sequential processing of critical tasks and interrupts while minimizing overhead.

## Application

It implements the user application initialization and a state machine to facilitate communication with the PC; caching the incoming data from the PC into an EEPROM and then sending it back upon completion of the reception phase.

## PC Transceiver

It implements the Python scripts/applications which are supposed to be run on the PC to simulate this project's use case. One of the scripts simulates the system while also computing the average speed during the entire reception and transmission phase. The second script simulates the system while computing real-time speeds during the reception and transmission phases. You'll need to tune the real-time processing window duration depending on how accurate you want the real-time speeds to be while also paying attention to the number of real-time speed update iterations.

## Additional Notes

1. **Loopback Packet Size**: The loopback packet size, which is the amount of data that has to be received by the MCU before it starts sending it back to the PC, can be changed in the user application header.

2. **EEPROM Simulation**: Well, I've kept an option to simulate an EEPROM in the system RAM memory which can be enabled in the user application header. Initially, I did it just for debugging to make sure everything's working fine before I bring the internal EEPROM memory into the scene. But then I was like, why not just make it sound fancy as if I've built something cool while also keeping it in the code maybe for debugging purposes? Well anyway, just make sure that you're not exceeding the RAM usage when you enable this option.

3. **System Clock**: The system clock can be changed by just updating the desired clock setting in the system configuration header.

4. **Scheduler**: The scheduler is dependent on the maximum queue size as well as the maximum data buffer size; both of which can be changed in the scheduler header. They should be updated based on the maximum amount of data generated for processing during a particular event in the system, as well as on how busy and CPU intensive the application is.