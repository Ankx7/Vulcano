#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup(){
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while(! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test" );
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  // pass in 'true' to get debug data printout!
/*
  if (measure.RangeStatus != 4 && measure.RangeMilliMeter < 1000) {
    // phase failures have incorrect data
    Serial.println("hay ana");
  }  
  */
  Serial.println( measure.RangeMilliMeter);
}
