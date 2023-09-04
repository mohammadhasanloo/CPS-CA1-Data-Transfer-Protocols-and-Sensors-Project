#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#define tx 1
#define rx 0
#define STOP "*##%"
#define DUTY10 "*10%"
#define DUTY25 "*25%"

SoftwareSerial blueMain(rx, tx); // RX, TX

////create LCD
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float humidityValue = 0;
float tempValue = 0;
String data;

void setup()
{
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  Serial.begin(9600);
  blueMain.begin(9600);

  // LCD
  lcd.begin(16, 2);
  lcd.print("Starting...");
}
void loop()
{
  readDataSensor();
}

void readDataSensor()
{

  char buff[13];
  // Get data from TH

  byte i = 0;
  while (i < 13)
  {
    if (Serial.available() > 0)
    {
      buff[i] = Serial.read();
      i++; // Only increment after something was received
    }
    // i++; Not here!
  }
  int j = 0;
  while (j < 13)
  {
    Serial.print(buff[j]);
    j++;
  }
  Serial.println("");

  char temp[10];
  char humadity[10];
  if (buff[0] == '*' && buff[12] == '%')
  {
    tempValue = atof(strncpy(temp, buff + 1, 5));
    humidityValue = atof(strncpy(humadity, buff + 7, 5));
    processData();
  }
}

void processData()
{

  createOutput();
  LCDShowSensorValues();
  sendData();
}

void LCDShowSensorValues()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println(String(tempValue));
  lcd.println(String(humidityValue));
  lcd.println(data);
}

void createOutput()
{
  if (humidityValue > 30)
  {
    data = STOP;
  }
  else if (humidityValue < 10)
  {
    data = DUTY25;
  }
  else if ((10 <= humidityValue) && (humidityValue <= 20))
  {
    data = DUTY20;
  }
  else if ((20 <= humidityValue) && (humidityValue <= 30))
  {
    if (tempValue < 25)
    {
      data = STOP;
    }
    else
    {
      data = DUTY10;
    }
  }
}

void sendData()
{
  Serial.print(data);
}
