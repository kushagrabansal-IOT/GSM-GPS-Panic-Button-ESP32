# GSM + GPS Panic Button — ESP32 🚨📍

[![ESP32](https://img.shields.io/badge/Hardware-ESP32-blue)](https://www.espressif.com/)
[![GSM](https://img.shields.io/badge/Module-SIM800L-orange)](https://github.com/kushagrabansal-IOT/GSM-GPS-Panic-Button-ESP32)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow)](LICENSE)
[![Project: RAKSHA](https://img.shields.io/badge/Project-RAKSHA-red)](https://github.com/kushagrabansal-IOT)

> Emergency panic button using **ESP32 + SIM800L GSM + NEO-6M GPS**. On button press, instantly sends live Google Maps location via SMS and auto-calls your emergency contact. No internet required — works on cellular.

**RAKSHA Series** | Built by **Kushagra Bansal** @ [Project Lab India](https://github.com/kushagrabansal-IOT)

---

## ✨ Features

- 🚨 One-press emergency trigger
- 📍 Live GPS coordinates + Google Maps link via SMS
- 📞 Auto-call to emergency contact
- 🔔 Buzzer + LED alert
- 📵 100% offline — works on GSM, no WiFi needed
- ⚡ Sub-3-second alert delivery

---

## 🔧 Hardware Required

| Component | Qty | Connection |
|-----------|-----|------------|
| ESP32 DevKit V1 | 1 | — |
| SIM800L GSM Module | 1 | RX=GPIO16, TX=GPIO17 |
| NEO-6M GPS Module | 1 | RX=GPIO14, TX=GPIO27 |
| Push Button | 1 | GPIO12 (pull-up) |
| Buzzer (Active) | 1 | GPIO13 |
| SIM Card (any carrier) | 1 | Insert in SIM800L |
| LiPo Battery / 5V 2A | 1 | Power for SIM800L |

---

## ⚡ Commands

```bash
# Step 1 — Clone
git clone https://github.com/kushagrabansal-IOT/GSM-GPS-Panic-Button-ESP32.git
cd GSM-GPS-Panic-Button-ESP32

# Step 2 — Install Arduino Libraries
# Arduino IDE → Tools → Manage Libraries:
# ✅ TinyGSM
# ✅ TinyGPS++

# Step 3 — Configure
# Open main/main.ino
# Set CONTACT_1 and CONTACT_2 to your emergency numbers
# Set DEVICE_NAME to identify your device

# Step 4 — Upload
# Board: ESP32 Dev Module → Upload

# Step 5 — Test
# Open Serial Monitor (115200 baud)
# Wait for "RAKSHA Panic Button READY ✅"
# Press button → SMS + call triggered!
```

---

## 📊 Wiring Diagram

```
ESP32           SIM800L
5V    ────────  VCC (use 3.7V–4.2V LiPo recommended)
GND   ────────  GND
GPIO16────────  TX
GPIO17────────  RX

ESP32           NEO-6M GPS
3.3V  ────────  VCC
GND   ────────  GND
GPIO14────────  TX
GPIO27────────  RX

ESP32           Peripherals
GPIO12────────  Push Button ──── GND
GPIO13────────  Buzzer (+)  ──── GND
GPIO2 ────────  LED (built-in)
```

---

## 📦 Project Structure

```
GSM-GPS-Panic-Button-ESP32/
├── main/
│   └── main.ino          ← Upload this to ESP32
├── requirements.txt      ← Arduino library list
├── docs/
│   └── wiring.md
└── README.md
```

---

## 🏆 Part of RAKSHA Project

This is a core component of **RAKSHA** — an offline AI voice + hardware emergency system.
- 🥇 Winner — MNIT Jaipur Innovation Challenge
- 🏆 Winner — Poornima & SKIT competitions
- 🎪 Presented at Pragyan 2026, JECRC Open Innovation

---

## 👨‍💻 Author

**Kushagra Bansal** — Founder @ Project Lab India, Jaipur
🛒 [radiomarket.in](https://radiomarket.in) | 🔬 ESP32 • GSM • GPS • Safety Systems

---

⭐ Star this repo if it helped your project!
