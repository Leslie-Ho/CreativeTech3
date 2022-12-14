#include "config.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

AdafruitIO_Feed *subFeed = io.feed("lightFeed2");

int prevBird;
int myBirdHeight = 0;

int timeCounter = 0;

void setup() {
  Serial.begin(115200);
  AFMS.begin();
  myMotor->setSpeed(50);
  myMotor->run(FORWARD); 
  myMotor->run(RELEASE);
  
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  subFeed->onMessage(handleMessage);
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
  subFeed->get();
}

void loop() {
  io.run();
  
  changeHeight();
}

void handleMessage(AdafruitIO_Data *data) {
  String temp = String(data -> value());
  prevBird = temp.toInt();
}

void changeHeight() { 
  int birdGap = prevBird - myBirdHeight;
  int moveBuff = 5;
  myMotor -> setSpeed(50);
  
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
