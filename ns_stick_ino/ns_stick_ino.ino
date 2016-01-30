#include <NS_Rainbow.h>

#define PIN 9
#define N_CELL 8

const int buttonPin = 2;
int buttonState = 0;
boolean running = false;
String incomingByte = "";

NS_Rainbow ns_stick = NS_Rainbow(N_CELL,PIN);
void setup() {
  pinMode(buttonPin, INPUT);
  // initialize serial:
  Serial.begin(9600);
  delay(100);
  Serial.setTimeout(10);
  ns_stick.begin();

  ns_stick.setBrightness(64);
}

void loop() {
  incomingByte = "";

  // read data from pushbutton
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && !running) {
    Serial.println("BTN,OPEN");
    running = true;
  } if (buttonState != HIGH && running) {
    Serial.println("BTN,CLOSED");
    running = false;
  }

  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    incomingByte = Serial.readString();

    Serial.println(incomingByte);
    // look for the next valid integer in the incoming serial stream:
    // String ledS = incomingByte.substring(0, 1);
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
      // print the three numbers in one string as hexadecimal:
      Serial.println(led);

  }
}
