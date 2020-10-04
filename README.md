# folder-machine-code implementation
首先，我們會對溫溼度感測器、button、RGB、LCD進行初始化的動作。
  void setup()
  
接著，在switch的前面，每進到一次loop()中，我們都會去記得現在的buttonState，並且在switch的後面，也會把這次的buttonState給beforeState，以方便之後判斷button是在甚麼時候被按下。
  buttonState = digitalRead(buttonPin);
  switch(state){

  }
  beforeState = buttonState;
  
而在case 0的時候，這時候會去偵測button是否有被按下，如果被按下的話，就會開始去偵測光敏電阻的值，而我在測試的時候發現當有衣服遮在上面的話，光敏電阻的值一定會小於300，因此在之後每一次只要值小於300的話，就代表上面是有擺衣服的，而當上面是有擺衣服的話，就讓它進到state 1，並且在LCD上顯示”Start sampling”，而如果沒有的話，RGB就會亮紅燈，並且在LCD上顯示”No Clothes”，並且留在state 0，等待下一次button 被按下去的時候。
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
  }

而一進到state 1的時候，會每隔四秒量一次它的溼度，總共量三次，並且顯示在LCD上，而為甚麼要隔四秒量三次的原因是因為如果只量第一次的話，怕會被上一次偵測的值影響，像是上一件偵測的是一件溼的衣服。
    case 1:
      delay(4000);
      h = dht.readHumidity();//讀取濕度
      Serial.print("濕度: ");
      Serial.print(h);
      lcd.clear();
      lcd.print(h);
      delay(4000);
      h = dht.readHumidity();//讀取濕度
      Serial.print("濕度: ");
      Serial.print(h);
      lcd.clear();
      lcd.print(h);
      delay(4000);
      h = dht.readHumidity();//讀取濕度
      Serial.print("濕度: ");
      Serial.print(h);
      lcd.clear();
      lcd.print(h);
      delay(1000);

而假設在最後一次量的溼度是小於一定的值的話(濕度可能要視當天的情況而定)，則代表這件衣服已經乾了，這時候機器就可以準備開始進行折衣服的動作，並且亮起RGB的藍燈和把state設成2，而假設是大於一定的值的話，就代表這件衣服還有一點溼，現在就把它折起來不太適合，因此這時候會亮起RGB的紅燈，並且在LCD上顯示”Too wet so back to state 0”。
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

而在state 2時，就會開始進行伺服馬達折衣服的動作，並且在三個伺服馬達都完成後，在LCD上顯示”Finish folding”。
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

