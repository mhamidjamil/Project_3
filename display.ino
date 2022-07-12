#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
 
 lcd.begin(16, 2);
 
}

void loop() {
 
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello Hackster");
  lcd.setCursor(0, 1);
  lcd.print("Value : ");
  lcd.setCursor(10, 1);
  lcd.print(analogRead(A0));
  Serial.println(analogRead(A0));
delay(500);
}