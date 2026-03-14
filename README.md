# rfid-cabinet-door
RFID Cabinet Door Lock (Arduino + Relay) — Smart Tool Cabinet Access Control

This repository contains an Arduino-based RFID cabinet door lock designed for industrial tool cabinets, lockers, and kiosk-controlled storage systems. The system reads RFID cards/tags, authorizes access, and triggers a relay output to unlock a cabinet door (solenoid lock / magnetic lock / electric strike).

It is built to be simple, stable, and 24/7 ready, and can be integrated into a Windows kiosk application via serial communication (for logging, auditing, and workflow control).

Features

✅ RFID authentication (scan card/tag to unlock)

✅ Relay-controlled door lock (configurable unlock time)

✅ Industrial-friendly: minimal logic, reliable loop, easy to maintain

✅ Serial-ready workflow for integration with a PC/kiosk app (optional)

✅ Easy to extend: admin cards, multi-door, event logs, sensors (door open/close)

Use Cases

Smart tool cabinet door access control

Industrial kiosk cabinet unlocking

RFID locker / storage cabinet security

Workshop inventory cabinet protection

How It Works

User scans an RFID tag/card near the reader

Arduino reads the UID and checks authorization

If authorized, Arduino activates the relay to unlock the cabinet door for a set duration

(Optional) Status can be printed to Serial for a connected PC app to log events

Hardware Requirements

Arduino (Uno / Mega / Nano supported)

RFID Reader (commonly MFRC522 or compatible)

Relay Module (1-channel or multi-channel)

Cabinet Lock (solenoid lock / magnetic lock / electric strike)

Proper power supply for your lock (recommended external PSU)

Wiring Notes (Important)

Door locks often require more current than Arduino can provide — use an external power supply.

If your relay module requires it, make sure Arduino GND is shared with relay power GND.

For noisy industrial environments, use stable power and consider shielded wiring.

Installation

Open the .ino sketch in Arduino IDE

Select Board and COM Port

Upload the sketch

Open Serial Monitor (optional) to confirm RFID reads and unlock actions

Configuration

Typical parameters you may want to adjust in the sketch:

Authorized RFID UIDs

Unlock duration (ms)

Relay output pin

Serial baud rate (if using serial logs/commands)

SEO Keywords (for Google)

RFID cabinet door lock, Arduino RFID access control, smart tool cabinet, industrial kiosk cabinet lock, RFID locker system, relay door lock Arduino, RFID door controller, MFRC522 cabinet lock, tool cabinet access control.

License

Add a license file (MIT is a common choice for Arduino projects).

Contributing

Pull requests are welcome. If you add support for door sensors (reed switch), multi-door relays, or a serial command protocol, please include documentation and wiring notes.

Extra: One-Line Tagline (Optional)

Simple Arduino RFID cabinet door unlock system with relay control for industrial smart cabinets and kiosk workflows.

Optional: Better Repo Title (If you want to rename)

rfid-cabinet-door-lock-arduino

smart-tool-cabinet-rfid-access-control

arduino-rfid-relay-door-lock
