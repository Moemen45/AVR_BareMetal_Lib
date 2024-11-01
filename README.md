# AVR Bare Metal Library

## Description
This repository contains a bare-metal library for AVR microcontrollers, utilizing 16-bit timers and UART communication. The library provides functionality for PWM generation and UART communication, making it suitable for a variety of embedded applications.

## Features
- **16-bit Timer (TIM1)**: Configured in counter mode with interrupt capabilities.
- **Fast PWM**: Supports 8-bit timers (TIM0 and TIM2) for PWM generation with the ability to select PWM pins via an API.
- **UART Communication**: Provides UART0 functionality for serial communication, allowing easy integration with other devices.

## Examples
The `examples` folder contains example implementations demonstrating the usage of the library. You can build and flash these examples onto your AVR microcontroller using the provided Makefile.

## Building the Project
To build the project, navigate to the root directory of the repository and run:

make : to clean build and flash
