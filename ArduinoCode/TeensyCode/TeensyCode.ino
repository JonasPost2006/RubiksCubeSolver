#include <AccelStepper.h>
#include <MultiStepper.h>

// Define the stepper motor and the pins that are connected to
// (Typeof driver: with 2 pins, STEP, DIR)
AccelStepper stepper1(1, 6, 25); // up
AccelStepper stepper2(1, 5, 12); // down
AccelStepper stepper3(1, 7, 24); // left
AccelStepper stepper4(1, 3, 10); // right
AccelStepper stepper5(1, 4, 11); // front
AccelStepper stepper6(1, 2, 9);  // back

MultiStepper steppersControl;  // Create an instance of MultiStepper

long gotoposition[6]; // An array to store the target positions for each stepper motor
int speed = 6000; //rpm

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  Serial.print("Ready!");
  stepper1.setMaxSpeed(speed); // Set maximum speed value for the stepper
  stepper2.setMaxSpeed(speed);
  stepper3.setMaxSpeed(speed);
  stepper4.setMaxSpeed(speed);
  stepper5.setMaxSpeed(speed);
  stepper6.setMaxSpeed(speed);

  // Adding the 6 steppers to the steppersControl instance for multi-stepper control
  steppersControl.addStepper(stepper1);
  steppersControl.addStepper(stepper2);
  steppersControl.addStepper(stepper3);
  steppersControl.addStepper(stepper4);
  steppersControl.addStepper(stepper5);
  steppersControl.addStepper(stepper6);
}

void loop() {
  if (Serial.available() > 0) {
    char move = Serial.read(); //Serial.readString(); PROBEREN
    motorMove(move);
    // Serial.print(move);
    // Serial.print("Moves uitgevoerd");
  }
}

void motorMove(char move) {
  switch (move) {
    case 'u':
      turnMotor(0, -400); // Draai de motor 90 graden met de klok mee
      break;
    case 'U':
      turnMotor(0, 400); // Draai de motor 90 graden tegen de klok in
      break;
    case 'd':
      turnMotor(1, -400);
      break;
    case 'D':
      turnMotor(1, 400); 
      break;
    case 'l':
      turnMotor(2, -400); 
      break;
    case 'L':
      turnMotor(2, 400); 
      break;
    case 'r':
      turnMotor(3, -400); 
      break;
    case 'R':
      turnMotor(3, 400);
      break;
    case 'b':
      turnMotor(4, -400); 
      break;
    case 'B':
      turnMotor(4, 400); 
      break;
    case 'f':
      turnMotor(5, -400);
      break;
    case 'F':
      turnMotor(5, 400); 
      break;
  }
}

void turnMotor(int motorIndex, int steps) {
  gotoposition[motorIndex] += steps;
  steppersControl.moveTo(gotoposition);
  steppersControl.runSpeedToPosition();
  // delay(10);
}
