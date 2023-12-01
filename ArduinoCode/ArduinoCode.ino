#include <AccelStepper.h>
#include <MultiStepper.h>

// Define the stepper motor and the pins that is connected to
AccelStepper stepper1(1, 5, 12); // (Typeof driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, 6, 25);
// AccelStepper stepper3(1, 4, 7);

MultiStepper steppersControl;  // Create instance of MultiStepper

long gotoposition[3]; // An array to store the target positions for each stepper motor

void setup() {
  Serial.begin(9600);

  stepper1.setMaxSpeed(1000); // Set maximum speed value for the stepper
  stepper2.setMaxSpeed(1000);
  // stepper3.setMaxSpeed(1000);

  // Adding the 3 steppers to the steppersControl instance for multi stepper control
  steppersControl.addStepper(stepper1);
  // steppersControl.addStepper(stepper2);
  // steppersControl.addStepper(stepper3);
}

void loop() {
  char pressedKey;

  if(Serial.available()){
    pressedKey = Serial.read();
  

    if(pressedKey == 'u'){
      steppersControl.moveTo(200);
      Serial.write("u gedraait");
      steppersControl.runSpeedToPosition();
    }
  }

  // // Store the target positions in the "gotopostion" array
  // gotoposition[0] = 800;  // 800 steps - full rotation with quater-step resolution
  // gotoposition[1] = 1600;
  // gotoposition[2] = 3200;

  // steppersControl.moveTo(gotoposition); // Calculates the required speed for all motors
  // steppersControl.runSpeedToPosition(); // Blocks until all steppers are in position

  // delay(1000);

  // gotoposition[0] = 0;
  // gotoposition[1] = 0;
  // gotoposition[2] = 0;

  // steppersControl.moveTo(gotoposition);
  // steppersControl.runSpeedToPosition();

  // delay(1000);
}