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

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  stepper1.setMaxSpeed(1000); // Set maximum speed value for the stepper
  stepper2.setMaxSpeed(1000);
  stepper3.setMaxSpeed(1000);
  stepper4.setMaxSpeed(1000);
  stepper5.setMaxSpeed(1000);
  stepper6.setMaxSpeed(1000);

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
    char command = Serial.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  switch (command) {
    case 'u':
      turnMotor(0, -400); // Turn up motor by 400 steps (90 degrees)
      break;
    case 'U':
      turnMotor(0, 400); // Turn up motor in the opposite direction by 400 steps
      break;
    case 'd':
      turnMotor(1, 400); // Turn down motor by 400 steps (90 degrees)
      break;
    case 'D':
      turnMotor(1, -400); // Turn down motor in the opposite direction by 400 steps
      break;
    case 'l':
      turnMotor(2, -400); // Turn left motor by 400 steps (90 degrees)
      break;
    case 'L':
      turnMotor(2, 400); // Turn left motor in the opposite direction by 400 steps
      break;
    case 'r':
      turnMotor(3, -400); // Turn right motor by 400 steps (90 degrees)
      break;
    case 'R':
      turnMotor(3, 400); // Turn right motor in the opposite direction by 400 steps
      break;
    case 'b':
      turnMotor(4, -400); // Turn front motor by 400 steps (90 degrees)
      break;
    case 'B':
      turnMotor(4, 400); // Turn front motor in the opposite direction by 400 steps
      break;
    case 'f':
      turnMotor(5, -400); // Turn back motor by 400 steps (90 degrees)
      break;
    case 'F':
      turnMotor(5, 400); // Turn back motor in the opposite direction by 400 steps
      break;
    // Add more cases for other commands if needed
  }
}

void turnMotor(int motorIndex, int steps) {
  gotoposition[motorIndex] += steps;
  steppersControl.moveTo(gotoposition);
  steppersControl.runSpeedToPosition();
}
