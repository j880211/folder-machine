#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h> 
#include "DHT.h"
#define dhtType DHT11 //選用DHT11  
const int dhtPin=8; 
const int buttonPin=2;
const int LEDRpin = 3;
const int LEDGpin = 4;
const int LEDBpin = 6;
int buttonState=0;
int beforeState=0;
int state;
float h;
DHT dht(dhtPin, dhtType);
Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);  //設定LCD位置0x27,設定LCD大小為16*2
void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(buttonPin , INPUT);
  pinMode(A0, INPUT);
  pinMode(LEDRpin, OUTPUT);
  pinMode(LEDGpin, OUTPUT);
  pinMode(LEDBpin, OUTPUT);
  digitalWrite(LEDRpin, LOW);
  digitalWrite(LEDGpin, LOW);
  digitalWrite(LEDBpin, LOW);
  lcd.init(); //初始化LCD 
  lcd.backlight(); //開啟背光
  lcd.print("START"); //顯示Hello, World!
 
  
}
void loop()
{
   buttonState = digitalRead(buttonPin);
   switch(state){
    case 0:
      if(buttonState==0 && beforeState==1){
        Serial.println("Button Pressed");
        int pr = analogRead(A0);
        Serial.println(pr);
        if(pr<300){
          state = 1;
          Serial.println("Start sampling!");
          lcd.clear();
          lcd.print("Start sampling");
        }
        else{
          lcd.clear();
          lcd.print("No clothes");
          digitalWrite(LEDRpin, HIGH);
          digitalWrite(LEDGpin, LOW);
          digitalWrite(LEDBpin, LOW);
          delay(2000);
          digitalWrite(LEDRpin, LOW);
          digitalWrite(LEDGpin, LOW);
          digitalWrite(LEDBpin, LOW);
        }
      }
    break;
    case 1:
      delay(4000);
      h = dht.readHumidity();//讀取濕度
      Serial.print("濕度: ");
      Serial.print(h);
      lcd.clear();
      lcd.print(h); //顯示Hello, World!
      delay(4000);
      h = dht.readHumidity();//讀取濕度
      Serial.print("濕度: ");
      Serial.print(h);
      lcd.clear();
      lcd.print(h); //顯示Hello, World!
      delay(4000);
      h = dht.readHumidity();//讀取濕度
      Serial.print("濕度: ");
      Serial.print(h);
      lcd.clear();
      lcd.print(h); //顯示Hello, World!
      delay(1000);
      if(h>72){
        Serial.print("Too wet so back to state 0");
        lcd.clear();
        lcd.print("Too wet so back to state 0");
        digitalWrite(LEDRpin, HIGH);
        digitalWrite(LEDGpin, LOW);
        digitalWrite(LEDBpin, LOW);
        delay(2000);
        digitalWrite(LEDRpin, LOW);
        digitalWrite(LEDGpin, LOW);
        digitalWrite(LEDBpin, LOW);
        state=0;
      }
      else{
        Serial.print("Start folding");
        lcd.clear();
        lcd.print("Start folding");
        state=2;
        digitalWrite(LEDRpin, LOW);
        digitalWrite(LEDGpin, LOW);
        digitalWrite(LEDBpin, HIGH);
        delay(2000);
        digitalWrite(LEDRpin, LOW);
        digitalWrite(LEDGpin, LOW);
        digitalWrite(LEDBpin, LOW);
      }
    break;
    case 2:
      myservo.attach(12); // servo motor
      myservo.write(30);
      delay(1500.0);
      myservo.write( 180 );
      delay( 1500.0 );
      myservo.detach();
      myservo.attach(9); // servo motor
      myservo.write(150);
      delay(1500.0);
      myservo.write( 0 );
      delay( 1500.0 );
      myservo.detach();
      myservo.attach(5); // servo motor
      myservo.write(150);
      delay(1500.0);
      myservo.write( 0 );
      delay( 1500.0 );
      myservo.detach();  
      state=0;  
      lcd.clear();
      lcd.print("Finish folding");
    break;
   }  
   beforeState = buttonState;
}
