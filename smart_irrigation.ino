/*
  Smart Irrigation System
  Board: Arduino Uno
  Sensor: LM393 soil moisture module, analog output -> A0
  Relay: 5V relay module, input -> D8

  Assumptions:
  - Sensor reading is higher when soil is dry.
  - Relay input is active LOW.
  - Thresholds must be calibrated for the actual sensor and soil.
*/

const byte SOIL_SENSOR_PIN = A0;
const byte RELAY_PIN = 8;

// Example starting values only. Calibrate using Serial Monitor.
const int DRY_THRESHOLD = 650;
const int WET_THRESHOLD = 450;

// Most common relay modules are active LOW; verify your module.
const byte RELAY_ON_LEVEL  = LOW;
const byte RELAY_OFF_LEVEL = HIGH;

bool pumpIsOn = false;

void setPump(bool turnOn) {
  digitalWrite(RELAY_PIN, turnOn ? RELAY_ON_LEVEL : RELAY_OFF_LEVEL);
  pumpIsOn = turnOn;
}

void setup() {
  // Set OFF state before normal operation.
  digitalWrite(RELAY_PIN, RELAY_OFF_LEVEL);
  pinMode(RELAY_PIN, OUTPUT);
  setPump(false);

  Serial.begin(9600);
  Serial.println(F("Smart Irrigation System started"));
  Serial.println(F("Calibrate thresholds for your own soil."));
}

void loop() {
  const int moistureRaw = analogRead(SOIL_SENSOR_PIN);

  Serial.print(F("Raw soil reading: "));
  Serial.print(moistureRaw);
  Serial.print(F(" | Pump: "));
  Serial.println(pumpIsOn ? F("ON") : F("OFF"));

  // Higher reading means drier soil for the assumed sensor orientation.
  if (!pumpIsOn && moistureRaw >= DRY_THRESHOLD) {
    setPump(true);
    Serial.println(F("Soil dry: relay ON"));
  } else if (pumpIsOn && moistureRaw <= WET_THRESHOLD) {
    setPump(false);
    Serial.println(F("Soil wet: relay OFF"));
  }

  delay(1000);
}
