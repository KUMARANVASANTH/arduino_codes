#include<ESP8266WiFi.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int trigPin=16;
int echoPin=2;
int buzz=0;
long duration;
float distance;
String api="7C65MPEBCGHRHBS0";
const char *ssid = "OPPO A53";
const char *pass = "20032003";
const char *server="api.thingspeak.com";
WiFiClient client;

void setup() {
  //Serial.begin(115200);
  //lcd.begin();
  lcd.backlight();
  delay(10);
  Serial.println("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
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

    if(distance<=20)
    {
      tone(buzz,300);
      lcd.setCursor(0, 0);
      lcd.print("Detect the sign board");
      lcd.setCursor(0, 1);
      lcd.print("Distance:");
      lcd.print(distance);
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print(" Go Straight ");
      lcd.setCursor(0, 1);
      lcd.print("Distance:");
      lcd.print(distance);
    }


    Serial.print("distance: ");
    Serial.print(distance);
    Serial.print("\n");
  }
  client.stop();
  Serial.println("waiting..");
  delay(1000);
}
