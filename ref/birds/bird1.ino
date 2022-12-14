#include "config.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

AdafruitIO_Feed *myFeed = io.feed("lightFeed1");

int trigPin = 5;
int echoPin = 18;
int maxDistance = 100;
long duration, sensor;

int prevBird;
int myBirdHeight = 0;

int timeCounter = 0;
float prevTime = 0;
float curTime = 0;

void setup() {
  Serial.begin(115200);
  AFMS.begin();
   
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  io.run();
  
  // put your main code here, to run repeatedly:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
     
    duration = pulseIn(echoPin, HIGH);
    sensor = (duration / 2) / 29.1;    
    
    setBirdHeight();
    changeHeight();

    checkTime();
}

void checkTime() {
  curTime = millis() % 4000;
  if(curTime < prevTime) {
    myFeed->save(prevBird);
    Serial.print("sentData");
    //timeCounter = 0;
  }
  prevTime = curTime;
}

void setBirdHeight() {
  int mappedDistance = map(sensor, 0, maxDistance, 0, 100);
    if(mappedDistance > maxDistance) {
      prevBird = 100;
    } else {
      prevBird = mappedDistance;
    }
}

void changeHeight() { 
  int birdGap = prevBird - myBirdHeight;
  int moveBuff = 5;
  myMotor -> setSpeed(30);
  
  if(birdGap >= moveBuff) {
    myMotor -> run(FORWARD);
    myBirdHeight += moveBuff;
    Serial.print("forward");
  }
  if(birdGap <= -moveBuff) {
    myMotor -> run(BACKWARD);
    myBirdHeight -= moveBuff;
  }
  if(birdGap < moveBuff && birdGap > -moveBuff) {
    myMotor -> run(RELEASE);
  }
  Serial.print(prevBird);
  Serial.print(", ");
  Serial.print(myBirdHeight);
  Serial.print(" , birdGap: ");
  Serial.println(birdGap); 
}
