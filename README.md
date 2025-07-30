# RB_hal_lib – HAL Library for Rugged Board A5D2x

This repository contains a collection of Hardware Abstraction Layer (HAL) libraries for the **Rugged Board A5D2x**. These libraries simplify access to hardware peripherals such as I2C, PWM, GPIO, UART, and more.

---

## 📁 Folder Structure

RB_hal_lib/
├── i2c/ # I2C library: src/, include/, Makefile
├── pwm/ # PWM library
├── uart/ # UART (if added)
├── gpio/ # GPIO (if added)
.
.
.


---

## 📦 Features

- ✅ Lightweight static libraries for bare-minimum Linux
- ✅ Supports `musl` toolchain with `arm-poky-linux-musleabi-gcc`
- ✅ Clean separation of header/source (`include/`, `src/`)
- ✅ Yocto-compatible and BSP-friendly

---

## 🔧 Build Instructions

Each peripheral folder contains:
- `src/` – `.c` implementation files
- `include/` – headers
- `Makefile` – builds `librb_<peripheral>.a`

### Example: Build I2C Library

```bash
cd i2c
make

build/librb_i2c.a

🚀  Compile an App with Library
$CC your_app.c -Iinclude -Lbuild -lrb_<module> -o output_binary


