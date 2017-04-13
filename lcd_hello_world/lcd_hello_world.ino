#include <LiquidCrystal.h>
#include <LCDKeypad.h>
//LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LCDKeypad lcd;
void setup() {
  lcd.begin(16, 2);
}
void loop() {
  lcd.setCursor(0,0);
  lcd.println("Hello, World!   ");
  lcd.setCursor(0,1);
  lcd.println("Ok!             ");
  delay(100);
}
