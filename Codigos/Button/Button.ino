/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button cacacacacacacaca
*/

// constants won't change. They're used here to set pin numbers:


// variables will change:

bool IR[] = {
  0,
  0,
  0,
  0,
  0,
  0
};
#define IR_90_IZQ 23
#define IR_90_DER 4

void setup() {
  Serial.begin(115200);
  // initialize the LED pin as an output:

  // initialize the pushbutton pin as an input:
  pinMode(IR_90_IZQ, INPUT);
  pinMode(IR_90_DER, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  IR[4] = digitalRead(IR_90_IZQ);
  IR[5] = digitalRead(IR_90_DER);

  if(IR[4] == LOW){
    Serial.println("90 DERECHA");
  }
  if(IR[5] == LOW){
    Serial.println("90 IZQUIERDA");   
  }
  delay(500);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:

}
