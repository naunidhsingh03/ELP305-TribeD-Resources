#include "DHT.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#define DHTPIN 12  // Pin connected to the DHT sensor

#define DHTTYPE DHT11  // DHT 11

#define pwm 9  // PWM pin for fan speed control

byte degree[8] =
{
  0b00011,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(1, degree);
  lcd.clear();
  lcd.print("   Fan Speed  ");
  lcd.setCursor(0, 1);
  lcd.print("  Controlling ");
  delay(2000);
  analogWrite(pwm, 255);
  delay(2000);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in t in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);   // Printing temperature on LCD
  lcd.print(" C");
  lcd.setCursor(0, 1);

  // Fan Speed Control based on Temperature
  if (t > 29) {
    analogWrite(9, 0);
    lcd.print("Fan OFF         ");
    delay(100);
  } else if (t == 29) {
    analogWrite(pwm, 51);
    lcd.print("Fan Speed: 20%   ");
    delay(100);
  } else if (t == 28) {
    analogWrite(pwm, 102);
    lcd.print("Fan Speed: 40%   ");
    delay(100);
  } else if (t == 24) {
    analogWrite(pwm, 153);
    lcd.print("Fan Speed: 60%   ");
    delay(100);
  } else if (t == 20) {
    analogWrite(pwm, 204);
    lcd.print("Fan Speed: 80%   ");
    delay(100);
  } else if (t < 20) {
    analogWrite(pwm, 255);
    lcd.print("Fan Speed: 100%   ");
    delay(100);
  }

  delay(3000);
}