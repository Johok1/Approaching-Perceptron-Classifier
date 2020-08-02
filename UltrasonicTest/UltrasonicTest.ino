const int pingPin = 7; 
const int echoPin = 6; 
const int ledPin = 4; 
const int onPin = 2;

void setup() {
 Serial.begin(9600);
 pinMode(pingPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(ledPin, OUTPUT);
 pinMode(onPin, INPUT);
}

void loop() {
  if(digitalRead(onPin) == HIGH){
   long duration, inches, cm;
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   Serial.println(inches);
   if(inches<=4){
    digitalWrite(ledPin, HIGH);
   }else{
    digitalWrite(ledPin, LOW);
    delay(100);
   }
  }else if(digitalRead(onPin)==LOW){
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

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
