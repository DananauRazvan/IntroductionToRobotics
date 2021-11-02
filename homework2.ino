const int mainRoadRed = 3;  
const int mainRoadYellow = 4;
const int mainRoadGreen = 5;
const int crossRed = 8;  
const int crossGreen = 9;
const int buzzer = 12;
const int button = 13; 
const int crossTime = 7000;   
long buttonGap;

void setup () {
  pinMode(mainRoadRed, OUTPUT);
  pinMode(mainRoadYellow, OUTPUT);
  pinMode(mainRoadGreen, OUTPUT);
  pinMode(crossRed, OUTPUT);
  pinMode(crossGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
 
  digitalWrite(mainRoadGreen, HIGH);
  digitalWrite(crossRed, HIGH);
}

void loop() {
  int state = digitalRead(button);
  
   // check if it is over 3 sec since last button press
  if(state == HIGH && (millis() - buttonGap) > 3000) {
    switchLights();   
  }
}

void switchLights() {
  digitalWrite(mainRoadGreen, LOW);
  digitalWrite(mainRoadYellow, HIGH);
  delay(2000);

  digitalWrite(mainRoadYellow, LOW);
  digitalWrite(mainRoadRed, HIGH);
  delay(1000);

  digitalWrite(crossRed, LOW);
  digitalWrite(crossGreen, HIGH);
  delay(crossTime);
  
  for (int i = 0; i < 10; i++){
    digitalWrite(crossGreen, HIGH);
    tone(buzzer, 2900, 250);
    delay(250);
    digitalWrite(crossGreen, LOW);
    delay(250);
  }
 
  digitalWrite(crossRed, HIGH);
  delay(100);
 
  digitalWrite(mainRoadGreen, HIGH);
  digitalWrite(mainRoadRed, LOW);
 
  buttonGap = millis();
}
