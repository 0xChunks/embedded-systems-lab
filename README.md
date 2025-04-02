# 🛠️ Embedded Systems Lab – by 0xChunks

Welcome to my personal embedded systems lab—a hands-on collection of real-world projects designed to sharpen my skills across:

- 🧠 Low-level Linux kernel development
- 📟 Hardware/software interfacing
- 📡 Embedded RF + networking
- ⚡ GPIO, interrupts, UART, and device drivers
- 🔧 Soldering, breadboarding, and PCB design
- 🔌 Platforms: Raspberry Pi, ESP32, Arduino Mega, Arty S7, and more

This lab is fully aligned with my MS Computer Engineering focus in Tactical Networking & Embedded Systems and supports my internship preparation at Persistent Systems.

---

## 🧩 Project Structure

| Folder | Title                       | Description |
|--------|-----------------------------|-------------|
| `00_cli_gpio` | UART CLI GPIO Controller | User-space C-based UART command parser simulating firmware behavior |
| `01_gpio_kernel` | Kernel GPIO Output | First kernel module: LED control using `gpio_set_value()` during load/unload |
| `02_kernel_sysfs_device_class` | Sysfs GPIO Interface | Created `/sys/class/gpio_driver/...` entries to expose GPIO read/write to userspace |
| `03_kernel_char_device` | Character Device Interface | Registered `/dev/gpiodev` with custom `read()`/`write()` handlers to control GPIO |
| `notes/` | Notes and Reference Logs | Study notes, architecture breakdowns, and build plans for future phases |

---

## 🔭 Roadmap (Phase-Aligned with Degree Plan)

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
| `12` | End-to-End Tactical Stack | Unified RF-mesh → Pi → FPGA system test |

---

## 🛠️ Hardware Platforms

- **Raspberry Pi 2B** – main Linux kernel and controller platform
- **ESP32 (dev board + chip)** – for RF protocols (ESP-NOW, Wi-Fi, BLE)
- **Arduino Mega** – serial comms, IO expansion
- **Arty S7 FPGA** – Verilog design, SPI/UART bridge
- **MSP430FR2355** – (planned) ultra-low power node
- **Electronics + Makerspace** – full breadboarding, sensors, soldering, and PCB equipment

---

## 🎓 Degree & Career Alignment

This project directly supports my M.S. in Computer Engineering (Class of 2027) at NC State, focused on:

- Embedded Systems Architecture (ECE 560, 561)
- Linux Kernel and OS Design (ECE 565)
- Wireless Networking and RF Systems (ECE 570, 575, 524)
- ASIC/FPGA Design and Verification (ECE 720, 745, 748)

---

## 📚 Usage Instructions

1. **Clone the repo**:
   ```bash
   git clone https://github.com/0xChunks/embedded-systems-lab.git
   cd embedded-systems-lab
   ```

2. **Navigate to a project folder** and build the kernel module:
   ```bash
   cd 03_kernel_char_device
   make
   sudo insmod gpio_module.ko
   ```

3. **Interact with hardware**:
   ```bash
   echo 1 | sudo tee /dev/gpiodev     # Turn LED ON
   echo 0 | sudo tee /dev/gpiodev     # Turn LED OFF
   cat /dev/gpiodev                   # Read button state
   ```

4. **Remove the module when done**:
   ```bash
   sudo rmmod gpio_module
   ```

5. **Sysfs GPIO examples**:
   ```bash
   cat /sys/class/gpio_driver/gpio_device/button_state
   echo 1 > /sys/class/gpio_driver/gpio_device/led
   ```

---

## 🧠 Author

👋 Hi, I’m **Chris Clark** (a.k.a. [0xChunks](https://github.com/0xChunks))  
I’m a graduate student at NC State focused on embedded systems, RF, Linux, and digital hardware. This repo is my lab to prep for my 2025 internship and beyond.

---

## 📬 Contact

Reach out to connect or collaborate:

📫 [chrisclark62203@gmail.com](mailto:chrisclark62203@gmail.com)  
🔗 [linkedin.com/in/clclark](https://linkedin.com/in/clclark)

---

Thanks for checking out my lab—built for learning, optimized for real-world embedded engineering.
