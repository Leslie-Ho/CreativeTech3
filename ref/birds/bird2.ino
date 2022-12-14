#include "config.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

AdafruitIO_Feed *myFeed = io.feed("lightFeed2");
AdafruitIO_Feed *subFeed = io.feed("lightFeed1");

int prevBird;
int myBirdHeight = 0;

int timeCounter = 0;
float prevTime = 0;
float curTime = 0;

void setup() {
  Serial.begin(115200);
  AFMS.begin();
  myMotor->setSpeed(50);
  myMotor->run(FORWARD); 
  myMotor->run(RELEASE);
  
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
  subFeed->onMessage(handleMessage);
  subFeed->get();
}

void loop() {
  io.run();
  changeHeight();  
  checkTime();
}

void handleMessage(AdafruitIO_Data *data) {
  String temp = String(data -> value());
  Serial.println("handle data");
  prevBird = temp.toInt();
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
    Serial.print("backward");
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
