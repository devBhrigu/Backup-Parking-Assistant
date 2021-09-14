#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

const int ledPin = 9; 
const int echoPin = 4; 
const int trigPin = 5; 
const int buzzerPin = 11; 
const long LCD = 1000; 
long alert = -1; 

unsigned long previousMillisL = 0; 
unsigned long previousMillisA = 0; 

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() 
{ 
  lcd.begin(); 
  lcd.backlight(); 
  pinMode(ledPin, OUTPUT); 
  pinMode(buzzerPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(trigPin, OUTPUT); 
}

void loop() 
{ 
  float distancevalue = readSensorData(); 
  unsigned long currentMillisL = millis(); 

  if(currentMillisL - previousMillisL >= LCD) 
  { 
    previousMillisL = currentMillisL; 
    lcdPrint(distancevalue); 
  }

 distancejudgement(distancevalue); 

 if(alert != 1) 
 { 
  unsigned long currentMillisA = millis(); 
  if (currentMillisA - previousMillisA >= alert) 
  {
    previousMillisA = currentMillisA; 
    alertwork();
  }
 }
}

void alertwork() 
{ 
  digitalWrite(ledPin, HIGH); 
  tone(11, 400, 100); 
  delay(10); 
  digitalWrite(ledPin, LOW);   
}

void lcdPrint(float distance) 
{
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Distance is: "); 
  lcd.setCursor(9,0); 
  lcd.print(distance); 
} 

float readSensorData(void)
{ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  float distance = pulseIn(echoPin, HIGH)/58.00; 
  return distance;  
}

void distancejudgement(float distance) 
{ 
  
  if (distance <=5) 
  { 
    alert = 300; 
  }

  else if (distance <=10)
  { 
    alert = 800; 
  }

  else if (distance <= 20)
  { 
    alert = 1500; 
  }

  else if (distance <= 2) 
  { 
    alert = 50; 
  }
  else 
  { 
   alert = -1;  
  }
}
