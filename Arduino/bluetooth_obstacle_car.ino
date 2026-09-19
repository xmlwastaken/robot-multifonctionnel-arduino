/*
 * Bluetooth Obstacle Avoiding Car
 * -------------------------------
 * PFA 2024-2025 - 3IAII
 * Réalisé par: LAAMRI Mohamed & BELEKHBIZI Slimane
 * Encadré par: Mme TEBAY Imane
 * 
 * Description:
 * Voiture télécommandée via Bluetooth HC-05 + évitement d'obstacles automatique
 * via capteur ultrason HC-SR04. Deux modes:
 * 1. Mode Manuel: Commandes Bluetooth (F,B,L,R,S)
 * 2. Mode Auto: Évitement automatique si obstacle < 20cm
 * 
 * This sketch allows for two modes:
 * 1. Manual Mode: Controlled via Bluetooth commands ('F','B','L','R','S')
 * 2. Auto Mode: Uses HC-SR04 to stop if obstacle too close
 * 
 * Connections (from original docx):
 * - HC-05 Bluetooth:
 *   VCC -> 5V, GND -> GND
 *   TX -> Arduino RX (D0), RX -> Arduino TX (D1) [voltage divider 5V->3.3V]
 * - HC-SR04 Ultrasonic:
 *   VCC -> 5V, GND -> GND, TRIG -> D9, ECHO -> D8
 * - L298N Motor Driver:
 *   IN1 -> D2, IN2 -> D3, IN3 -> D4, IN4 -> D5
 *   ENA -> D10 (PWM Motor A), ENB -> D11 (PWM Motor B)
 *   DC Motors -> L298N outputs
 * 
 * Source: Extrait de "Bluetooth Obstacle Avoiding Car.docx" dans le Drive PFA
 */

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 8;

// L298N Motor Driver pins
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;
const int enA = 10; // PWM left motor
const int enB = 11; // PWM right motor

// Motor speed (0-255)
const int motorSpeed = 150;

// Bluetooth command
char command = 'S'; // Default: Stop

void setup() {
  // Serial for HC-05 Bluetooth (9600 baud)
  Serial.begin(9600);

  // Motor driver pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start with motors off
  stopMotors();
}

void loop() {
  // If Bluetooth command available -> Manual mode
  if (Serial.available() > 0) {
    command = Serial.read();
    executeCommand(command);
  } else {
    // No command -> Auto obstacle avoidance mode
    autoObstacleAvoid();
  }
}

// Measure distance using HC-SR04
long readDistance() {
  long duration, distance;
  
  // Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger HIGH for 10us
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read echoPin duration (timeout 30ms)
  duration = pulseIn(echoPin, HIGH, 30000);
  
  // Convert to cm
  distance = duration * 0.034 / 2;
  
  return distance;
}

// Auto obstacle avoidance
void autoObstacleAvoid() {
  long distance = readDistance();

  // If obstacle detected within 20cm, stop
  if (distance > 0 && distance <= 20) {
    stopMotors();
    delay(500);
    
    // Optional: turn right to avoid
    // turnRight();
    // delay(500);
    // stopMotors();
    // delay(200);
  } else {
    // No obstacle -> move forward
    moveForward();
  }
}

// Execute Bluetooth command
void executeCommand(char cmd) {
  switch (cmd) {
    case 'F': // Forward
      moveForward();
      break;
    case 'B': // Backward
      moveBackward();
      break;
    case 'L': // Left
      turnLeft();
      break;
    case 'R': // Right
      turnRight();
      break;
    case 'S': // Stop
    default:
      stopMotors();
      break;
  }
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
