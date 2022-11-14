int trigPin=8;
int echoPin=9;
int ledPin=6;

long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //digitalWrite(ledPin,HIGH);
  digitalWrite(trigPin, LOW);
  delay(10);
  digitalWrite(trigPin, HIGH);
  delay(15);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (0.034*duration)/2;
  Serial.print(distance);
  if(distance<=30)
  {
    for(int i=255;i>=30;i--)
    {
      analogWrite(ledPin, i);
      delay(30);
    }
  }
  else
  {
    //continue;
    digitalWrite(ledPin, HIGH); 
  }
  delay(1000);
}
