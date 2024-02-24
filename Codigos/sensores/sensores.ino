#include "Adafruit_VL53L0X.h"
#include <Adafruit_NeoPixel.h>

#define PIN        13

#define NUMPIXELS 16

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x31
#define LOX2_ADDRESS 0x29

// set the pins to shutdown
#define SHT_LOX1          15
#define SHT_LOX2          2

#define IR_90_IZQ         23
#define IR_90_DER         4

#define IR_45_IZQ         18
#define IR_CTR            5
#define IR_45_DER         19

#define DER_90            7
#define IZQ_90            6

#define MEDIO_45_DER      5
#define MEDIO_45_IZQ      4

#define ADELANTE_45_DER   3
#define CTR               2
#define ADELANTE_45_IZQ   1
// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;

int distance1, distance2;

bool IR[] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

/*
    Reset all sensors by setting all of their XSHUT pins low for delay(10), then set all XSHUT high to bring out of reset
    Keep sensor #1 awake by keeping XSHUT pin high
    Put all other sensors into shutdown by pulling XSHUT pins low
    Initialize sensor #1 with lox.begin(new_i2c_address) Pick any number but 0x29 and it must be under 0x7F. Going with 0x30 to 0x3F is probably OK.
    Keep sensor #1 awake, and now bring sensor #2 out of reset by setting its XSHUT pin high.
    Initialize sensor #2 with lox.begin(new_i2c_address) Pick any number but 0x29 and whatever you set the first sensor to
*/
void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);

  // initing LOX1
  if (!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if (!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1);
  }
}

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);

  Serial.println(F("Shutdown pins inited..."));

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);

  Serial.println(F("Both in reset mode...(pins are low)"));

  pinMode(IR_90_IZQ, INPUT);
  pinMode(IR_90_DER, INPUT);
  pixels.begin();

  Serial.println(F("Starting..."));
  setID();

}

void loop() {


  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!

  //CENTRAL
  //pixels.clear();
  //pixels.setPixelColor(7, pixels.Color(20, 0, 0));
  //pixels.setPixelColor(8, pixels.Color(20, 0, 0));
  //pixels.setPixelColor(9, pixels.Color(20, 0, 0));

  //45 IZQUIERDA
  //pixels.setPixelColor(6, pixels.Color(0, 20, 0));
  //45 ATRAS IZQUIERDA
  //pixels.setPixelColor(5, pixels.Color(0, 0, 20));
  //90 IZQUIERDA
  //pixels.setPixelColor(4, pixels.Color(20, 20, 0));


  //45 DERECHA
  //pixels.setPixelColor(10, pixels.Color(0, 20, 0));
  //45 ATRAS DERECHA
  //pixels.setPixelColor(11, pixels.Color(0, 0, 20));
  //90 DERECHA
  //pixels.setPixelColor(12, pixels.Color(20, 20, 0));





  //pixels.show();

  if (measure1.RangeStatus != 4) {    // if not out of range
    distance1 = measure1.RangeMilliMeter;
  }
  if (measure2.RangeStatus != 4) {
    distance2 = measure2.RangeMilliMeter;
  }

  if (distance1 < 700) {
    IR[MEDIO_45_DER] = HIGH;
  } else {
    IR[MEDIO_45_DER] = LOW;
  }
  if (distance2 < 700) {
    IR[MEDIO_45_IZQ] = HIGH;
  } else {
    IR[MEDIO_45_IZQ] = LOW;
  }
  IR[ADELANTE_45_IZQ] = !digitalRead(IR_45_IZQ);
  IR[CTR] = !digitalRead(IR_CTR);
  IR[ADELANTE_45_DER] = !digitalRead(IR_45_DER);
  IR[IZQ_90] = !digitalRead(IR_90_IZQ);
  IR[DER_90] = !digitalRead(IR_90_DER);

  pruebaSensores();
  /*
  for (int i = 0; i < 8; i++) {
    Serial.print(IR[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
  Serial.println();
  delay(100)*/
}

void pruebaSensores() {

  if (IR[DER_90] == HIGH) {
    pixels.setPixelColor(12, pixels.Color(20, 20, 0));
    pixels.show();
  } else {
    pixels.setPixelColor(12, pixels.Color(0, 0, 0));
    pixels.show();
  }

  if (IR[IZQ_90] == HIGH) {
    pixels.setPixelColor(4, pixels.Color(20, 20, 0));
    pixels.show();
  } else {
    pixels.setPixelColor(4, pixels.Color(0, 0, 0));
    pixels.show();
  }

  if (IR[MEDIO_45_DER] == HIGH) {
    pixels.setPixelColor(11, pixels.Color(0, 0, 20));
    pixels.show();
  } else {
    pixels.setPixelColor(11, pixels.Color(0, 0, 0));
    pixels.show();
  }

  if (IR[MEDIO_45_IZQ] == HIGH) {
    pixels.setPixelColor(5, pixels.Color(0, 0, 20));
    pixels.show();
  } else {
    pixels.setPixelColor(5, pixels.Color(0, 0, 0));
    pixels.show();
  }

  if (IR[ADELANTE_45_DER] == HIGH) {
    pixels.setPixelColor(10, pixels.Color(0, 20, 0));
    pixels.show();
  } else {
    pixels.setPixelColor(10, pixels.Color(0, 0, 0));
    pixels.show();
  }

  if (IR[ADELANTE_45_IZQ] == HIGH) {
    pixels.setPixelColor(6, pixels.Color(0, 20, 0));
    pixels.show();
  } else {
    pixels.setPixelColor(6, pixels.Color(0, 0, 0));
    pixels.show();
  }

  if (IR[CTR] == HIGH) {
    pixels.setPixelColor(7, pixels.Color(20, 0, 0));
    pixels.setPixelColor(8, pixels.Color(20, 0, 0));
    pixels.setPixelColor(9, pixels.Color(20, 0, 0));
    pixels.show();
  } else {
    pixels.setPixelColor(7, pixels.Color(0, 0, 0));
    pixels.setPixelColor(8, pixels.Color(0, 0, 0));
    pixels.setPixelColor(9, pixels.Color(0, 0, 0));
    pixels.show();
  }
}
