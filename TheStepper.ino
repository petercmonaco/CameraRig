/*
 * Copied from ArduinoProjects/StepperExpts
 * Then further adapted for the purposes of the Camera Rig project.
 */
 
#include "MyStepper.h"

const int stepsPerRevolution = 512;

// I'm using analog pins A1-A4 simply because it's easier to solder to those pins on the LCD shield.
MyStepper myStepper(stepsPerRevolution, A1, A2, A3, A4);

void stepperSetup() {
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
}

void stepperLoop(double rpms, int dir) {
  // set the motor speed:
  myStepper.setRPMs(rpms);
  while (1) {
    myStepper.step(1000000 * dir);
  }
}


