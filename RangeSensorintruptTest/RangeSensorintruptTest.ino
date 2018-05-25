const int TRIG_PIN = 5;
const int ECHO_PIN = 2;

// Max range of 400 CM
const unsigned int MAX_DIST=23200;

//minDist for sensor use in bot context 
const float minDist = 18;

float rangeFind() {
  pinMode(TRIG_PIN, OUTPUT);
  
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float distance = 0;
  unsigned long TRIG_PING_TIMER = 0;
  unsigned long currentMillis = millis();
  unsigned long pingTimer = 20;
  int pingStatus=LOW;
  
  if (pingStatus==LOW&& currentMillis - TRIG_PING_TIMER >= pingTimer){
    TRIG_PING_TIMER = currentMillis;
    Serial.print(TRIG_PING_TIMER);
    Serial.print("|");
    Serial.println(currentMillis);
    pingStatus=HIGH;
    digitalWrite(TRIG_PIN, pingStatus);
    Serial.println(pingStatus);
  }
      
    if(pingStatus==HIGH&&currentMillis-TRIG_PING_TIMER < pingTimer){
      TRIG_PING_TIMER=currentMillis;
      pingStatus=LOW;
      digitalWrite(TRIG_PIN, pingStatus);
    }

  Serial.print(pingStatus);
  //echo trigger
  while ( digitalRead(ECHO_PIN) == 0);
  t1 = micros();

  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // calculate distance in CM
  cm = pulse_width / 58.0;
  Serial.println(cm);
  Serial.println(pingStatus);
  Serial.println(TRIG_PING_TIMER);
  (distance = cm);
  return distance;

}

void setup() {
Serial.begin(115200);  //start serial comms
}

void loop() {
float Dist;
Dist = rangeFind();
Serial.println(Dist);
Serial.println("testing...");
delay (2000);

}
