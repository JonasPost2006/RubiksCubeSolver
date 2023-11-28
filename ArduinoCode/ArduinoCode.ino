#include <AccelStepper.h>
#include <MultiStepper.h>

// AccelStepper stepper1(1, 2, 9);
// AccelStepper stepper2(1, 7, 24);
// AccelStepper stepper3(1, 3, 10);
// AccelStepper stepper4(1, 4, 11);
AccelStepper stepper5(1, 5, 12);
AccelStepper stepper6(1, 6, 25);

MultiStepper steppersControl;

void setup() {
  Serial.begin(9600);

  stepper5.setMaxSpeed(1000);
  stepper6.setMaxSpeed(1000);

  steppersControl.addStepper(stepper5);
  steppersControl.addStepper(stepper6);
}

void loop() {
  if(Serial.available() > 0){
    char input = Serial.read();
    
    if(input == 'U'){
      stepper5.step(200);
    }
    if(input == 'u'){
      stepper5.step(-200);
    }

    if(input == 'D'){
      stepper6.step(200);
    }
    if(input == 'd'){
      stepper6.step(-200);
    }
  }

}
