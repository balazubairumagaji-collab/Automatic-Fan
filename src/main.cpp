#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTTYPE DHT11
#define DHTPIN 2
#define fanPin 9

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temp fan control");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(3000);
  lcd.clear();
}

void loop() {
  delay(2000);

  const float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor error    ");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C   ");

  if (temperature > 32.0f) {
    digitalWrite(fanPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Fan: ON         ");
  } else {
    digitalWrite(fanPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Fan: OFF        ");
  }
}
