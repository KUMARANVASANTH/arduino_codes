#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<ESP8266WiFi.h>

String api="7C65MPEBCGHRHBS0";
const char *ssid="OPPO A53";
const char *pass="20032003";
const char *server="api.thingspeak.com";
WiFiClient client;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

int trigPin=0;
int echoPin=2;
long duration;
float distance;

void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("");
  Serial.print("WiFi connected");
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*0.034)/2;
  if(client.connect(server,80))
  {
    String postStr= api;
    postStr+="&field1=";
    postStr+=String(distance);
    postStr+="\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY:"+api+"\n");
    client.print("conten-type: application/x-www-form-urlencoded\n");
    client.print("content-length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    if(distance<=30)
    {
      lcd.setCursor(0, 0);
      lcd.print("Detect the sign");
      lcd.setCursor(0, 1);
      lcd.print("board");
      delay(1000);
      lcd.clear();
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print(" Go Straight ");
      delay(1000);
      lcd.clear();
    }


    Serial.print("distance: ");
    Serial.print(distance);
    Serial.print("\n");
  }
}
