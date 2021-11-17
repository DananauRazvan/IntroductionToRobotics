const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int dataPin = 12;
const int latchPin = 11;
const int clockPin = 10;

const int swPin = 2;
const int xPin = A0;
const int yPin = A1;

int digitArray[10] = {
  B11111100,
  B01100000,
  B11011010,
  B11110010,
  B01100110,
  B10110110,
  B10111110,
  B11100000,
  B11111110,
  B11110110
};

const int displayCount = 4;

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

int segmentValues[displayCount];

const int dot = 300;
const int joyLow = 1;
const int joyHigh = 1000;

int state = 0;
int segIndex = 0;
int dotState = HIGH;

bool joyMoved = false;
unsigned long snap = 0;

void setup() {
  pinMode(swPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(swPin), interruptState, FALLING);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }

  state0();
  segValues();  
}

void loop() {
  if (state == 0) {
    state0Prog();
  }
  else
    if (state == 1) {
      state1Prog();
    }

  showSegValues();
}

void writeReg(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}

void showDigit(int displayNumber) {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void segValues() {
  for (int i = 0; i < displayCount; i++) {
    segmentValues[i] = i;
  }
}

void showSegValues() {
  for (int i = 0; i < displayCount; i++) {
    int number = digitArray[segmentValues[i]];
    if (i == segIndex && dotState == HIGH) {
      number ^= 1; 
    }
    
  writeReg(number);
  showDigit(i);
  delay(5);
  }
}

void state0() {
  state = 0;
  snap = millis();
  joyMoved = false;
  dotState = HIGH;
}

void state0Prog() {
  int yJoy = analogRead(yPin);
  
  unsigned long start = millis();

  if (start - snap > dot) {
    dotState = !dotState;
    snap = start;
  }

  if (joyMoved == false && yJoy > joyHigh) {
    joyMoved = true;
    segIndex -= 1;    
  }

  if (joyMoved == false && yJoy < joyLow) {
    joyMoved = true;
    segIndex += 1;
  }

  if (joyMoved == true && yJoy >= joyLow && yJoy <= joyHigh) {
    joyMoved = false;
  }

  if (segIndex == displayCount) {
    segIndex = 0;
  }
  else
    if (segIndex == -1) {
      segIndex = displayCount - 1;
    }
}

void state1() {
  state = 1;
  dotState = HIGH;
}

void state1Prog() {
  int xJoy = analogRead(xPin);

  if (joyMoved == false && xJoy > joyHigh) {
    joyMoved = true;
    segmentValues[segIndex] += 1;
  }

  if (joyMoved == false && xJoy < joyLow) {
    joyMoved = true;
    segmentValues[segIndex] -= 1;
  }

  if (joyMoved == true && xJoy >= joyLow && xJoy <= joyHigh) {
    joyMoved = false;
  }

  if (segmentValues[segIndex] == 10) {
    segmentValues[segIndex] = 0;
  }
  else
    if (segmentValues[segIndex] == -1) {
      segmentValues[segIndex] = 9;
    }
}

void interruptState() {
  if (state == 0) {
    state1();
  }
  else
    if (state == 1) {
      state0();
    }
}
