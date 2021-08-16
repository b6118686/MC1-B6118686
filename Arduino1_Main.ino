//Main Arduino
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
char senddata = 'X';

#include <IRremote.h>
int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(3, OUTPUT);

  Wire.begin(7);                // join i2c bus with address #7
  Wire.onRequest(requestEvent); // register event
}

void loop()
{ 
  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
    
    if (results.value == 16582903){// 1-A
     digitalWrite(13, 1);
     analogWrite(12, 0);
     analogWrite(11, 0);
     senddata = 'A';
      requestEvent();
    }
    else if (results.value == 16615543){//2-B
     digitalWrite(12, 1);
     analogWrite(13, 0);
     analogWrite(11, 0);
     senddata = 'B';
      requestEvent();
    }
    else if (results.value == 16599223){//3-C
     digitalWrite(11, 1);
     analogWrite(12, 0);
     analogWrite(13, 0);
     senddata = 'C';
      requestEvent();
    }
    else if (results.value == 16580863){//3-C
     analogWrite(11, 0);
     analogWrite(12, 0);
     analogWrite(13, 0);
     senddata = 'X';
     requestEvent();
    }else{
      requestEvent();
    }
    
    irrecv.resume(); // Receive thxt value
  }
  delay(100);
  display();
}

void requestEvent() { 
  Wire.write(senddata);
  Serial.println("senddata : "+String(senddata));
  delay(100);
}

void display(){
  if(senddata == 'X'){
  	lcd.begin(16, 2);                                                 //กำหนดขนาดของจอ columns และ rows
  	lcd.setCursor(1, 0); 
  	lcd.print("Select display");                      //กำหนดข้อความที่ต้องการแสดงผล
  	lcd.setCursor(0, 1);                                        //กำหนดตำแหน่ง Cursor
  	lcd.print("Press the switch");
  }else if(senddata == 'A'){
    lcd.begin(16, 2);
  	lcd.setCursor(2, 0);
    lcd.print("Send Value :");
  	lcd.setCursor(0, 1);
  	lcd.print(">>Force Sensor");
  }else if(senddata == 'B'){
    lcd.begin(16, 2);
  	lcd.setCursor(2, 0);
    lcd.print("Send Value :");
  	lcd.setCursor(0, 1);
  	lcd.print(">>Photoresistor");
  }else if(senddata == 'C'){
    lcd.begin(16, 2);
  	lcd.setCursor(2, 0);
    lcd.print("Send Value :");
  	lcd.setCursor(0, 1);
  	lcd.print(">>Temperature");
  }
}