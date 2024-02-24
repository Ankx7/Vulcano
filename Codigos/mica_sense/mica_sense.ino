//Sensores de mica andando

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
