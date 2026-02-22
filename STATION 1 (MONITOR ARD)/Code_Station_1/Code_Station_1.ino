#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ------------------- SENSOR DEFINITIONS -------------------
#define LED_RED 2
#define LED_GREEN 3
#define BUZZERPIN 7
#define DHTPIN 4
#define DHTTYPE DHT11
#define LDRPIN A2

// ------------------- OBJECT DECLARATIONS -------------------
LiquidCrystal_I2C lcd(0x20, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

// ------------------- VARIABLES -------------------
int temperatureDHT, humidity;
int lightLevel;
int lightPercent;
// ------------------- SETUP -------------------
void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(LDRPIN, INPUT);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("MONITORING SYST");
  delay(2000);
  lcd.clear();
}

// ------------------- LOOP -------------------
void loop() {
  // Read sensor values
  humidity = dht.readHumidity();
  temperatureDHT = dht.readTemperature();
  lightLevel = analogRead(LDRPIN);

  lightPercent = map(lightLevel, 0, 1023, 0, 100);

  lcd.clear();

  // ------------------- MONITORING LOGIC -------------------
  
  // --- Case 1: High Temperature ---
  if (temperatureDHT >= 30) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    tone(BUZZERPIN, 1000);

    lcd.setCursor(0, 0);
    lcd.print("ALERT: HIGH TEMP");
    lcd.setCursor(0, 1);
    lcd.print("Temp: "); lcd.print(temperatureDHT); lcd.print("C");
  } 
  
  // --- Case 2: High Humidity ---
  else if (humidity > 70) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    tone(BUZZERPIN, 1000);

    lcd.setCursor(0, 0);
    lcd.print("ALERT: HUMID");
    lcd.setCursor(0, 1);
    lcd.print("Hum: "); lcd.print(humidity); lcd.print("%");
  }

  // --- Case 3: Low Humidity ---
  else if (humidity < 40) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    tone(BUZZERPIN, 800);

    lcd.setCursor(0, 0);
    lcd.print("ALERT: LOW HUM");
    lcd.setCursor(0, 1);
    lcd.print("Hum: "); lcd.print(humidity); lcd.print("%");
  }

  // --- Case 4: All Normal ---
  else {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    noTone(BUZZERPIN);

    lcd.setCursor(0, 0);
    lcd.print("Temp: "); lcd.print(temperatureDHT); lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Lgt:"); lcd.print(lightPercent); lcd.print("% ");
    lcd.print("Hum:"); lcd.print(humidity); lcd.print("%");
  }

  // ------------------- TIMESTAMP & CSV -------------------
  unsigned long timestamp = millis() / 1000;
  
  // CSV Output format: Time, Temperature, Humidity, Light Level
  String csvData = String(timestamp) + "," + 
                   String(temperatureDHT) + "," + 
                   String(humidity) + "," + 
                   String(lightPercent);

  Serial.println(csvData);

  delay(2000); // 2-second delay for simulation stability
}
