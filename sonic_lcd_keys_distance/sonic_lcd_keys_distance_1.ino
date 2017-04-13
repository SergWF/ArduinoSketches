#include <LiquidCrystal.h>
#include <LCDKeypad.h>
#include <DFR_Key.h>

LCDKeypad lcd;
DFR_Key keypad;
// defines pins numbers
const int trigPin = 13;
const int echoPin = 12;
int trying = 0;
long distance = -1;
int btn = -1;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  lcd.begin(16, 2);
}

void loop() {
  int pressedBtn = keypad.getKey();
  if (pressedBtn  > 0) {
    btn = pressedBtn;
    show(getDistance(), pressedBtn);
  }



  lcd.setCursor(0, 1);
  lcd.println("Press any button");
  delay(100);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}

void show(long duration, int trying) {
  int distanceCm = duration * 0.034 / 2;
  lcd.setCursor(0, 0);
  lcd.print(trying);
  lcd.print(": ");
  lcd.print(distanceCm);
  lcd.print("cm ");
}

void showStartMessage() {
  lcd.setCursor(0, 0);
  lcd.println("Waiting!        ");
}


