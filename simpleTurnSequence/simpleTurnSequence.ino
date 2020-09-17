//Line Tracking IO define
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

// motor control pins
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#define HIGHSPEED 150
#define MIDSPEED 130
#define LOWSPEED 100

int currentSpeed = LOWSPEED;
bool goingForward = true;
unsigned long actionTimer = 0;
unsigned long lookTime = 200;
unsigned long backUpTime = 10;


unsigned long performanceTimer = 0;
int mode = 0;

// 0 = pause, 1 = run, 2 = finished
unsigned long sequence[][2] = {
  {300000, 0}, // 30000 = start in 30 sec 300000 = 5 min
  {180000, 0}, // wait 3 min
  {180000, 1}, // run 6 min.
  {180000, 0}, // 3 min pause
  {180000, 1}, // 3 min run
  {2000, 2}};
int movement = 0;

void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT);
  pinMode(4, INPUT);
  pinMode(2, INPUT);
  performanceTimer = millis() + sequence[movement][0];
  mode = sequence[movement][1];
}

void loop() {

  if (millis() > performanceTimer && mode < 2) {
    movement++;
    performanceTimer = millis() + sequence[movement][0];
    mode = sequence[movement][1];
  }
  if(mode == 0){
    stopAll();
    delay(300);
  }
  else if(mode == 1){
    if (LT_M && LT_R && LT_L) {
      turnAndLook();
    }
    if (LT_M) {
      actionTimer = millis() + lookTime;
      currentSpeed = LOWSPEED;
      forward(currentSpeed);
    }
    else if (LT_R) {
      actionTimer = millis() + lookTime;
      fHardRight(HIGHSPEED);
      while (LT_R);
    }
    else if (LT_L) {
      actionTimer = millis() + lookTime;
      fHardLeft(HIGHSPEED);
      while (LT_L);
    }
    else if (!LT_M && !LT_L && !LT_R) {
      Serial.print("speed: ");
      Serial.println(currentSpeed);

      if (currentSpeed > LOWSPEED * .5) {
        currentSpeed--;
        forward(currentSpeed);
      } else if (actionTimer < millis()) {
        backUpAndLook();

      }
    }
  }
  else {
    stopAll();
    delay(600);
  }
}

void turnAndLook() {
  // reversing
  Serial.println("turn around");
  stopAll();
  delay(200);

  fHardLeft(HIGHSPEED);
  delay(500);
  fHardLeft(MIDSPEED);
  Serial.println("looking for line");
  while (!LT_M) {
  }
}

void backUpAndLook() {
  Serial.println("lost, backing up");
  stopAll();
  delay(50);
  backward(LOWSPEED);
  while (!LT_M) {
  }
  delay(20);
}
