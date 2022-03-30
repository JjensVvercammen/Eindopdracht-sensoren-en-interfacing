#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

char auth[] = "y5Oj9vGyCsyGpbROK15ynEg-xU0Ks_AX";
char ssid[] = "telenet-0BB62";
char pass[] = "F8vPuVsXH4P3";

#define DHTPIN 19
#define DHTTYPE DHT11

#define led_rood 2
#define led_groen 5
#define led_geel 4
int button = 22;

#define temperatuur V0
#define wanted_temp V1

WidgetLED rode_led(V2);
WidgetLED groene_led(V3);
WidgetLED gele_led(V4);

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temp = 0;
float v = 0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);

  dht.begin();
  pinMode(led_rood, OUTPUT);
  pinMode(led_groen, OUTPUT);
  pinMode(led_geel, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  Blynk.run();

  Blynk.virtualWrite(temperatuur, temp);
  Blynk.virtualWrite(wanted_temp, v);

  delay(100);

  float val = map(analogRead(34), 0, 1023, 100, 300);
  float getal = val / 10;

  float t = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  temp = t;

  if (getal > temp - 1)
  {
    digitalWrite(led_groen, HIGH);
    digitalWrite(led_geel, LOW);
    digitalWrite(led_rood, LOW);
    groene_led.on();
    gele_led.off();
    rode_led.off();
  } else
  {
    digitalWrite(led_geel, HIGH);
    digitalWrite(led_groen, LOW);
    digitalWrite(led_rood, LOW);
    gele_led.on();
    groene_led.off();
    rode_led.off();
  }
  if (temp > 22)
  {
    digitalWrite(led_rood, HIGH);
    digitalWrite(led_groen, LOW);
    digitalWrite(led_geel, LOW);
    rode_led.on();
    groene_led.off();
    gele_led.off();
  }
  while (digitalRead(button) == LOW)
  {

    Serial.print(F("  Temperature: "));
    Serial.print(t);
    Serial.println("");

    temp = t;


    Serial.print(F("  wanted: "));
    Serial.print(getal);
    Serial.println("");
  }
}
