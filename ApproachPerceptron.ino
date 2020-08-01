unsigned long previousMilliseconds; 
unsigned long previousMicroseconds; 

float Ultrasonic_displacementOneSecond; 
float Ultrasonic_displacementTwoSecond; 
float Ultrasonic_displacementThreeSecond; 
float Ultrasonic_displacementFourSecond; 
int Ultrasonic_velocityTwoSecond = Ultrasonic_displacementTwoSecond-Ultrasonic_displacementOneSecond;
int Ultrasonic_velocityFourSecond = Ultrasonic_displacementFourSecond-Ultrasonic_displacementThreeSecond; 
long Ultrasonic_accelerationFourSecond = (Ultrasonic_velocityFourSecond-Ultrasonic_velocityTwoSecond)/4; 

float Ultrasonic_displacementFiveSecond; 
float Ultrasonic_displacementSixSecond;
float Ultrasonic_displacementSevenSecond; 
float Ultrasonic_displacementEightSecond; 
int Ultrasonic_velocitySixSecond = Ultrasonic_displacementSixSecond-Ultrasonic_displacementFiveSecond; 
int Ultrasonic_velocityEightSecond = Ultrasonic_displacementEightSecond-Ultrasonic_displacementSevenSecond; 
long Ultrasonic_accelerationEightSecond = (Ultrasonic_velocityEightSecond-Ultrasonic_velocitySixSecond)/4; 

long Ultrasonic_changeInAcceleration = (Ultrasonic_accelerationEightSecond-Ultrasonic_accelerationFourSecond)/8;
long Ultrasonic_weight = 0;  

int PIR_valueOneSecond; 
int PIR_valueTwoSecond; 
int PIR_valueThreeSecond; 
int PIR_valueFourSecond; 
int PIR_valueFiveSecond; 
int PIR_valueSixSecond; 
int PIR_valueSevenSecond; 
int PIR_valueEightSecond; 

int PIR_sum = PIR_valueOneSecond + PIR_valueTwoSecond + PIR_valueThreeSecond + PIR_valueFourSecond + PIR_valueFiveSecond 
+ PIR_valueSixSecond + PIR_valueSevenSecond + PIR_valueEightSecond;
long PIR_weight = 0;

boolean passedOne = false; 
boolean passedTwo = false; 
boolean passedThree= false; 
boolean passedFour = false; 
boolean passedFive = false; 
boolean passedSix = false; 
boolean passedSeven = false; 
boolean passedEight = false; 

const int Ultrasonic_pingPin = 7; 
const int Ultrasonic_echoPin = 6; 

const int PIR_outputPin = 5;

//label input 
const int trainInputPin = 4; 

//activate training or testing phase 
const int trainActivationPin = 8; 
const int testActivationPin = 9; 

const int successLEDPin = 3; 
const int failureLEDPin = 2; 

//Ultrasonic measure and pulse duration
long inches, duration; 

void setup(){
  pinMode(Ultrasonic_echoPin, INPUT);
  pinMode(Ultrasonic_pingPin, OUTPUT);
  pinMode(PIR_outputPin, INPUT); 
  pinMode(trainInputPin, INPUT);
  pinMode(trainActivationPin, INPUT);
  pinMode(testActivationPin, INPUT); 
  pinMode(successLEDPin, OUTPUT);
  pinMode(failureLEDPin, OUTPUT); 
  
}

void loop(){
  if(trainActivationPin == HIGH){
    if(train()){
      digitalWrite(successLEDPin, HIGH);
      digitalWrite(failureLEDPin, LOW);
    }else{
      digitalWrite(failureLEDPin, HIGH);
      digitalWrite(successLEDPin, LOW);
    }
  }else if(testActivationPin == HIGH){
    test();
  }else{
    blinkLED();
  }
}

void blinkLED(){
  digitalWrite(successLEDPin, HIGH);
  delay(100);
  digitalWrite(successLEDPin,LOW);
  delay(100);
  digitalWrite(successLEDPin, HIGH);
  delay(100);
  digitalWrite(successLEDPin, LOW);
}

