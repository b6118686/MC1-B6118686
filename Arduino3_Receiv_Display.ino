//Receiv
#include <Wire.h>
float val;
float temp = 0;
int light = 0;
void setup() {
  
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A0, INPUT);
}
 
void loop() {
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8
  if (Wire.available()>0) { // slave may send less than requested
  	String receiv = Wire.readString(); // receive a byte as character
    val = receiv.toFloat();
    Serial.println("receiv = "+String(receiv));
    Serial.println("Check val = "+String(val));         // print the character
    if (val>19){
      temp = map(val,20,358,-40,125);
    }else{
      temp = -99;
    }
  }
  if (temp>-41){
    light = map(analogRead(A0),0,1024,0,255);
    if(temp>=-40 && temp<1){
      analogWrite(10,light);
      analogWrite(11,0);
      analogWrite(12,0);
      analogWrite(13,0);
      noTone(8);
    }else if(temp>=1 && temp<41){
      analogWrite(11,light);
      analogWrite(10,0);
      analogWrite(12,0);
      analogWrite(13,0);
      noTone(8);
    }else if(temp>=41 && temp<81){
      analogWrite(11,0);
      analogWrite(10,0);
      analogWrite(12,light);
      analogWrite(13,0);
      noTone(8);
    }else if(temp>=81 && temp<126){
      analogWrite(11,0);
      analogWrite(10,0);
      analogWrite(12,0);
      analogWrite(13,light);
      tone(8, 1500, 100);
    }
  }else{
    analogWrite(11,0);
    analogWrite(10,0);
    analogWrite(12,0);
    analogWrite(13,0);
  }
}