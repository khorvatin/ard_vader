
#include <Servo.h>
#define leftTrigPin 8
#define leftEchoPin 9

long headPos = 0;
Servo myServo;
//Servo saberServo;
void setup() {
  Serial.begin (9600);
  myServo.attach(7);
  //saberServo.attach(13);
}

long turningHead = 0;
long lastDiff;

long leftDistance = 1000;
  
void loop() {
  if (!turningHead)
  {
    leftDistance = GetDistance(leftTrigPin, leftEchoPin);
    delay(5);
  }
  
  PrintSide(leftDistance);
  delay(5);
}

void PrintSide(int left) {
  if (left > 0 && left < 50) {
      if (headPos < 50) {
        headPos++;
        turningHead = true;
      }
      else {
        turningHead = 0;
      }
      pinMode(12, OUTPUT);
      digitalWrite(12, HIGH);
  }
  else if (headPos > 0) {
    
      pinMode(12, OUTPUT);
      digitalWrite(12, LOW);
      headPos--;
      turningHead = true;
  }
  else {
    turningHead = false;
  }

  if (turningHead) {
    myServo.write(headPos);
  }
}

long GetDistance(int trig, int echo) {
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  return cm;
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
