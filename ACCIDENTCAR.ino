#include <Servo.h>

#define in1 11
#define in2 10
#define in3 7
#define in4 6
#define irSensorPin 3
#define buzzerPin 5
#define servoPin A2

Servo ultrasonicServo;

void setup() {
  Serial.begin(9600);

  ultrasonicServo.attach(servoPin);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(irSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    switch (command) {
      case 'F':
        moveCarForward();
        break;
      case 'B':
        moveCarBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        stopCar();
        break;
      case 'P':
        Serial.println(" found car on 16.4963° N, 80.5007° E");
        break;
      default:
        break;
    }
  }
    

  if (digitalRead(irSensorPin) == LOW) {
    // Obstacle detected by IR sensor
    ultrasonicServo.write(0);  // Rotate servo to 90 degrees
    delay(100); // Adjust delay as needed
    sendMessageToApp("Accident happended PLEASE CHECK!");
    // You may add any other actions you want to take in case of an accident.
  }

  // Check IR sensor and activate buzzer if obstacle detected
  if (digitalRead(irSensorPin) == LOW) {
    digitalWrite(buzzerPin, HIGH);
    ultrasonicServo.write(90);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
}

void sendMessageToApp(String message) {
  // Send message to app via Bluetooth
  Serial.println(message);
}

void stopCar() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void moveCarForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveCarBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}