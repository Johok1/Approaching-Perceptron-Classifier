const int ledPin = 4;
const int onPin = 2;
const int PIR_outputPin = 6;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(onPin, INPUT);
  pinMode(PIR_outputPin, INPUT); 
  blinkLED();
}

void loop(){
  delay(400);
  if(digitalRead(onPin) == HIGH){
    if(digitalRead(PIR_outputPin) == HIGH){
      digitalWrite(ledPin, HIGH);
    }else{
      digitalWrite(ledPin, LOW); 
    }
  }else{
    blinkLED();
  }  
}

void blinkLED(){
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin,LOW);
  delay(100);
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}
