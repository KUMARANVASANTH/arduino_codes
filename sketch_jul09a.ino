int trig =11;
int echo= 10;
long duration;
int distance;
int buzzer=12;
void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(5);
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration*0.034/2;
  if(distance<=5)
  {
    tone(buzzer,900);
    printf("%d",distance);
  }
  else
  {
    noTone(buzzer);
  }
}
