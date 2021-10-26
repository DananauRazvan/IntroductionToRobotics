const int redPotPin = A0;
const int greenPotPin = A1;
const int bluePotPin = A2;

const int redPin = 3;
const int greenPin = 5;
const int bluePin = 9;

const int ledLowestLimit = 0;
const int ledHighestLimit = 255;
const int potLowestLimit = 0;
const int potHighestLimit = 1023;

int redPotValue = 0, greenPotValue = 0, bluePotValue = 0;
int redPinValue = 0, greenPinValue = 0, bluePinValue = 0; 

void setup() {
  pinMode(redPotPin, INPUT);
  pinMode(greenPotPin, INPUT);
  pinMode(bluePotPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  redPotValue = analogRead(redPotPin);
  greenPotValue = analogRead(greenPotPin);
  bluePotValue = analogRead(bluePotPin);

  redPinValue = map(redPotValue, potLowestLimit, potHighestLimit, ledLowestLimit, ledHighestLimit);
  greenPinValue = map(greenPotValue, potLowestLimit, potHighestLimit, ledLowestLimit, ledHighestLimit);
  bluePinValue = map(bluePotValue, potLowestLimit, potHighestLimit, ledLowestLimit, ledHighestLimit);
  
  analogWrite(redPin, redPinValue);
  analogWrite(greenPin, greenPinValue);
  analogWrite(bluePin, bluePinValue);
}
