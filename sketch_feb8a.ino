#include <Wire.h>
#include <SPI.h>
#include <U8g2lib.h>

// Initialize OLED472 (SH1106/SSD1309) in SPI Mode
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Define Sensor & Relay Pins
#define SOIL_SENSOR_PIN 34    // Soil moisture sensor (Analog)
#define WATER_LEVEL_PIN 35    // HW-038 Water Level Sensor (Analog)
#define RELAY_PIN 5         // Relay control pin

// Soil moisture threshold (Adjust based on soil type)
#define MOISTURE_THRESHOLD 70
  // Below this, the pump turns ON
#define WATER_LEVEL_THRESHOLD 20  // Below this, the pump won't run

void setup() {
  Serial.begin(115200);

  // Initialize OLED472 Display
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(10, 20, "Smart Irrigation");
  u8g2.sendBuffer();
  delay(2000);

  // Sensor & Relay Setup
  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(WATER_LEVEL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Ensure pump is OFF at startup
}

void loop() {
  // Read Soil Moisture Sensor
  int soilRaw = analogRead(SOIL_SENSOR_PIN);
  int soilMoisture = map(soilRaw, 0, 4095, 100, 0); // Convert to percentage (0-100%)

  // Read Water Level Sensor
  int waterRaw = analogRead(WATER_LEVEL_PIN);
  int waterLevel = map(waterRaw, 0, 4095, 0, 100); // Convert to percentage (0-100%)

  // Print Values in Serial Monitor
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.println("%");

  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  // Control Water Pump
  String pumpStatus;
  if (soilMoisture < MOISTURE_THRESHOLD) { // If soil is dry
    if (waterLevel > WATER_LEVEL_THRESHOLD) { // If tank has enough water
      digitalWrite(RELAY_PIN, LOW); // Turn ON Pump
      pumpStatus = "PUMP: ON";
      Serial.println("Pump ON: Watering...");
    } else {
      pumpStatus = "Low Water! Pump OFF";
      Serial.println("Low Water Level! Pump OFF");
    }
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Turn OFF Pump
    pumpStatus = "PUMP: OFF";
    Serial.println("Pump OFF: Soil is Moist");
  }

  // Update OLED472 Display
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  
  u8g2.drawStr(10, 10, "Smart Irrigation");
  
  char soilStr[20];
  sprintf(soilStr, "Soil Moisture: %d%%", soilMoisture);
  u8g2.drawStr(10, 25, soilStr);

  char waterStr[20];
  sprintf(waterStr, "Water Level: %d%%", waterLevel);
  u8g2.drawStr(10, 40, waterStr);

  u8g2.drawStr(10, 55, pumpStatus.c_str());

  u8g2.sendBuffer(); // Update display

  delay(5000); // Wait 5 seconds before next reading
}