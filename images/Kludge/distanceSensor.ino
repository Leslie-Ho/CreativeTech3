int trigPinS1 = 12;    // Trigger
int echoPinS1 = 11;    // Echo
long durationS1, sensor1;

int trigPinS2 = 9;    // Trigger
int echoPinS2 = 10;    // Echo
long durationS2, sensor2;

int buttonPin = 7;
int buttonRead;

bool calibrated = false;
long calibSens1 = 0;
long calibSens2 = 0;

bool isSomeoneHere = false;
int visitors;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPinS1, OUTPUT);
  pinMode(echoPinS1, INPUT);

  pinMode(trigPinS2, OUTPUT);
  pinMode(echoPinS2, INPUT);

  pinMode(buttonPin, INPUT);
}
 
void loop() {
  digitalWrite(trigPinS1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinS1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinS1, LOW);
  pinMode(echoPinS1, INPUT);
  durationS1 = pulseIn(echoPinS1, HIGH); 
  sensor1 = (durationS1/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  

//SENSOR 2
  digitalWrite(trigPinS2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinS2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinS2, LOW); 
  pinMode(echoPinS2, INPUT);
  durationS2 = pulseIn(echoPinS2, HIGH);
  sensor2 = (durationS2/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  //which way did the visitor go?

  buttonRead = digitalRead(buttonPin);
  if(!buttonRead) {
    calibSens1 = sensor1;
    calibSens2 = sensor2;
    calibrated = true;
  }

  if (calibrated) {
    if((calibSens1 - sensor1 < 50) && (calibSens2 - sensor2 < 50) ) {
      isSomeoneHere = false;
    } else {
      isSomeoneHere = true;
    }

    if (isSomeoneHere) {
      if((calibSens1 - sensor1 > 50) && (calibSens2 - sensor2 < 50)) {
        visitors++; 
      } else if ((calibSens1 - sensor1 < 50) && (calibSens2 - sensor2 > 50)) {
        if (visitors > 0) {
          visitors--;
        }  
      }
    }
  }
  Serial.print("s1: ");
  Serial.print(sensor1);
  Serial.print(",");
  Serial.print("c1: ");
  Serial.print(calibSens1);
  Serial.print(",");
  Serial.print("s2: ");
  Serial.print(sensor2);
  Serial.print(",");
  Serial.print("c2: ");
  Serial.println(calibSens2);

//
//  Serial.print("buttonRead: ");
//  Serial.print(buttonRead);
//  Serial.println(",");
//
//  Serial.print(calibrated);
//  Serial.print(",");
//  Serial.println(visitors);
  delay(250);
}
