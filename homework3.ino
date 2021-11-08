#define NUMREADINGS 25
const int senseLimit = 1023;
const int probePin = A5;
int val = 0;
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4 = 5;
const int LED5 = 6;
const int LED6 = 7;
const int LED7 = 8;
const int LED8 = 9;
const int buzzer = 12;
int readings[NUMREADINGS];
int index = 0;
int total = 0;
int average = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(probePin, INPUT);
  
  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;
}

void loop() {
  val = analogRead(probePin);
  
  if (val >= 1) {
    val = constrain(val, 1, senseLimit);
    val = map(val, 1, senseLimit, 1, 1023);
    
    total -= readings[index];
    readings[index] = val;
    total += readings[index]; 
    index = (index + 1); 
    
    if (index >= NUMREADINGS) 
     index = 0;
     
    average = total / NUMREADINGS;
    
    if (average > 50) {
      digitalWrite(LED1, HIGH);
    }
    else {
      digitalWrite(LED1, LOW);
     }
     if (average > 100) {
        digitalWrite(LED2, HIGH);
     }
     else {
        digitalWrite(LED2, LOW);
     }
     if (average > 150) {
        digitalWrite(LED3, HIGH);
     }
     else {
        digitalWrite(LED3, LOW);
     }
     if (average > 200) {
        digitalWrite(LED4, HIGH);
     }
     else {
        digitalWrite(LED4, LOW);
     }
     if (average > 250) {
        digitalWrite(LED5, HIGH);
     }
     else {
        digitalWrite(LED5, LOW);
     }
     if (average > 300) {
        digitalWrite(LED6, HIGH);
        tone(buzzer, 300, 20);
     }
     else {
        digitalWrite(LED6, LOW);
     }
     if (average > 350) {
        digitalWrite(LED7, HIGH);
     }
     else {
        digitalWrite(LED7, LOW);
     }
     if (average > 400) {
        digitalWrite(LED8, HIGH);
     }
     else {
        digitalWrite(LED8, LOW);
     }
  }
}
