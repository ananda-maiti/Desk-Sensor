#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor1;
VL53L0X sensor2;
// VL53L0X sensor3;
// VL53L0X sensor4;

#define LONG_RANGE

#define S1_PORT 6
#define S2_PORT 4
// #define S3_PORT 5
// #define S4_PORT 6

char txt[1000];
int DISTANCE_FWD;

void setup()
{

  pinMode(S1_PORT, OUTPUT);
  pinMode(S2_PORT, OUTPUT);
  // pinMode(S3_PORT, OUTPUT);
  // pinMode(S4_PORT, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  
  digitalWrite(S1_PORT, LOW);
  digitalWrite(S2_PORT, LOW);
  // digitalWrite(S3_PORT, LOW);
  // digitalWrite(S4_PORT, LOW);

  
  digitalWrite(LED_BUILTIN, LOW);

  delay(500);
  Wire.begin();


  Serial.begin (115200);

  //SENSOR 1
  pinMode(S1_PORT, INPUT);
  delay(150);
  sensor1.init(true);
  delay(100);
  sensor1.setAddress((uint8_t) 22);

  //SENSOR 2
  pinMode(S2_PORT, INPUT);
  delay(150);
  sensor2.init(true);
  delay(100);
  sensor2.setAddress((uint8_t) 25);

  // //SENSOR 3
  // pinMode(S3_PORT, INPUT);
  // delay(150);
  // sensor3.init(true);
  // delay(100);
  // sensor3.setAddress((uint8_t) 28);

  // //SENSOR 4
  // pinMode(S4_PORT, INPUT);
  // delay(150);
  // sensor4.init(true);
  // delay(100);
  // sensor4.setAddress((uint8_t) 31);
  
//  Serial.println("");
//  Serial.println("addresses set");
//  Serial.println("");
//  Serial.println("");



  sensor1.setTimeout(500);
  sensor2.setTimeout(500);
  // sensor3.setTimeout(500);
  // sensor4.setTimeout(500);

  
  
#if defined LONG_RANGE
  sensor1.setSignalRateLimit(0.1);
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  
  sensor2.setSignalRateLimit(0.1);
  sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  
  // sensor3.setSignalRateLimit(0.1);
  // sensor3.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  // sensor3.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);

  // sensor4.setSignalRateLimit(0.1);
  // sensor4.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  // sensor4.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);  
#endif

}

void loop() {
  
  //CHECK DISTANCES
  memset(txt, '\0', 1000);  
  //sprintf(txt + strlen(txt), "%s", ">");

  //FWD OR SENSOR
  if (sensor1.timeoutOccurred())  {
  }
  else  {
   DISTANCE_FWD = sensor1.readRangeSingleMillimeters();
   sprintf(txt + strlen(txt), "%d", DISTANCE_FWD);// Serial.print(DISTANCE_FWD);
  }

  sprintf(txt + strlen(txt), "%s", " ");

  //FLT OR SENSOR2
  if (sensor2.timeoutOccurred()) {
  }
  else  {
   sprintf(txt + strlen(txt), "%d", sensor2.readRangeSingleMillimeters());// Serial.print(DISTANCE_FLT);
  }

  sprintf(txt + strlen(txt), "%s", " ");
    
  // //FRT OR SENSOR3
  // if (sensor3.timeoutOccurred())  {
  // }
  // else  {
  //  sprintf(txt + strlen(txt), "%d", sensor3.readRangeSingleMillimeters());// Serial.print(DISTANCE_FRT);
  // }

  // sprintf(txt + strlen(txt), "%s", " ");
  
  // //FRT OR SENSOR4
  // if (sensor4.timeoutOccurred())  {
  // }
  // else  {
  //  sprintf(txt + strlen(txt), "%d", sensor4.readRangeSingleMillimeters());// Serial.print(DISTANCE_FRT);
  // }
  
  Serial.print(txt);
  //Serial.print(";");
  Serial.println();

  // if(DISTANCE_FWD > 1000) {
  //   digitalWrite(LED_BUILTIN, HIGH);
  // }
  // else {
  //   digitalWrite(LED_BUILTIN, LOW);
  // }
  
  delay(10);//can change to a lower time like 100
}
