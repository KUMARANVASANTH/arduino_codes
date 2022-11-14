#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

long duration;
float distance;

int trigPin=9;
int echoPin=10;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();
  lcd.backlight();
  Wire.begin();
  Serial.begin(9600);
}
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = 0.034*duration/2;
  if(distance>=30)
  {
    lcd.setCursor(0,0);
    lcd.print("Note the sign board");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Go straight");
  }
  delay(1000);
}