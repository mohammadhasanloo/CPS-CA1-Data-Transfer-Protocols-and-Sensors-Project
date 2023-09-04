#include <SoftwareSerial.h>
#include <Wire.h>

#define tx 2
#define rx 3
#define Addr 0x40
#define tempCMD 0xF3
#define humidityCMD 0xF5
#define out1 10
#define out2 9
#define STOP "*##%"
#define DUTY10 "*10%"
#define DUTY25 "*25%"

SoftwareSerial blueTH(rx,tx); //RX, TX

int blocked = true;

void setup() 
{
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  
  Serial.begin(9600);
  blueTH.begin(9600);

  Wire.begin();
}

void loop() 
{
  blocked = true;
  float temp = getTempValue();
  float humidity = getHumidityValue();
  sendData (temp, humidity);

  proccessResponseData();
  
  delay(4000); 
 
  
}

void proccessResponseData() {
  String response = readResponseData();
  Serial.print(response);
//  if (response.substring(0, 1) == "*" && response.substring(3, 4) == "%" ){
  sendDataToDC(response);
//  }
}

String readResponseData() {
  char buff[4];
  byte i=0;
  while (i < 4) {
//    if (blueTH.available() > 0) {
      buff[i] = blueTH.read();
      i++; //Only increment after something was received
      
//    }
   
  }
  
  return String(buff);
}

void sendDataToDC(String response){
  Serial.print("in dc");
  if(response == STOP) {
    analogWrite(out1, 0);
  }else if(response == DUTY10){
    analogWrite(out1, 25.4);
  }else if(response == DUTY25) {
    analogWrite(out1, 63.5);
  }
    
}

void sensorTransmission(int vale) {
  Wire.beginTransmission(Addr);
  Wire.write(vale);
  Wire.endTransmission();
  delay(500);
}


float getHumidityValue() {
  sensorTransmission(humidityCMD);
  //request
  unsigned int data[2];
  Wire.requestFrom(Addr, 2);
  if(Wire.available() == 2)  
  {    
    data[0] = Wire.read();    
    data[1] = Wire.read();
  }
  return (((data[0] * 256.0 + data[1]) * 125.0) / 65536.0) - 6;
}

float getTempValue() {
  sensorTransmission(tempCMD);
  //request
  unsigned int data[2];
  Wire.requestFrom(Addr, 2);
  if(Wire.available() == 2)  
  {    
    data[0] = Wire.read();    
    data[1] = Wire.read();
  }
  return (((data[0] * 256.0 + data[1]) * 175.72) / 65536.0) - 46.85;
}

void sendData (float temp,float humidity) {
  blueTH.print("*" + String(temp, 2) + "-" + String(humidity, 2) + "%");

}
