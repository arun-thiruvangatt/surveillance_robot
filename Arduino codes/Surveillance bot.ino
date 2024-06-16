#include <Servo.h>

int enA = A2;
int in1 = A0;
int in2 = A1;
// motor two
int enB = A3;
int in3 = A5;
int in4 = A4;

#define echoPin 2
#define trigPin 3
#define servoPin 4

#define spoint 90

long duration;
int distance;
int left, right, L = 0, R = 0;

Servo servo;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo.attach(servoPin);
  servo.write(10);
  start();
}

void loop() {
  int dist = ultrasonic();
  if (dist <= 20) {
    stopMotors();
    moveBackward();
    delay(100);
    L = leftsee();
    servo.write(spoint);
    delay(800);
    R = rightsee();
    servo.write(spoint);
    if (L < R) {
      turnLeft();
      delay(500);
      stopMotors();
      delay(200);
    } else if (L > R) {
      turnRight();
      delay(500);
      stopMotors();
      delay(200);
    }
  } else {
    moveForward();
  }
}

int ultrasonic() {
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void moveForward() {
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
}

void moveBackward() {
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
}

void turnLeft() {
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
}

void turnRight() {
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
}
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
int leftsee() {
  servo.write(20);
  delay(800);
  left = ultrasonic();
  return left;
}
int rightsee() {
  servo.write(150);
  delay(800);
  right = ultrasonic();
  return right;
}
void start() {
  delay(3000);
  for (int a = 0; a < 4; a++) {
    servo.write(spoint);
    delay(50);
    servo.write(40);
    delay(50);
    servo.write(90);
    delay(50);
    servo.write(spoint);
  }
}