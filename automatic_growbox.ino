// Automatic GrowBox by dzNET


#include "DHT.h"
#define DHTPIN 0
#define DHTTYPE DHT22

unsigned long diff_time;

const int H_MIN  = 700;
const int H_WARN = 400;
const int air_time = 3000;
const int water_time = 6000;
const long interval = 14400000;

int w_pump = 12;
int warning = 11;
int comfort = 10;
int dhtErr = 9;
int hot_air = 8;
int cold_air = 7;
int inPin = A0;
int num = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(w_pump, OUTPUT);
  pinMode(warning, OUTPUT);
  pinMode(comfort, OUTPUT);
  pinMode(dhtErr, OUTPUT);
  pinMode(hot_air, OUTPUT);
  pinMode(cold_air, OUTPUT);
  pinMode(inPin, INPUT);
  dht.begin();
}

void loop() {
  airPump();  
  waterPump();
}

void waterPump() {
  num = analogRead(inPin);
  
  if(num >= H_WARN) {;
    if(millis() - diff_time > interval) {
      diff_time = millis();
      digitalWrite(w_pump, HIGH);
      delay(3000);
      digitalWrite(w_pump, LOW);
    }
  }else {
    digitalWrite(comfort, HIGH);
    delay(1000);
    digitalWrite(comfort, LOW);
  }
  if(num >= H_MIN) {
    digitalWrite(warning, HIGH);
    delay(1000);
    digitalWrite(warning, LOW);
  }
}

void airPump() {
  float h   = dht.readHumidity();
  float t   = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false);

  if (isnan(h) || isnan(t)) {
    digitalWrite(dhtErr, HIGH);
    delay(1000);
    digitalWrite(dhtErr, LOW);
    return;
  }  
  if (t < 20.00){
    digitalWrite(hot_air, HIGH);
    delay(3000);
    digitalWrite(hot_air, LOW);
  }
  if (t > 24.00) {
    digitalWrite(cold_air, HIGH);
    delay(3000);
    digitalWrite(cold_air, LOW);
  }
}
