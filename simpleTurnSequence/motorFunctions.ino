

void straight() {
  if (goingForward) {
    forward(HIGHSPEED);
  }
  else {
    backward(HIGHSPEED);
  }
}

void correctLeft() {
  if (goingForward) {
    fLeft();
  }
  else {
    bLeft();
  }
}

void correctRight() {
  if (goingForward) {
    fRight();
  }
  else {
    bRight();
  }
}

void forward(int rate) {
  leftSideForward(rate);
  rightSideForward(rate);
}

void backward(int rate) {
  leftSideBackward(rate);
  rightSideBackward(rate);
}

void reverseFor(int backupTime){
  backward(LOWSPEED);
  delay(backupTime);
}


void stopAll() {
  leftSideStop();
  rightSideStop();
}


void fLeft() {
  leftSideBackward(MIDSPEED);
  rightSideForward(MIDSPEED);
}

void fHardLeft(int rate) {
  leftSideBackward(rate);
  rightSideForward(rate);
}

void fRight() {
  rightSideBackward(MIDSPEED);
  leftSideForward(MIDSPEED);
}

void fHardRight(int rate) {
  rightSideBackward(rate);
  leftSideForward(rate);
}

void bRight() {
  leftSideBackward(MIDSPEED);
  rightSideBackward(HIGHSPEED);
}
void bHardRight() {
  leftSideForward(MIDSPEED);
  rightSideBackward(MIDSPEED);
}
void bLeft() {
  rightSideBackward(MIDSPEED);
  leftSideBackward(HIGHSPEED);
}
void bHardLeft() {
  rightSideForward(MIDSPEED);
  leftSideBackward(MIDSPEED);
}


void leftSideForward(int rate) {
  analogWrite(ENA, rate);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void leftSideBackward(int rate) {
  analogWrite(ENA, rate);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void leftSideStop() {
  analogWrite(ENA, LOW);
}
void rightSideStop() {
  analogWrite(ENB, LOW);
}

void rightSideForward(int rate) {
  analogWrite(ENB, rate);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void rightSideBackward(int rate) {
  analogWrite(ENB, rate);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
