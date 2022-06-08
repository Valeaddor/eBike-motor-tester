#include <LCD_I2C.h>

LCD_I2C lcd(0x3F);

const byte hALED = 2;
const byte hBLED = 3;
const byte hCLED = 4;
byte LED, check60, check120 = 0;
byte holl,hollA,hollB,hollC = 0;
boolean checkOn = false;

void setup () {

  pinMode(hALED,OUTPUT);
  pinMode(hBLED,OUTPUT);
  pinMode(hCLED,OUTPUT);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);

  lcd.begin();
  lcd.backlight();

  // sets the LCD's rows and colums:
  lcd.clear();  
  lcd.home();

  lcd.print("A B C");

}


void loop () {

  holl = digitalRead(A0);
  if(holl != hollA) {
    if(holl == LOW) LED = 1;
    else LED = 0;
    ShowLed(hALED);
    hollA = holl;
  };

  holl = digitalRead(A1);
  if(holl != hollB) {
    if(holl == LOW) LED = 1;
    else LED = 0;
    ShowLed(hBLED);
    hollB = holl;
  };
  
  holl = digitalRead(A2);
  if(holl != hollC) {
    if(holl == LOW) LED = 1;
    else LED = 0;
    ShowLed(hCLED);
    hollC = holl;
  };

  if(hollA == LOW && hollB == LOW && hollC == LOW) {
    if(!checkOn) {
      if(check60 >= 99) check60 = 1; else check60++;
      lcd.setCursor(9, 0);
      lcd.print("60%    ");
      lcd.setCursor(14, 0);
      lcd.print(check60);
      checkOn = true;
    }
  } else if (hollA == HIGH && hollB == LOW && hollC == HIGH) {
    if(!checkOn) {
      if(check120 >= 99) check120 = 1; else check120++;
      lcd.setCursor(9, 1);
      lcd.print("120%   ");
      lcd.setCursor(14, 1);
      lcd.print(check120);
      checkOn = true;
    };
  } else {
    checkOn = false;
  }
  
}

void ShowLed(byte hLED) {


  lcd.setCursor((hLED - 2) * 2, 1);
  lcd.print(LED);
  lcd.print(" ");
  
  if(LED == 1) digitalWrite(hLED,HIGH); 
    else digitalWrite(hLED,LOW);
  
}
