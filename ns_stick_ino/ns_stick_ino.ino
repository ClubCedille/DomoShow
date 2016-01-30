#include <NS_Rainbow.h>

#define PIN 9
#define N_CELL 8

const int buttonPin = 2;
int buttonState = 0;
boolean running = false;

NS_Rainbow ns_stick = NS_Rainbow(N_CELL,PIN);
void setup() {
  pinMode(buttonPin, INPUT);
  // initialize serial:
  Serial.begin(9600);
  delay(100);
  ns_stick.begin();

  ns_stick.setBrightness(64);
}

void loop() {

  // read data from pushbutton
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && !running) {
    Serial.println("BTN,OPEN");
    // ns_stick.setColor(0, 0, 255, 0);
    // ns_stick.show();
    running = true;
  } if (buttonState != HIGH && running) {
    Serial.println("BTN,CLOSE");
    // ns_stick.setColor(0, 255, 0, 0);
    // ns_stick.show();
  }

  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int led = Serial.parseInt();
    int red = Serial.parseInt();
    // do it again:
    int green = Serial.parseInt();
    // do it again:
    int blue = Serial.parseInt();

    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '\n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      led = led;
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);

      ns_stick.setColor(led, red, green, blue);
      ns_stick.show();
      // print the three numbers in one string as hexadecimal:
      Serial.print(led);
      Serial.print(" : ");
      Serial.print(red);
      Serial.print(green);
      Serial.println(blue);
    }
  }
}
