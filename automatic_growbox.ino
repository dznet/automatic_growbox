unsigned long last_time;
unsigned long diff_time;

const int H_MIN  = 700;
const int H_WARN = 400;

int w_pump   = 12;
int warning  = 11;
int comfort  = 10;
int sensor   = A0;
int humidity = 0;

void setup()
{
  pinMode(w_pump, OUTPUT);
  pinMode(warning, OUTPUT);
  pinMode(comfort, OUTPUT);
  pinMode(sensor, INPUT);
}

void loop()
{
  humidity = analogRead(sensor);
  
  if(humidity >= H_WARN) {
    diff_time = millis() - last_time;
    if(diff_time > 14400000) {
      last_time = millis();
      digitalWrite(w_pump, HIGH);
      delay(30000);
      digitalWrite(w_pump, LOW);
    }
  } 
  else {
    digitalWrite(comfort, HIGH);
    delay(1000);
    digitalWrite(comfort, LOW);
  }
  if(humidity >= H_MIN) {
    digitalWrite(warning, HIGH);
    delay(30000);
    digitalWrite(warning, LOW);
  }
}