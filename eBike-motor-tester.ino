//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

#include <LCD_I2C.h>

LCD_I2C lcd(0x3F); // Default address of most PCF8574 modules, change according


// loop counter
int count = 0;
unsigned int holl,hollA,hollB,hollC = 0;
const byte hALED = 2;
const byte hBLED = 3;
const byte hCLED = 4;
byte LED = 0;


void setup () {

  pinMode(hALED,OUTPUT);
  pinMode(hBLED,OUTPUT);
  pinMode(hCLED,OUTPUT);
//  Serial.begin(57600);
//  Wire.begin();
//  lcd.init();                      // initialize the lcd 
  lcd.begin();
  lcd.backlight();
  lcd.home();

  // sets the LCD's rows and colums:
  lcd.clear();  

  lcd.print("A B C");
  lcd.setCursor(0, 1);
  lcd.print("0 0 0");


}


void loop () {

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);

  holl = analogRead(A0);
  if(holl != hollA) {
    if(holl < 512) LED = 0;
    else LED = 1;
    lcd.setCursor(0, 1);
    ShowLed(hALED);
    hollA = holl;
  };

  holl = analogRead(A1);
  if(holl != hollB) {
    if(holl < 512) LED = 0;
    else LED = 1;
    lcd.setCursor(2, 1);
    ShowLed(hBLED);
    hollB = holl;
  };
  
  holl = analogRead(A2);
  if(holl != hollC) {
    if(holl < 512) LED = 0;
    else LED = 1;
    lcd.setCursor(4, 1);
    ShowLed(hCLED);
    hollC = holl;
  };

  if(hollA==0 && hollB==0 && hollC==0) {
    lcd.setCursor(10, 0);
    lcd.print("60% ");
  } else if ((hollA>511 && hollB==0 && hollC>512)||(hollA==0 && hollB>511 && hollC==0)) {
    lcd.setCursor(10, 1);
    lcd.print("120%");    
  };
  
  lcd.setCursor(12, 0);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  
  

}

void ShowLed(byte hLED) {

  lcd.print(LED);
  lcd.print(" ");
  
  if(LED == 1) digitalWrite(hLED,HIGH); 
    else digitalWrite(hLED,LOW);
  
}
