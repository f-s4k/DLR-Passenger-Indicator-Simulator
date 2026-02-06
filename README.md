# DLR Passenger Indicator Simulator

An Arduino-based simulation of the **Docklands Light Railway (DLR) passenger information display** using a 16x2 I2C LCD.

This project mimics real DLR onboard announcements, including:
- Scrolling destination messages
- "Next stop" announcements
- Terminus behaviour with direction reversal
- Realistic dwell times at stations and terminius

---

## 🛠 Wokwi Simulator tools used
- Arduino (Uno / Nano / compatible)
- 16x2 I2C LCD (address `0x27`)
- Jumper wires
- Breadboard (optional)

---

## 📜 Features
- Finite State Machine (FSM) for display control
- Forward and reverse route logic
- Terminus hold and automatic direction change
- Smooth scrolling text
- Accurate DLR station sequence (Tower Gateway ↔ Beckton)

---

## 🚆 Route Simulated
Tower Gateway → Beckton  and vice versa

---

## ⏱ Timing Behaviour
| Event | Duration |
|------|---------|
| Scrolling delay | 200 ms |
| Station dwell | 3 seconds |
| Terminus dwell | 10 seconds |

(All timings configurable in code)

---

## 📂 Code Structure
- `SCROLL` – Scrolls announcement message
- `STATION` – Holds station name on arrival
- `TERMINUS_HOLD` – Extended dwell + direction reversal

---

## 🔌 Libraries Required
- `Wire.h`
- `LiquidCrystal_I2C.h`

Install via **Arduino Library Manager**.

---

## ▶️ How to Run
1. Open the `.ino` file in Arduino IDE
2. Connect the LCD via I2C
3. Upload to Arduino
4. Power the board and watch the simulation run

---

## ✨ Inspiration
Inspired by real DLR onboard passenger information systems.

