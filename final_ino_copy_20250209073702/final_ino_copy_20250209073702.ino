#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3NtILrnJe"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"
#define BLYNK_AUTH_TOKEN "5Wh5AGAhLbU7bpdPBv7tJUztUSb3RcHC"

#include <Blynk.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// 🔹 WiFi Credentials
// ✅ Ensure the full token is inside quotes
#define WIFI_SSID "wifi2"
#define WIFI_PASS "12345678"

// 🔹 Sensor & Relay Pins
#define SOIL_SENSOR_PIN 34  // Soil moisture sensor (Analog)
#define WATER_LEVEL_PIN 35  // HW-038 Water Level Sensor (Analog)
#define RELAY_PIN 5        // Relay for Water Pump

// 🔹 Threshold Values
#define MOISTURE_THRESHOLD 30  // % moisture to turn ON pump
#define WATER_LEVEL_THRESHOLD 20 // % water level to run pump

BlynkTimer timer; // Timer for sending data

void sendData() {

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  int soilRaw = analogRead(SOIL_SENSOR_PIN);
  int soilMoisture = map(soilRaw, 0, 4095, 100, 0); // Convert to percentage

  int waterRaw = analogRead(WATER_LEVEL_PIN);
  int waterLevel = map(waterRaw, 0, 4095, 0, 100); // Convert to percentage

  // Pump Logic
  if (soilMoisture < MOISTURE_THRESHOLD && waterLevel > WATER_LEVEL_THRESHOLD) {
    digitalWrite(RELAY_PIN, LOW); // Pump ON
    Blynk.virtualWrite(V2, "ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Pump OFF
    Blynk.virtualWrite(V2, "OFF");
  }

  // Send data to Blynk
  Blynk.virtualWrite(V0, soilMoisture);
  Blynk.virtualWrite(V1, waterLevel);

  Serial.print("Soil Moisture: "); Serial.print(soilMoisture); Serial.println("%");
  Serial.print("Water Level: "); Serial.print(waterLevel); Serial.println("%");
}

void setup() {
  Serial.begin(115200);
  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(WATER_LEVEL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Ensure pump is OFF at startup

  // Connect to WiFi & Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN,WIFI_SSID, WIFI_PASS);
  
  // Set timer to send data every 5 seconds
  timer.setInterval(5000L, sendData);
}

void loop() {
  Blynk.run(); // Run Blynk
  timer.run(); // Run Timer
}