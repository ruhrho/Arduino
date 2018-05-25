#include <AFMotor.h>
//other used pins in AFMotor.h: 3,4, 7, 8, 12, 11
//motor setup
AF_DCMotor motorRight(2);
AF_DCMotor motorLeft(1);

//range finder pins
const int TRIG_PIN = 5;
const int ECHO_PIN = 2;

//LED pins
const int blueRGB = 13;  //blue | rgb
const int redRGB = 6; //red | rgb
const int greenRGB = 9; //green | rgb

//push button
const int pushButton = 10;

//push button state
int buttonState = 0;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

// set minDistance of stuff for sensor to "see" before attempting to turn and get away from it
const float minDistance = 18.00;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  Serial.begin(115200);

  // turn on motor
  motorRight.setSpeed(190);
  motorLeft.setSpeed(220);
  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);

  //led pins
  pinMode(blueRGB, OUTPUT);
  pinMode(redRGB, OUTPUT);
  pinMode(greenRGB, OUTPUT);

  //inputButton
  pinMode(pushButton, INPUT);

  //set led pins to low
  digitalWrite(blueRGB, LOW);
  digitalWrite(redRGB, LOW);
  digitalWrite(greenRGB, LOW);

}

void loop() {
  buttonState = digitalRead(pushButton);
  Serial.println("loop start");
  float distance;
  distance = rangeFind();
  Serial.print("range find | ");
  
  while (buttonState == LOW){
    pause();
  }
    
  if (distance >= minDistance) {
    Serial.print("forward | ");
    Serial.println(distance);
    forward();
    distance = 0;
  }
  else {
    Serial.print("reverse | ");
    backward();
    int randNum = random(100);
    if (randNum < 50) {
      right();
      Serial.print("right | ");
      while (distance <= minDistance) {
        right();
        distance = rangeFind();
        delay(20);
        right();
      }
    }
    else if (randNum >= 50) {
      left();
      Serial.print("left | ");

      while (distance <= minDistance) {
        left();
        distance = rangeFind();
        delay(20);
        left();
      }
    }

  }
  
}

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


void forward() {
  uint8_t i;
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  for (i = 0; i < 50; i++) {
    digitalWrite(blueRGB, HIGH);
    digitalWrite(redRGB, HIGH);

    motorRight.setSpeed(190);
    motorLeft.setSpeed(220);
    delay(10);
    digitalWrite(blueRGB, LOW);
    digitalWrite(redRGB, LOW);
  }
}

void backward() {
  uint8_t i;
  motorRight.run(BACKWARD);
  motorLeft.run(BACKWARD);
  for (i = 0; i < 50; i++) {
    digitalWrite(redRGB, HIGH);
    motorRight.setSpeed(200);
    motorLeft.setSpeed(200);

    delay(10);
  }
  for (i = 10; i != 0; i--) {
    motorRight.setSpeed(i);
    motorLeft.setSpeed(i);
    delay(10);
    digitalWrite(redRGB, LOW);
  }
} 

void left() {
  uint8_t i;
  int randNum = random(100);
  motorRight.run(BACKWARD);
  motorLeft.run(FORWARD);
  for (i = 0; i < 20; i++) {
    digitalWrite(greenRGB, HIGH);
    digitalWrite(redRGB, HIGH);
    motorRight.setSpeed(175);
    motorLeft.setSpeed(150);
    delay(10);
  }
  for (i = 10; i != 0; i--) {
    motorRight.setSpeed(i);
    motorLeft.setSpeed(i);
    delay(10);
    digitalWrite(greenRGB, LOW);
    digitalWrite(redRGB, LOW);
  }
}
void pause(){
  uint8_t i;
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  for(i=0; i<50; i++){
    motorRight.setSpeed(0);
    motorLeft.setSpeed(0);
    delay(10);
  }
  
}
void right() {
  uint8_t i;
  int randNum = random(100);
  motorRight.run(FORWARD);
  motorLeft.run(BACKWARD);
  for (i = 0; i < 20; i++) {
    digitalWrite(blueRGB, HIGH);
    digitalWrite(greenRGB, HIGH);
    motorRight.setSpeed(150);
    motorLeft.setSpeed(175);

    delay(10);
  }
  for (i = 10; i != 0; i--) {
    motorRight.setSpeed(i);
    motorLeft.setSpeed(i);
    delay(10);
    digitalWrite(blueRGB, LOW);
    digitalWrite(greenRGB, LOW);
  }
}
