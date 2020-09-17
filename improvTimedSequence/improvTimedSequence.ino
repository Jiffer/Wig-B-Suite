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
#define MIDSPEED 100
#define LOWSPEED 90

int currentSpeed = HIGHSPEED;
bool goingForward = true;
unsigned long actionTimer = 0;
unsigned long lookTime = 200;
unsigned long backUpTime = 10;

unsigned long performanceTimer = 0;
int mode = 0;

// 0 = pause, 1 = run, 2 = finished
unsigned long sequence[][2] = {
  {300000, 0}, // start in 30 sec
  {720000, 1}, // run 12 minutes
  {5000, 2}
};

int movement = 0;
//bool lastDirection; // 0 = forward, 1 = backward, 2 = left, 3 = right

void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT);
  pinMode(4, INPUT);
  pinMode(2, INPUT);

  movement = 0;
  performanceTimer = millis() + sequence[movement][0];
  mode = sequence[movement][1];

  Serial.println("begin");
  Serial.print("wait for: ");
  Serial.println(performanceTimer);
}

void loop() {
 
  if (millis() > performanceTimer && mode < 2) {
    movement++;
    Serial.print("movement: ");
    Serial.println(movement);
    performanceTimer = millis() + sequence[movement][0];
    mode = sequence[movement][1];
    Serial.print("mode: ");
    Serial.println(mode);
  }
  if (mode == 0) {

    stopAll();
    delay(100);
  }
  else if (mode == 1) {
    Serial.println("new sequence");
    int sequenceLength = random(8, 16);
    int mood[sequenceLength];
    for (int i = 0; i < sequenceLength; i++) {
      mood[i] = random(5);
    }
    for (int loopIt = 0; loopIt < random(4, 8); loopIt++) {
      for (int i = 0; i < sequenceLength; i++) {
        if (millis() > performanceTimer) {
          break;
        }
        if (!LT_M && !LT_L && !LT_R) { // if all white detected
          Serial.println("backup");
          backward(HIGHSPEED);
          delay(600);

        } else if (!LT_R) {
          fHardLeft(HIGHSPEED);
          delay(600);
          forward(HIGHSPEED);
          
          delay(300);
        } else if (!LT_L) {
          fHardRight(HIGHSPEED);
          delay(600);
          forward(HIGHSPEED);
          
          delay(300);
        }
        switch (mood[i]) {
          case 0:
            actionTimer = millis() + lookTime;
            forward(LOWSPEED);
            
            delay(300);
            break;
          case 1:
            fHardRight(HIGHSPEED);
            
            delay(300);
            break;
          case 2:
            fHardLeft(HIGHSPEED);
            
            delay(300);
            break;
          case 3:
            backward(LOWSPEED);
            
            //            delay(300);
            break;
          default:
            stopAll();
            delay(600);
            break;
        }
      }
    }
  }
  else if (mode == 2) {
    Serial.println("finished");
    stopAll();
    delay(60000);
  }
}
