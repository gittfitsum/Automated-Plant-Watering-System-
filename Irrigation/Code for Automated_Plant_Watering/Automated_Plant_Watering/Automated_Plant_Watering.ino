
//***************AUTOMATED PLANT WATERING AND WATER LEVEL CONTROL FOR IRRIGATION SYSTEM WITH ARDUINO**************//
//*A PROJECT TO THE FEDERAL TECHNICAL AND VOCATIONAL EDUCATION AND TRAINING IINSTITUTE SCHOOL OF GRATUATE STUDENTS*//
//*IN PARTIAL FULFILMENT FOR THE DEGREE OF BACHELER OF SCINCE IN ELECTRONICS COMMUNICATION TECHNOLOGY MANAGEMENT*//
//**********************************************************************************************************//
//*Material Lists*//
// Arduino Uno(1)
// Soil Moisture Sensor(1)
// Ultrasonic Sensor/as A Waterlebel Sensor(1)
// 16x2 LCD display(1)
// Green LED(1)
// Yellow LED(1)
// Red LED(1)
// Piezo Buzzer(1)
// 2 Channel Relay(1)
// Resistors 100ohm (3)
// 12&5V Powersupply
//*June 2020 Addis Ababa*// 
//* Ethiopia*//
//************************//

// include the library code:
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Ultrasonic.h>
// Initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 6, en = 7, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int watersensorPin = A1; // Water Sensor input at Analog PIN A1
int moisturesensorPin = A0;//Moisture Sensor input at Analog PIN A0 

//Initialize variables 
int waterLevel;
int soilState;

// Arduino pins 
#define buzer 8
#define greenLed 9
#define yellowLed 10
#define redLed 11
#define farmValve 12
int tankPump = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzer, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(farmValve, OUTPUT);
  pinMode(tankPump, OUTPUT);
  digitalWrite(tankPump, HIGH); //pump switched ON
  digitalWrite(farmValve, LOW);
  digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, LOW);

  // Set up the LCD's number of columns and rows:
  lcd.clear();
  Serial.println("AUTOMATED PLANT WATERING SYSTEM AND ");
  Serial.println("WATER LEVEL CONTROL FOR IRRIGATION");
  lcd.begin(16, 2);
  lcd.print("AUTOMATED PLANT");
  lcd.setCursor(0, 1);
  lcd.print("WATERING SYSTEM.");
  delay(1000);
  lcd.clear();
  Serial.println("CHECKING STATUS...");
  lcd.print("CHECKING STATUS.");
  lcd.setCursor(0, 1);
  lcd.print(".............");
  delay(500);
}
void loop() {

  // put your main code here, to run repeatedly:
  waterLevel = analogRead(watersensorPin);
  soilState = analogRead(moisturesensorPin);
  Serial.print("Water Level Reading:");
  Serial.println(waterLevel);
  Serial.print("Moisture Sensor Reading:");
  Serial.println(soilState);

  if (waterLevel == LOW) {
    lcd.clear();
    lcd.print("Water Tank Low");
    Serial.println("Water In The Tank Gets Low");
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(tankPump, HIGH); //Tank pump switched ON
    Serial.println("Tank Pump Switched ON");
    delay(500);
    waterLevel = analogRead(watersensorPin);
    lcd.clear();
  }
  else {
    lcd.clear();
    lcd.print("WTank Level Okay.");
    Serial.println("Water In the Tank Okay");
    digitalWrite(tankPump, LOW); //Tank pump switched OFF
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    Serial.println("Tank Pump Switched OFF");
    delay(500);
    lcd.clear();
  }
  if (soilState <= 170) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Loggy Soil");
    Serial.println("Loggy Soil");
    digitalWrite(farmValve, LOW); //farm Valve switched OFF
    Serial.println("Farm Valve Switched OFF");
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    delay(500);
    soilState = analogRead(moisturesensorPin);
    lcd.clear();
  }
  if ((soilState >= 200) && (soilState <= 350) ) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Wet Soil");
    Serial.println("Wet Soil");
    digitalWrite(farmValve, LOW); //farm Valve switched OFF
    Serial.println("Farm Valve Switched OFF");
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    delay(500);
    soilState = analogRead(moisturesensorPin);
    lcd.clear();
  }
  if (soilState > 600) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("No Moisture");
    Serial.println("No Soil Moisture, Soil Dry");
    digitalWrite(farmValve, HIGH); //farm valve Switched ON
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    Serial.println("Farm Valve Switched ON");
    delay(500);
    soilState = analogRead(moisturesensorPin);
    lcd.clear();
  }
  if ((soilState >= 351) && (soilState <= 580) ) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Moist Soil");
    Serial.println("Moist Soil, Water Moisture Okay");
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    soilState = analogRead(moisturesensorPin);

  }
  if ((waterLevel == LOW) && (soilState <= 300)) {
    lcd.clear();
    lcd.print("System  OK");
    Serial.println("System OK ");
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(farmValve, LOW); // Farm Irrigation Valve Switched OFF
    digitalWrite(tankPump, LOW); //Tank pump switched OFF
    Serial.println("Farm Valve Switched OFF");
    Serial.println("Tank Valve Switched OFF");

  }
  if ((soilState > 600) && (waterLevel == LOW)) {
    lcd.clear();
    lcd.print("Soil Water LOW");
    Serial.println("Soil Water Low");
    lcd.setCursor(0, 1);
    lcd.print("Tank Empty");
    Serial.println("Tank Empty");
    digitalWrite(buzer, HIGH);//Buzzer Swiched ON
    digitalWrite(greenLed, LOW);//Turn OFF Green LED
    digitalWrite(redLed, HIGH);//Turn ON Red LED
    digitalWrite(farmValve, HIGH);// Farm Irrigation Valve Switched ON
    digitalWrite(tankPump, HIGH);//Tank pump switched ON
    Serial.println("Farm Valve Switched ON");
    Serial.println("Tank Valve Switched ON");
    digitalWrite(yellowLed, LOW);
    delay(500);
    digitalWrite(buzer, LOW);

    waterLevel =analogRead(watersensorPin);
    soilState = analogRead(moisturesensorPin);
    lcd.clear();
  }
  //end
  waterLevel = analogRead(watersensorPin);
  soilState = analogRead(moisturesensorPin);
  lcd.clear();
  lcd.print("AUTOMATED PLANT");
  lcd.setCursor(0, 1);
  lcd.print("WATERING SYSTEM.");
}
