# 🔐 RFID Cabinet Door Lock – Intelligentes RFID‑Türschloss für Werkzeugschränke

**Robuste Arduino‑basierte Zutrittskontrolle für industrielle Werkzeugschränke, Lagerboxen und Kiosk‑Systeme.**  
Entwickelt von **Amirmobasheraghdam** – einsatzbereit 24/7, einfach zu integrieren und wartungsfreundlich.

[![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D.svg)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Version](https://img.shields.io/badge/Version-2.0.0-blue.svg)]()

---

## 📋 Inhaltsverzeichnis
- [Überblick](#-überblick)
- [Features](#-features)
- [Anwendungsfälle](#-anwendungsfälle)
- [Hardware‑Anforderungen](#-hardware‑anforderungen)
- [Schaltplan / Verdrahtung](#-schaltplan--verdrahtung)
- [Installation](#-installation)
- [Konfiguration](#-konfiguration)
- [Serielle Kommunikation (Integration mit PC)](#-serielle-kommunikation-integration-mit-pc)
- [Fehlerbehebung](#-fehlerbehebung)
- [Lizenz](#-lizenz)
- [Autor & Kontakt](#-autor--kontakt)

---

## 🔍 Überblick

Dieses Projekt realisiert eine **RFID‑gesteuerte Türöffnung** für Werkzeugschränke, Schränke mit Elektroschlössern oder Kiosk‑Boxen.  
Ein Arduino liest die UID eines RFID‑Tags, vergleicht sie mit hinterlegten Schlüsseln und aktiviert bei Erfolg für kurze Zeit ein Relais. Dieses Relais schaltet dann ein **Türöffnermagneteschloss** oder einen **Elektroriegel** frei.

Die Firmware ist bewusst einfach und stabil gehalten – ideal für den Dauerbetrieb in der Werkstatt oder Industrie. Über die serielle Schnittstelle kann sie mit einer Windows‑Kiosk‑App kommunizieren, die Zugriffe protokolliert oder weitere Logik übernimmt.

---

## ✨ Features

- ✅ **RFID‑Authentifizierung** – Karte vorhalten, Tür öffnet sich.
- ✅ **Relais‑Ausgang** – Schaltet ein externes Schloss (Magnet, Türöffner, Riegel).
- ✅ **Zwei autorisierte Schlüssel** (im Code hinterlegte UIDs für Ehsan und Amir) – leicht erweiterbar.
- ✅ **Ping‑Funktion** – Regelmäßiges „Ich bin online“-Signal über serielle Schnittstelle (alle 3 Sekunden).
- ✅ **Unbekannte Karten werden ausgegeben** – Nützlich zum Einlernen neuer Karten.
- ✅ **Robuster Loop** – Keine Blockaden, sofort bereit für nächste Karte.
- ✅ **Kompatibel mit MFRC522** – dem am weitesten verbreiteten RFID‑Modul.
- ✅ **Einfach erweiterbar** – für mehrere Türen, Türkontakte (Reed‑Schalter) oder erweiterte Logik.

---

## 🏭 Anwendungsfälle

- **Werkzeugschrank** – Nur berechtigte Mitarbeiter erhalten Zugriff.
- **Industrieller Kiosk** – Schrank öffnet sich nach Kartenvorlage.
- **Lagerbox / Spind** – RFID‑basierte Schliessfachsteuerung.
- **Zutrittskontrolle für Technikräume** – mit Protokollierung über PC.
- **Inventarschrank in der Werkstatt** – Zugriff nur mit autorisiertem Chip.

---

## 🧰 Hardware‑Anforderungen

| Komponente | Empfehlung / Typ |
|------------|------------------|
| Mikrocontroller | Arduino Uno, Mega, Nano (oder kompatibel) |
| RFID‑Leser | MFRC522 (SPI‑Schnittstelle) |
| Relais‑Modul | 1‑Kanal (für 5V / 12V je nach Schloss) |
| Schloss | Elektrischer Türöffner, Magneteschloss (AC/DC je nach Typ) |
| Externes Netzteil | Für das Schloss (niemals über Arduino versorgen!) |
| Kabel | Jumperkabel, ggf. abgeschirmte Leitungen für störungsarme Umgebungen |

> ⚠️ **Wichtig:** Türschlösser benötigen oft 12V und mehrere Ampere. Verwende immer ein separates Netzteil für das Schloss und schalte es über das Relais. Arduino und Relais dürfen nur die gemeinsame Masse verbinden.

---

## 🔌 Schaltplan / Verdrahtung

### MFRC522 an Arduino

| MFRC522 | Arduino |
|---------|---------|
| SDA     | 10      |
| SCK     | 13      |
| MOSI    | 11      |
| MISO    | 12      |
| IRQ     | nicht verbunden |
| GND     | GND     |
| RST     | 5       |
| 3.3V    | 3.3V    |

### Relais an Arduino

| Relais‑Modul | Arduino |
|--------------|---------|
| IN / Signal  | A5      |
| VCC          | 5V (oder externe 5V, falls Modul viel Strom zieht) |
| GND          | GND (gemeinsam mit Arduino) |

### Schloss extern versorgen

- **Relais‑Kontakt (COM / NO)** in Reihe mit dem Schloss und dessen eigenem Netzteil schalten.
- Achte auf ausreichende Dimensionierung der Relais‑Kontakte (Spannung / Strom).

---

## 🛠 Installation

1. **Arduino IDE** herunterladen und installieren.
2. Benötigte Bibliotheken installieren:
   - `MFRC522` von GithubCommunity (über Bibliotheksverwalter)
   - `TimerOne` (ebenfalls über Bibliotheksverwalter)
3. Dieses Repository klonen oder die `.ino`-Datei herunterladen.
4. Sketch in der IDE öffnen.
5. **Autorisierte UIDs** anpassen (siehe Konfiguration).
6. Board und COM‑Port auswählen.
7. Sketch auf den Arduino hochladen.
8. Seriellen Monitor öffnen (9600 Baud) – dort erscheinen Meldungen und die Ping‑Nachrichten.

---

## ⚙ Konfiguration

Die wichtigsten Einstellungen findest du am Anfang der `.ino`-Datei:

```cpp
// ==================== Leser-Identifikation ====================
const String READER_ID       = "3";
const String MELDUNG_KARTE   = "Karte erkannt!:" + READER_ID;
const String MELDUNG_ONLINE  = "Ich bin online:" + READER_ID;

// ==================== Autorisierte Schlüssel-UIDs ====================
const byte UID_EHSAN[7] = {0x1D, 0x63, 0x25, 0xAE, 0x02, 0x10, 0x80};
const byte UID_AMIR[7]  = {0x1D, 0xF6, 0x31, 0xAE, 0x02, 0x10, 0x80};
```

- `READER_ID` kann geändert werden, wenn mehrere Leser im Einsatz sind.
- Die UIDs kannst du durch eigene Werte ersetzen. Um eine unbekannte Karte auszulesen, halte sie vor den Leser – die Serielle Ausgabe zeigt die UID im Hex‑Format.
- Die Relais‑Einschaltdauer (aktuell 100 ms) kann in den entsprechenden `delay(100)`-Zeilen angepasst werden.

---

## 💬 Serielle Kommunikation (Integration mit PC)

Der Arduino sendet folgende Nachrichten an den Seriell‑Port (9600 Baud):

- **„Karte erkannt!:3“** – immer, wenn eine Karte gelesen wurde (gefolgt vom Namen oder der neuen UID).
- **„Ich bin online:3“** – alle 3 Sekunden als Lebenszeichen.
- **„Ehsan“** oder **„Amir“** – wenn einer der autorisierten Schlüssel erkannt wurde.
- **„Neue ID: XX XX …“** – bei unbekannten Karten.

Eine angeschlossene PC‑Anwendung (z.B. in Python, C# oder als Kiosk‑App) kann diese Nachrichten auswerten, Zugriffe protokollieren, Alarme auslösen oder eine Whitelist verwalten.

---

## 🐞 Fehlerbehebung

| Problem | Mögliche Lösung |
|---------|-----------------|
| Keine Reaktion beim Kartenvorhalten | Prüfe Verkabelung des RFID‑Moduls, Spannungsversorgung (3.3V), korrekte Pins. |
| Relais schaltet nicht | Prüfe Relais‑Pin (A5), Logikpegel (HIGH = ein). Stelle sicher, dass die gemeinsame Masse verbunden ist. |
| Türöffner bekommt keinen Strom | Externes Netzteil prüfen, Relais‑Kontakte richtig angeschlossen? |
| Unbekannte Karte wird nicht ausgegeben | Seriellen Monitor geöffnet? Baudrate 9600? |
| Ping erscheint nicht | TimerOne‑Bibliothek installiert? Interruptkonflikt? |

---

## 📄 Lizenz

Dieses Projekt steht unter der **MIT‑Lizenz**.  
Du darfst es frei verwenden, anpassen und weitergeben – eine Quellenangabe wird geschätzt.

---

## 👤 Autor & Kontakt

- **Amirmobasheraghdam**  
- 🔗 [LinkedIn](https://www.linkedin.com/in/amirmobasher)  
- 🐙 [GitHub](https://github.com/amirmobasheraghdam)  
- 📧 bei Fragen gerne eine Issue öffnen oder direkt kontaktieren.

---

## 🏷️ Hashtags / Keywords

`#RFID` `#Arduino` `#Türschloss` `#Zutrittskontrolle` `#Werkzeugschrank` `#Industrie` `#SmartCabinet` `#MFRC522` `#Relais` `#Amirmobasheraghdam` `#OpenSource` `#MITLizenz` `#Elektroschloss` `#KioskSystem`

---

**Viel Erfolg mit deinem RFID‑Türschloss!**  
Bei Verbesserungsvorschlägen oder Fragen – ich freue mich auf dein Feedback.
```
