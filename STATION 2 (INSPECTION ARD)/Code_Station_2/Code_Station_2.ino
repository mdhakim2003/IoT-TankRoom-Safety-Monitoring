#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ------------------- SENSOR DEFINITIONS -------------------
#define LED_RED 2
#define LED_GREEN 3
#define TRIG 12
#define ECHO 11
const int smokeSensorPin = A1; // POT-HG connected here
#define BUZZERPIN 7

#define EN1 6
#define IN1 10
#define IN2 9

// ------------------- OBJECT DECLARATIONS -------------------
// For Proteus PCF8574 simulation, use address 0x20
LiquidCrystal_I2C lcd(0x20, 16, 2); 

// ------------------- VARIABLES -------------------
float distance;
int occupancy = 0;   
int fanState = 0;
int smokeValue = 0;    // To store raw ADC reading (0-1023)
int smokePercent = 0;  // To store converted percentage (0-100)

// ------------------- ULTRASONIC FUNCTION -------------------
float getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  float duration = pulseIn(ECHO, HIGH);
  return (duration * 0.0343) / 2;
}

// ------------------- SETUP -------------------
void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(smokeSensorPin, INPUT);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Inspection Monitor");
  delay(2000);
  lcd.clear();
}

// ------------------- LOOP -------------------
void loop() {
  // 1. Read Sensors
  distance = getDistance();
  smokeValue = analogRead(smokeSensorPin); // Read the pin, not a variable
  
  // 2. Convert raw data to percentage
  smokePercent = map(smokeValue, 0, 1023, 0, 100); 

  lcd.clear();

  // ------------------- LOGIC: OCCUPANCY -------------------
  if (distance >= 50) {
    occupancy = 0;
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    noTone(BUZZERPIN);
    
    fanState = 0;
    digitalWrite(EN1, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    lcd.setCursor(0, 0);
    lcd.print("No Occupancy");

  } else {
    occupancy = 1;
    lcd.setCursor(0, 0);
    lcd.print("In Inspection");

    // --- R2: Smoke Detection Alert ---
    // Threshold set to 40% (adjust as needed for POT-HG)
    if (smokePercent >= 40) {
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
      tone(BUZZERPIN, 1000);

      fanState = 1;
      digitalWrite(EN1, HIGH);
      digitalWrite(IN1, HIGH); // Max speed
      digitalWrite(IN2, LOW);

      lcd.setCursor(0, 1);
      lcd.print("SMOKE ALERT: ");
      lcd.print(smokePercent);
      lcd.print("%");
    } 
    else {
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, HIGH);
      noTone(BUZZERPIN);

      fanState = 0;
      digitalWrite(EN1, LOW);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);

      lcd.setCursor(0, 1);
      lcd.print("Safe: ");
      lcd.print(smokePercent);
      lcd.print("%");
    }
  }

  // ------------------- CSV FORMAT -------------------
  unsigned long timestamp = millis() / 1000;
  String csvData =
    String(timestamp) + "," +
    String(occupancy) + "," +
    String(distance, 2) + "," +
    String(smokePercent) + "," +
    String(fanState);

  Serial.println(csvData);

  delay(2000); // 2-second update for Proteus stability
}
