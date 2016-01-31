#include <NS_Rainbow.h>
//*****************LED-BUTTON************
#define PIN 9
#define N_CELL 8

const int buttonPin = 2;
int buttonState = 0;
boolean running = false;
String incomingByte = "";

NS_Rainbow ns_stick = NS_Rainbow(N_CELL,PIN);
//*****************LED-BUTTON************
//*****************TEMPERATURE************
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int showTemp = 0;

int actualTEMP = 22;
int oldTEMP = 22;

int inputPin = 0;
//*****************TEMPERATURE************
//*****************RELAYSWITCH************
int relayPIN = 4;
boolean launchRelay = false;
boolean relayHIGH = false;
//*****************RELAYSWITCH************

void setup() {
  pinMode(buttonPin, INPUT);
  // initialize serial:
  Serial.begin(9600);
  delay(5000);
  Serial.setTimeout(10);
  ns_stick.begin();

  ns_stick.setBrightness(64);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  pinMode(relayPIN, OUTPUT);
}

void loop() {
  temperature();
  buttonShow();
  ledShow();
  relaySwitch();
}

void relaySwitch(){
  if(launchRelay && relayHIGH){
    digitalWrite(relayPIN, HIGH);
    relayHIGH = false;
  } else if (!launchRelay && !relayHIGH) {
    digitalWrite(relayPIN, LOW);
    relayHIGH = true;
  }
}

void buttonShow(){
  // read data from pushbutton
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && !running) {
    ledButtonShow(192,0,0);
    Serial.println("BTN,CLOSED");
    running = true;
  } if (buttonState != HIGH && running) {
    ledButtonShow(0,192,0);
    Serial.println("BTN,OPEN");
    running = false;
  }
}

void ledButtonShow(int r, int g, int b){
  cleanLED();
  for (int i=7; i >= 0; i--){
    ns_stick.setColor(i, r, g, b);
    delay(30);
    ns_stick.show();
  }
  cleanLED();
}

void cleanLED(){
  for (int i=0; i <= 7; i++){
    ns_stick.setColor(i, 0, 0, 0);
    ns_stick.show();
  }
}

void ledShow(){
  incomingByte = "";
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    incomingByte = Serial.readString();

    // look for the next valid integer in the incoming serial stream
    if(incomingByte.length() != 1){
      int led = incomingByte.substring(0, 1).toInt();
      // String redS = incomingByte.substring(1, 4);
      int red = incomingByte.substring(1, 4).toInt();

      // do it again:
      // String greenS = incomingByte.substring(4, 7);
      int green = incomingByte.substring(4, 7).toInt();

      // do it again:
      // String blueS = incomingByte.substring(7, 10);
      int blue = incomingByte.substring(7, 10).toInt();

        ns_stick.setColor(led, red, green, blue);
        ns_stick.show();
    } else if (incomingByte.equals("8")){
      launchRelay = true;
    } else {
      launchRelay = false;
    }
  }
}

void temperature() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  actualTEMP = 10+(average / 50);
  // send it to the computer as ASCII digits
  if (actualTEMP != oldTEMP) {
    Serial.print("TMP,");
    Serial.println(actualTEMP);
    oldTEMP = actualTEMP;
  }
}
