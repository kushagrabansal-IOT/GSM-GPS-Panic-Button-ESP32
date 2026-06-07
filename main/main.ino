/*
 * GSM + GPS Panic Button — ESP32
 * Author  : Kushagra Bansal — Project Lab India
 * Project : RAKSHA / SURAKSHA Series
 * GitHub  : github.com/kushagrabansal-IOT/GSM-GPS-Panic-Button-ESP32
 *
 * When panic button is pressed:
 *   1. Reads GPS coordinates (latitude, longitude)
 *   2. Sends emergency SMS with live Google Maps link
 *   3. Makes auto-call to emergency contact
 *   4. Triggers buzzer alert
 *
 * Commands:
 *   git clone https://github.com/kushagrabansal-IOT/GSM-GPS-Panic-Button-ESP32.git
 *   # Open main/main.ino in Arduino IDE
 *   # Install: TinyGSM, TinyGPS++
 *   # Set emergency contacts below → Upload → Done
 */

#include <TinyGsmClient.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// ── PIN CONFIG ────────────────────────────────────────────
#define PANIC_BUTTON_PIN  12    // GPIO12 → Panic button (pull-up)
#define BUZZER_PIN        13    // GPIO13 → Buzzer
#define LED_PIN           2     // GPIO2  → Status LED (built-in)

// GSM (SIM800L) — Hardware Serial 1
#define GSM_RX   16
#define GSM_TX   17
#define GSM_BAUD 9600

// GPS (NEO-6M) — Hardware Serial 2
#define GPS_RX   14
#define GPS_TX   27
#define GPS_BAUD 9600

// ── EMERGENCY CONTACTS ───────────────────────────────────
const char* CONTACT_1 = "+91XXXXXXXXXX";   // Primary emergency contact
const char* CONTACT_2 = "+91XXXXXXXXXX";   // Secondary contact (optional)
const char* DEVICE_NAME = "RAKSHA Device"; // Your device name

// ── OBJECTS ──────────────────────────────────────────────
HardwareSerial gsmSerial(1);
HardwareSerial gpsSerial(2);
TinyGsm modem(gsmSerial);
TinyGPSPlus gps;

float latitude  = 0.0;
float longitude = 0.0;
bool  panicActive = false;
unsigned long lastGPSRead = 0;

// ── SETUP ─────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  pinMode(PANIC_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Init GSM
  gsmSerial.begin(GSM_BAUD, SERIAL_8N1, GSM_RX, GSM_TX);
  Serial.println("Initializing GSM...");
  modem.restart();
  Serial.println("GSM OK | SIM: " + modem.getSimCCID());

  // Init GPS
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX, GPS_TX);
  Serial.println("GPS initialized. Waiting for fix...");

  blinkLED(3, 200);  // Ready signal
  Serial.println("RAKSHA Panic Button READY ✅");
}

// ── LOOP ──────────────────────────────────────────────────
void loop() {
  // Continuously read GPS
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    latitude  = gps.location.lat();
    longitude = gps.location.lng();
  }

  // Check panic button (LOW = pressed, pull-up)
  if (digitalRead(PANIC_BUTTON_PIN) == LOW && !panicActive) {
    panicActive = true;
    Serial.println("🚨 PANIC BUTTON PRESSED!");
    triggerPanic();
    delay(5000);   // Debounce / cooldown
    panicActive = false;
  }

  delay(100);
}

// ── PANIC TRIGGER ─────────────────────────────────────────
void triggerPanic() {
  // 1. Buzzer alarm
  tone(BUZZER_PIN, 1000, 3000);
  blinkLED(5, 100);

  // 2. Build location string
  String mapLink = "";
  String locationStr = "";

  if (latitude != 0.0 && longitude != 0.0) {
    mapLink = "https://maps.google.com/?q=" + String(latitude, 6) + "," + String(longitude, 6);
    locationStr = "Lat:" + String(latitude, 6) + " Lon:" + String(longitude, 6);
  } else {
    locationStr = "GPS fix not acquired yet";
    mapLink = "GPS unavailable";
  }

  // 3. Build SMS
  String sms = "🚨 EMERGENCY ALERT 🚨
";
  sms += "From: " + String(DEVICE_NAME) + "
";
  sms += "Location: " + locationStr + "
";
  sms += "Map: " + mapLink + "
";
  sms += "PLEASE RESPOND IMMEDIATELY";

  // 4. Send SMS to both contacts
  Serial.println("Sending emergency SMS...");
  sendSMS(CONTACT_1, sms);
  if (strlen(CONTACT_2) > 4) sendSMS(CONTACT_2, sms);

  // 5. Auto call contact 1
  Serial.println("Calling emergency contact...");
  makeCall(CONTACT_1);

  Serial.println("✅ Emergency alerts sent!");
}

// ── HELPERS ──────────────────────────────────────────────
void sendSMS(const char* number, String message) {
  modem.sendSMS(number, message);
  Serial.println("SMS sent to " + String(number));
}

void makeCall(const char* number) {
  modem.callNumber(number);
  delay(20000);   // Ring for 20 seconds
  modem.callHangup();
}

void blinkLED(int times, int delayMs) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(delayMs);
    digitalWrite(LED_PIN, LOW);
    delay(delayMs);
  }
}
