//Sender - Receiv
#include <Wire.h>
#include <LiquidCrystal.h>
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define E 8
#define RS 9
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
void display();
char senddata[6];
char receiv = 'X';
float forcesen = 0;
float photoresistor = 0;
float tmp36 = 0;
float tmp36_1 = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onRequest(requestEvent); // register event
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
}
void loop() {
  
  forcesen = analogRead(A0);
  photoresistor = analogRead(A1);
  tmp36 = analogRead(A2);
  
  Wire.requestFrom(7, 6);    // request 6 bytes from slave device #8
  if (Wire.available()>0) { // slave may send less than requested
    receiv = Wire.read(); // receive a byte as character
    Serial.println("receiv = "+String(receiv));
  }
  delay(100);
  display();
  requestEvent();
}

void requestEvent() {
  if(receiv == 'C'){
    dtostrf(tmp36, 4, 0, senddata);
  }else{
    dtostrf(tmp36_1, 4, 0, senddata);
  }
  Wire.write(senddata);
  Serial.println("senddata : "+String(receiv)+" "+String(senddata));
  delay(100);
}

void display(){
  if(receiv == 'X'){
  	lcd.begin(16, 2);                                                 //กำหนดขนาดของจอ columns และ rows
  	lcd.setCursor(0, 0); 
  	lcd.print("Wellcome Arduino");                      //กำหนดข้อความที่ต้องการแสดงผล
  	lcd.setCursor(0, 1);                                        //กำหนดตำแหน่ง Cursor
  	lcd.print(">>Wait Data");
  }else if(receiv == 'A'){
    lcd.begin(16, 2);
  	lcd.setCursor(0, 0);
    lcd.print(">>Force Sensor");
  	lcd.setCursor(0, 1);
  	lcd.print(">>"+String(forcesen,0));
  }else if(receiv == 'B'){
    lcd.begin(16, 2);
  	lcd.setCursor(0, 0);
    lcd.print(">>Photoresistor");
  	lcd.setCursor(0, 1);
  	lcd.print(">>"+String(photoresistor,0));
  }else if(receiv == 'C'){
    lcd.begin(16, 2);
  	lcd.setCursor(0, 0);
    lcd.print(">>Temperature");
  	lcd.setCursor(0, 1);
  	lcd.print(">>"+String(tmp36,0));
  }
}
  