Got it 👍 I’ll draft you a **professional GitHub README** that explains everything clearly and makes recruiters impressed. You can copy-paste and tweak board/wiring images later if you want.

---

# STM32 HAL GPIO & UART Demo – Nucleo-L031K6

## 📌 Project Overview

This project demonstrates **basic GPIO and UART programming** on the **STM32 Nucleo-L031K6** board using the **STM32 HAL (Hardware Abstraction Layer)**.

It includes:

* **LED Blinking (GPIO Output):** Two LEDs blink alternately.
* **External Button (GPIO Input):** An additional LED toggles whenever an external push button is pressed.
* **UART Communication:** Simple UART messages are sent to a serial terminal (e.g., Putty, TeraTerm, or minicom) for debugging.

This project is beginner-friendly and shows how to interface **GPIO input/output** and **UART communication** using STM32 HAL drivers.

---

## 🛠 Hardware Requirements

* STM32 Nucleo-L031K6 board
* 3 LEDs (with current-limiting resistors \~220Ω)
* 1 Push button (normally open type)
* Breadboard + jumper wires
* USB cable (for programming + UART communication)

---

## ⚡ Circuit Connections

| Component | Pin Connection                       |
| --------- | ------------------------------------ |
| LED1      | PA5 (onboard LED on Nucleo board)    |
| LED2      | PB3 (external LED with resistor)     |
| Button    | PA0 → GND (internal pull-up enabled) |
| UART TX   | PA2 → USB ST-Link Virtual COM Port   |
| UART RX   | PA3 → USB ST-Link Virtual COM Port   |

📌 *Note: Button is connected between **PA0 and GND**. Internal pull-up is enabled via HAL.*

---

## 💻 Software Setup

1. Install **STM32CubeIDE** or **STM32CubeMX + preferred IDE**.
2. Create a new project for **Nucleo-L031K6**.
3. Enable peripherals in CubeMX:

   * **GPIO** for LEDs and Button
   * **USART2** (asynchronous, 115200 baud, 8N1, no flow control)
4. Generate code with HAL drivers.
5. Implement application logic inside `main.c`.

---

## 📂 Project Structure

```
STM32-HAL-GPIO-UART/
│── Core/
│   ├── Inc/       # Header files
│   ├── Src/       # main.c and source files
│── Drivers/       # HAL library drivers
│── README.md      # Project documentation
│── .project       # CubeIDE metadata
```

---

## 🚀 How It Works

1. **Alternate LEDs**:

   * LED1 (PA5) and LED2 (PB3) blink alternately every 500 ms.

2. **Button Toggle LED**:

   * External button on PA0 toggles LED2 whenever pressed.
   * Internal pull-up resistor prevents floating input.

3. **UART Messages**:

   * On startup: `"System Initialized"` is sent via UART.
   * On button press: `"Button Pressed – LED Toggled"` is sent.
   * On LED toggle: `"LED State Changed"` is sent.

---

## 🖥 Example UART Output

```
System Initialized
LED1 ON, LED2 OFF
LED1 OFF, LED2 ON
Button Pressed – LED Toggled
LED State Changed
```

---

## 🔮 Future Improvements

* Add **debouncing** for button input.
* Implement **interrupt-based button handling** instead of polling.
* Expand to **PWM LED fading** or **UART command-based LED control**.

---

## 📝 License

This project is licensed under the **MIT License** – free to use and modify.

---



