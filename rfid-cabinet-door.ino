/**
 * ----------------------------------------------------------------------------
 * RFID Türsteuerung – Zutrittssystem mit zwei autorisierten Schlüsseln
 * ----------------------------------------------------------------------------
 * Autor:        Amirmobasheraghdam
 * Version:      2.0.0
 * Datum:        2026-03-17
 * Beschreibung:
 *   Dieses Programm steuert ein RFID-basiertes Türschloss.
 *   Es erkennt zwei fest hinterlegte Schlüssel (Ehsan, Amir) und öffnet
 *   für 100 ms ein Relais (Türöffner). Unbekannte Karten werden über
 *   die serielle Schnittstelle ausgegeben.
 *   Ein regelmässiger Ping (alle 3 s) signalisiert "Ich bin online:3"
 *   an den angeschlossenen Rechner.
 * 
 * Hardware:
 *   - Arduino (z.B. Uno)
 *   - RFID-Modul MFRC522 (SS=10, RST=5)
 *   - Relais an A5 (schliesst bei HIGH)
 * 
 * Benötigte Bibliotheken:
 *   - SPI
 *   - MFRC522 by GithubCommunity
 *   - TimerOne
 * ----------------------------------------------------------------------------
 */

#include <SPI.h>
#include <MFRC522.h>
#include <TimerOne.h>

// ==================== PIN-Konfiguration ====================
#define SS_PIN      10      // SDA (Slave Select) für MFRC522
#define RST_PIN     5       // Reset für MFRC522
#define RELAY_PIN   A5      // Relais-Ausgang (HIGH = Tür öffnen)

// ==================== Leser-Identifikation ====================
const String READER_ID       = "3";                 // Eindeutige Leser‑ID
const String MELDUNG_KARTE   = "Karte erkannt!:" + READER_ID;   // "Card inserted!:3"
const String MELDUNG_ONLINE  = "Ich bin online:" + READER_ID;    // "I'm online:3"

// ==================== Autorisierte Schlüssel-UIDs ====================
// UID für Ehsan (7 Byte)
const byte UID_EHSAN[7] = {0x1D, 0x63, 0x25, 0xAE, 0x02, 0x10, 0x80};
// UID für Amir (7 Byte)
const byte UID_AMIR[7]  = {0x1D, 0xF6, 0x31, 0xAE, 0x02, 0x10, 0x80};

// ==================== Globale Objekte ====================
MFRC522 rfid(SS_PIN, RST_PIN);   // RFID-Leser

// ==================== Hilfsfunktionen ====================

/**
 * Vergleicht zwei UID‑Arrays miteinander.
 * 
 * @param uid1  Erstes Array (z.B. gelesene UID)
 * @param uid2  Zweites Array (hinterlegte UID)
 * @param len   Länge der Arrays (bei MFRC522 meist 4, 7 oder 10)
 * @return true wenn beide Arrays byte‑gleich sind, sonst false
 */
bool uidIstGleich(byte *uid1, byte *uid2, byte len) {
  for (byte i = 0; i < len; i++) {
    if (uid1[i] != uid2[i]) return false;
  }
  return true;
}

/**
 * Gibt die gelesene UID im hexadezimalen Format auf der seriellen Schnittstelle aus.
 */
void zeigeUID(byte *uid, byte len) {
  Serial.print("Neue ID:");
  for (byte i = 0; i < len; i++) {
    // Führende Null bei Werten < 0x10
    if (uid[i] < 0x10) Serial.print(" 0");
    else Serial.print(" ");
    Serial.print(uid[i], HEX);
  }
  Serial.println();
}

// ==================== Timer-Interrupt (Ping) ====================
void sendePing() {
  Serial.println(MELDUNG_ONLINE);
}

// ==================== Setup ====================
void setup() {
  Serial.begin(9600);               // Serielle Kommunikation starten
  SPI.begin();                      // SPI‑Bus initialisieren
  rfid.PCD_Init();                   // RFID‑Modul initialisieren

  pinMode(RELAY_PIN, OUTPUT);       // Relais‑Pin als Ausgang
  digitalWrite(RELAY_PIN, LOW);      // Tür verriegelt (Relais inaktiv)

  // Timer1 alle 3 Sekunden auslösen (3000000 µs)
  Timer1.initialize(3000000);
  Timer1.attachInterrupt(sendePing); // Bei jedem Interrupt "sendePing" aufrufen

  Serial.println("RFID-Türsteuerung gestartet – bereit.");
}

// ==================== Hauptschleife ====================
void loop() {
  // Prüfen, ob eine neue Karte vor dem Leser liegt
  if ( ! rfid.PICC_IsNewCardPresent() ) {
    return;   // keine neue Karte → Schleife neu starten
  }

  // Versuchen, die UID der Karte zu lesen
  if ( ! rfid.PICC_ReadCardSerial() ) {
    return;   // Lesen fehlgeschlagen → neu versuchen
  }

  // Karte wurde erfolgreich gelesen
  Serial.println(MELDUNG_KARTE);

  // Typ der Karte auslesen (nur für Debug‑Zwecke, hier nicht weiter verwendet)
  MFRC522::PICC_Type kartentyp = rfid.PICC_GetType(rfid.uid.sak);

  // UID des gelesenen Tags
  byte *geleseneUID = rfid.uid.uidByte;
  byte uidLaenge    = rfid.uid.size;

  // Prüfen, ob es sich um einen autorisierten Schlüssel handelt
  if ( uidIstGleich(geleseneUID, (byte*)UID_EHSAN, uidLaenge) ) {
    Serial.println("Ehsan");                 // Name ausgeben
    digitalWrite(RELAY_PIN, HIGH);            // Tür öffnen (Relais an)
    delay(100);                               // 100 ms Impuls
    digitalWrite(RELAY_PIN, LOW);             // Tür wieder verriegeln
  }
  else if ( uidIstGleich(geleseneUID, (byte*)UID_AMIR, uidLaenge) ) {
    Serial.println("Amir");
    digitalWrite(RELAY_PIN, HIGH);
    delay(100);
    digitalWrite(RELAY_PIN, LOW);
  }
  else {
    // Unbekannte Karte – UID zur Identifikation ausgeben
    zeigeUID(geleseneUID, uidLaenge);
  }

  // Karte anhalten und Kryptografie stoppen (für nächsten Lesevorgang)
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