void test(){
  long prediction = calculatePrediction(); 
  if(prediction<0){
    digitalWrite(failureLEDPin, HIGH);
    digitalWrite(successLEDPin, LOW);
  }else{
    digitalWrite(successLEDPin, HIGH); 
    digitalWrite(failureLEDPin, LOW);
  }
  
}
  
boolean train(){
  long prediction = calculatePrediction();
  int label; 
  if(waitMilliseconds(1800)&&trainInputPin==HIGH){
    label = 1; 
  }else{
    label = -1; 
  }
  if(label*prediction<0){
    PIR_weight = PIR_weight + (PIR_sum*label);
    Ultrasonic_weight = Ultrasonic_weight + (Ultrasonic_changeInAcceleration*label);
    return false; 
  }else{
    return true; 
  }
}

long calculatePrediction(){
 runUltrasonic(); 
 while(!waitMilliseconds(8200)){
  if(waitMilliseconds(8000)&&!passedEight){
    passedEight = true; 
    Ultrasonic_displacementEightSecond = inches; 
    if(PIR_outputPin == HIGH){
      PIR_valueEightSecond = 1; 
    }else{
      PIR_valueEightSecond = -1; 
    }
   }else if(waitMilliseconds(7000)&&!passedSeven){
     passedSeven = true; 
    Ultrasonic_displacementSevenSecond = inches; 
    if(PIR_outputPin == HIGH){
      PIR_valueSevenSecond = 1; 
    }else{
      PIR_valueSevenSecond = -1; 
    }
  }else if(waitMilliseconds(6000)&&!passedSix){
    passedSix = true; 
    Ultrasonic_displacementSixSecond = inches; 
    if(PIR_outputPin == HIGH){
      PIR_valueSixSecond = 1;  
    }else{
      PIR_valueSixSecond = -1; 
    } 
  }else if(waitMilliseconds(5000)&&!passedFive){
    passedFive = true; 
    Ultrasonic_displacementFiveSecond = inches;  
    if(PIR_outputPin == HIGH){
      PIR_valueFiveSecond = 1; 
    }else{
      PIR_valueFiveSecond = -1; 
    }
  }else if(waitMilliseconds(4000)&&!passedFour){
    passedFour = true; 
    Ultrasonic_displacementFourSecond = inches; 
    if(PIR_outputPin == HIGH){
      PIR_valueFourSecond = 1; 
    }else{
      PIR_valueFourSecond = -1; 
    } 
  }else if(waitMilliseconds(3000)&&!passedThree){
    passedThree = true; 
    Ultrasonic_displacementThreeSecond = inches; 
    if(PIR_outputPin == HIGH){
      PIR_valueThreeSecond = 1;  
    }else{
      PIR_valueThreeSecond = -1; 
    } 
  }else if(waitMilliseconds(2000)&&!passedTwo){
    passedTwo = true; 
    Ultrasonic_displacementTwoSecond = inches;
    if(PIR_outputPin == HIGH){
      PIR_valueTwoSecond  = 1; 
    }else{
      PIR_valueTwoSecond = -1; 
    }
  }else if(waitMilliseconds(1000)&&!passedOne){
    passedOne = true; 
    Ultrasonic_displacementOneSecond = inches; 
    if(PIR_outputPin == HIGH){
      PIR_valueOneSecond = 1; 
    }else{
      PIR_valueOneSecond = -1; 
    }
  }
  
 }
 
  long Ultrasonic_prediction = Ultrasonic_changeInAcceleration*Ultrasonic_weight; 
  long PIR_prediction = PIR_sum*PIR_weight;

  return Ultrasonic_prediction+PIR_prediction; 
}

void runUltrasonic(){
   digitalWrite(Ultrasonic_pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(Ultrasonic_pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(Ultrasonic_pingPin, LOW);
   duration = pulseIn(Ultrasonic_echoPin, HIGH);
   inches = microsecondsToInches(duration);
}

boolean waitMilliseconds(int milliseconds){
  unsigned long currentMilliseconds = millis();
  if(currentMilliseconds-previousMilliseconds >= milliseconds){
    previousMilliseconds = currentMilliseconds;
    return true;
  }else{
    return false; 
  }
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}
