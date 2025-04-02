# Embedded Systems Lab – by 0xChunks

Welcome to my personal embedded systems lab—a focused, practical environment for learning and applying embedded software, Linux kernel development, RF systems, digital hardware design, and hardware/software co-integration. This repository serves as a cornerstone for my professional development in embedded systems, aligned with both my graduate studies and internship goals.

---

## Graduate Focus – MS in Computer Engineering @ NC State

This project aligns with my MS in Computer Engineering with a concentration in Tactical Networking and Embedded Systems. My studies include embedded architecture, Linux operating systems, wireless networks, RF system design, digital hardware, and ASIC/FPGA verification.

These projects help reinforce and apply concepts in:
- Embedded firmware and real-time control
- Linux kernel module development
- Mesh networking and wireless communication
- FPGA design and system integration
- Hardware/software co-design and performance optimization

---

## Internship Preparation

This lab is designed to build practical experience in:
- Linux-based system development and kernel module interaction
- Interfacing with GPIO, interrupts, and UART peripherals
- Schematic-level hardware debugging and digital signal interfacing
- Embedded communication protocols including UART and RF (ESP-NOW)
- Integrating microcontrollers, FPGAs, and wireless devices into cohesive systems
- Soldering, PCB prototyping, and interfacing electronics with computing platforms

By completing this lab, I aim to contribute meaningfully to real-world embedded and communication systems, while continuing to develop into a versatile and dependable embedded systems engineer.

---

## Project Structure

| Folder | Title                       | Description |
|--------|-----------------------------|-------------|
| `00_cli_gpio` | UART CLI GPIO Controller | User-space C-based UART command parser simulating firmware behavior |
| `01_gpio_kernel` | Kernel GPIO Output | First kernel module: LED control using `gpio_set_value()` during load/unload |
| `02_kernel_sysfs_device_class` | Sysfs GPIO Interface | Created `/sys/class/gpio_driver/...` entries to expose GPIO read/write to userspace |
| `03_kernel_char_device` | Character Device Interface | Registered `/dev/gpiodev` with custom `read()`/`write()` handlers to control GPIO |
| `notes/` | Notes and Reference Logs | Study notes, architecture breakdowns, and build plans for future phases |

---

## Roadmap (Aligned with Career & Academic Goals)

| Phase | Title | Description |
|-------|-------|-------------|
| `04` | IRQ-Driven Button Handler | Interrupt handler on GPIO for real-time input |
| `05` | Kernel UART Messaging | Bidirectional UART messaging with Arduino/ESP32 |
| `06` | RF Messaging (ESP-NOW) | Wireless comms via ESP32 RF modules |
| `07` | Embedded Control Node | ESP32 node: RF, UART, GPIO control |
| `08` | Custom PCB Sensor Node | Design + soldered sensor system for data collection |
| `09` | Arty S7 GPIO Peripheral | Simple GPIO peripheral in Verilog/Vivado |
| `10` | FPGA Co-Processor | Interface Pi ↔ FPGA via SPI or UART |
| `11` | Mesh Network Simulation | Multi-node ESP/Pi RF network routing |
| `12` | End-to-End Embedded System | Unified RF-mesh → Pi → FPGA system test |

---

## Hardware Platforms

- **Raspberry Pi 2B** – Linux kernel and controller platform
- **ESP32 (dev board + chip)** – RF protocols (ESP-NOW, Wi-Fi, BLE)
- **Arduino Mega** – Serial communication, IO expansion
- **Arty S7 FPGA** – Verilog logic design and integration
- **MSP430FR2355** – (planned) ultra-low power embedded node
- **Electronics + Makerspace** – Breadboarding, sensors, soldering, PCB prototyping

---

## Usage Instructions

1. **Clone the repo**:
   ```bash
   git clone https://github.com/0xChunks/embedded-systems-lab.git
   cd embedded-systems-lab
   ```

2. **Navigate to a project folder and build**:
   ```bash
   cd 03_kernel_char_device
   make
   sudo insmod gpio_module.ko
   ```

3. **Interact with hardware**:
   ```bash
   echo 1 | sudo tee /dev/gpiodev
   echo 0 | sudo tee /dev/gpiodev
   cat /dev/gpiodev
   ```

4. **Sysfs GPIO examples**:
   ```bash
   cat /sys/class/gpio_driver/gpio_device/button_state
   echo 1 > /sys/class/gpio_driver/gpio_device/led
   ```

5. **Unload when done**:
   ```bash
   sudo rmmod gpio_module
   ```

---

## Author

**Chris Clark** ([0xChunks](https://github.com/0xChunks))  
MS Computer Engineering student at NC State  
Focused on embedded systems, wireless communication, kernel development, and digital hardware.

📫 [chrisclark62203@gmail.com](mailto:chrisclark62203@gmail.com)  
🔗 [linkedin.com/in/clclark](https://linkedin.com/in/clclark)

---

Thanks for reading. This project is a living space for experimentation and growth in embedded system design and development.
