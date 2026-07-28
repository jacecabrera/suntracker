#define LDR_TL A0
#define LDR_TR A1
#define LDR_BL A2
#define LDR_BR A3

// Pins for boundary pts. (opticals are first, levers backup)
const int optA6 = 12;
const int optA7 = 13;
const int leverA6 = 7;
const int leverA7 = 8;

//DC motor pins
const int dc_pwm = 3;
const int dc_ina = 5;
const int dc_inb = 6;

// linear actuator pins
const int la_pwm = 9;
const int la_ina = 10;
const int la_inb = 11;

// tune laters
int dark_thres = 150;
unsigned long dark_timeout = 30000;
int deadband = 40;
int move_speed = 150;
int search_speed = 100;

// tracking state variables
unsigned long darkTimer = 0;
bool isDark = false;
unsigned long stallTimer = 0;
bool isStalled = false;

enum Direction { DIR_A, DIR_B, UP, DOWN };

void stopAzimuth() {
  digitalWrite(dc_ina, LOW);
  digitalWrite(dc_inb, LOW);
  analogWrite(dc_pwm, 0);
}

void stopElevation() {
  digitalWrite(la_ina, LOW);
  digitalWrite(la_inb, LOW);
  analogWrite(la_pwm, 0);
}

void holdPosition() {
  stopAzimuth();
  stopElevation();
}

bool atRotationBoundary() {
  if (digitalRead(optA6) == LOW || digitalRead(leverA6) == LOW) return true;
  if (digitalRead(optA7) == LOW || digitalRead(leverA7) == LOW) return true;
  return false;
}

void driveDCMotor(Direction dir) {
  if (dir == DIR_A) {
    digitalWrite(dc_ina, HIGH);
    digitalWrite(dc_inb, LOW);
  } else {
    digitalWrite(dc_ina, LOW);
    digitalWrite(dc_inb, HIGH);
  }
  analogWrite(dc_pwm, move_speed);
}

void driveLinearActuator(Direction dir) {
  if (dir == UP) {
    digitalWrite(la_ina, HIGH);
    digitalWrite(la_inb, LOW);
  } else {
    digitalWrite(la_ina, LOW);
    digitalWrite(la_inb, HIGH);
  }
  analogWrite(la_pwm, move_speed);
}

void searchForLight() {
  static Direction sweepDir = DIR_A;
  static unsigned long lastFlip = 0;

  // flip direction if hitting limit switch (1s debounce)
  if (atRotationBoundary() && (millis() - lastFlip > 1000)) {
    if (sweepDir == DIR_A) sweepDir = DIR_B;
    else sweepDir = DIR_A;
    lastFlip = millis();
  }

  if (sweepDir == DIR_A) {
    digitalWrite(dc_ina, HIGH);
    digitalWrite(dc_inb, LOW);
  } else {
    digitalWrite(dc_ina, LOW);
    digitalWrite(dc_inb, HIGH);
  }
  analogWrite(dc_pwm, search_speed);

  int avgCheck = (analogRead(LDR_TL) + analogRead(LDR_TR) + analogRead(LDR_BL) + analogRead(LDR_BR)) / 4;
  if (avgCheck >= dark_thres) {
    isDark = false;
    stopAzimuth();
  }
}

void setup() {
  pinMode(optA6, INPUT_PULLUP);
  pinMode(optA7, INPUT_PULLUP);
  pinMode(leverA6, INPUT_PULLUP);
  pinMode(leverA7, INPUT_PULLUP);

  pinMode(dc_pwm, OUTPUT);
  pinMode(dc_ina, OUTPUT);
  pinMode(dc_inb, OUTPUT);
  
  pinMode(la_pwm, OUTPUT);
  pinMode(la_ina, OUTPUT);
  pinMode(la_inb, OUTPUT);

  holdPosition();
}

void loop() {
  int tl = analogRead(LDR_TL);
  int tr = analogRead(LDR_TR);
  int bl = analogRead(LDR_BL);
  int br = analogRead(LDR_BR);
  int avg = (tl + tr + bl + br) / 4;

  // night mode logic
  if (avg < dark_thres) {
    if (atRotationBoundary()) {
      if (!isStalled) {
        isStalled = true;
        stallTimer = millis();
      }
      if (millis() - stallTimer > dark_timeout) {
        searchForLight();
        return;
      }
      holdPosition();
      return;
    }
    isStalled = false;

    if (!isDark) {
      isDark = true;
      darkTimer = millis();
    }
    if (millis() - darkTimer > dark_timeout) {
      searchForLight();
      return;
    }
    holdPosition();
    return;
  } else {
    isDark = false;
    isStalled = false;
  }

  // normal tracking logic
  int xDiff = (tl + bl) - (tr + br);
  int yDiff = (tl + tr) - (bl + br);

  // azimuth tracking
  if (abs(xDiff) > deadband) {
    if (atRotationBoundary()) {
      stopAzimuth();
    } else {
      if (xDiff > 0) driveDCMotor(DIR_A);
      else driveDCMotor(DIR_B);
    }
  } else {
    stopAzimuth();
  }

  // elevation tracking
  if (abs(yDiff) > deadband) {
    if (yDiff > 0) driveLinearActuator(UP);
    else driveLinearActuator(DOWN);
  } else {
    stopElevation();
  }
}