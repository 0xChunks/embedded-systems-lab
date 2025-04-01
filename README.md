# 🛠️ Embedded Systems Lab – by 0xChunks

Welcome to my personal embedded systems lab—a hands-on collection of real-world projects designed to sharpen my skills across:

- 🧠 Low-level Linux kernel development
- 📟 Hardware/software interfacing
- 📡 Embedded RF + networking
- ⚡ GPIO, interrupts, UART, and device drivers
- 🔧 Soldering, breadboarding, and PCB design
- 🔌 Platforms: Raspberry Pi, ESP32, Arduino Mega, Arty S7, and more

---

## 🧩 Project Structure

Each numbered folder contains a focused learning module:

| Folder | Title                       | Description |
|--------|-----------------------------|-------------|
| `00_cli_gpio` | UART CLI GPIO Controller | User-space C-based UART command parser simulating firmware behavior |
| `01_gpio_kernel` | Kernel GPIO Output | First kernel module: LED control using `gpio_set_value()` during load/unload |
| `02_kernel_sysfs_device_class` | Sysfs GPIO Interface | Created `/sys/class/gpio_driver/...` entries to expose GPIO read/write to userspace |
| `03_kernel_char_device` | Character Device Interface | Registered `/dev/gpiodev` with custom `read()`/`write()` handlers to control GPIO |
| `notes/` | Notes and Reference Logs | Study notes, architecture breakdowns, and build plans for future phases |

---

## 🚀 Why This Lab?

This lab is my personal journey into embedded systems, driver development, and cross-platform prototyping. I'm using this space to:

- Prepare for my upcoming embedded systems internship
- Get fluent in kernel modules, GPIO handling, and low-level programming
- Bridge the gap between electronics, C programming, and real hardware
- Build and document modular, scalable embedded systems the way I’d deploy them in the field

---

## ⚙️ Platforms & Hardware

- **Raspberry Pi 2B** – main kernel development and testing platform  
- **ESP32 (dev kit + bare chip)** – for RF (ESP-NOW, BLE, Wi-Fi) experiments  
- **Arduino Mega** – for GPIO expansion and UART communication  
- **Arty S7 FPGA** – planned for coprocessing, signaling, and offloaded logic  
- **MSP430FR2355** – planned for low-power sensor node  
- **Electronics + Makerspace** – full access to breadboards, resistors, capacitors, LEDs, relays, switches, PCBs, and soldering equipment

---

## 🧠 Learning Goals

- 🔧 Build an end-to-end embedded system with real hardware
- 🔌 Understand kernel modules, GPIO, sysfs, and `/dev` interfaces
- 🔄 Enable RF communication and device networking (ESP32 → Pi)
- 🧪 Test sensors, simulate peripherals, design PCBs
- 💻 Become internship-ready by tackling real driver and system-level code

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

5. **To test sysfs interfaces** (e.g., in `02_kernel_sysfs_device_class`):
   ```bash
   cat /sys/class/gpio_driver/gpio_device/button_state
   echo 1 > /sys/class/gpio_driver/gpio_device/led
   ```

---

## 🧠 Author

👋 Hi, I’m **Chris Clark** (a.k.a. [0xChunks](https://github.com/0xChunks))  
I’m a graduate student at NC State studying Computer Engineering with a focus on embedded systems, RF, and ad-hoc networking. This repo is my personal lab to explore everything I’ll need in the field—from device drivers to hardware debugging.

---

## 🗺️ Roadmap (Next Phases)

Here’s what’s coming next:

| Phase | Focus |
|-------|-------|
| 05 | **Interrupt-Driven GPIO** – Use `request_irq()` to respond to button presses |
| 06 | **UART Kernel Device** – Send/receive messages from Arduino or ESP32 in kernel space |
| 07 | **RF Communication** – ESP-NOW, Wi-Fi, and BLE messaging using ESP32 chips |
| 08 | **PCB + Soldered Interface** – Custom-designed breakout board w/ Pi or ESP |
| 09 | **FPGA Integration (Arty S7)** – Signal processing, coprocessing, or GPIO coordination |
| 10 | **Full Embedded Integration** – Connect Pi ↔ ESP32 ↔ FPGA in a unified system |

---

## 📬 Contact

Open to collaboration, questions, or fellow embedded nerds reaching out:  
📫 [chrisclark62203@gmail.com](mailto:chrisclark62203@gmail.com)  
🔗 [linkedin.com/in/clclark](https://linkedin.com/in/clclark)

---

Thanks for checking out my lab—feel free to fork it, learn from it, or build something cooler than me. I'm here to keep growing.
