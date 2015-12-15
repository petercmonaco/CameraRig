/*
 * MyStepper.cpp - Stepper library for Wiring/Arduino - Version 1.1.0
 */

#include "Arduino.h"
#include "MyStepper.h"


/*
 *   constructor for four-pin version
 *   Sets which wires should control the motor.
 */
MyStepper::MyStepper(int number_of_steps, int motor_pin_1, int motor_pin_2,
                                      int motor_pin_3, int motor_pin_4)
{
  this->step_number = 0;    // which step the motor is on
  this->speed = 0;          // the motor speed, in revolutions per minute
  this->direction = 0;      // motor direction
  this->numMotorSteps = number_of_steps; // total number of steps for this motor
  this->stepsPerStep = 4;
  this->numMicroSteps = this->numMotorSteps * this->stepsPerStep;

  // Arduino pins for the motor control connection:
  this->motor_pin_1 = motor_pin_1;
  this->motor_pin_2 = motor_pin_2;
  this->motor_pin_3 = motor_pin_3;
  this->motor_pin_4 = motor_pin_4;

  // setup the pins on the microcontroller:
  pinMode(this->motor_pin_1, OUTPUT);
  pinMode(this->motor_pin_2, OUTPUT);
  pinMode(this->motor_pin_3, OUTPUT);
  pinMode(this->motor_pin_4, OUTPUT);
}

/*
 * Sets the speed in RPMs
 */
void MyStepper::setRPMs(double rpms)
{
  this->step_delay = 60.0 * 1000L * 1000L / this->numMicroSteps / rpms;
}

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void MyStepper::step(int steps_to_move)
{
  steps_to_move *= this->stepsPerStep; // Multiply motor-steps to get micro-steps
  int steps_left = abs(steps_to_move);  // how many steps to take

  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) { this->direction = 1; }
  if (steps_to_move < 0) { this->direction = 0; }

  unsigned long firstStepTime = micros();
  unsigned long stepsTaken = 0;

  // decrement the number of steps, moving one step each time:
  while (steps_left > 0)
  {
    unsigned long now = micros();
    // move only if the appropriate delay has passed:
    if (now - firstStepTime >= (this->step_delay * stepsTaken)) {

      // increment or decrement the step number,
      // depending on direction:
      if (this->direction == 1) {
        this->step_number++;
        if (this->step_number >= 4) {
          this->step_number = 0;
        }
      } else {
        this->step_number--;
        if (this->step_number <= -1) {
          this->step_number = 3;
        }
      }
      
      // decrement the steps left:
      steps_left--;
      stepsTaken++;
      // step the motor to step number 0 or 1 or 2 or 3
      stepMotor(this->step_number);
    }
  }
}

/*
 * Moves the motor forward or backwards.
 */
void MyStepper::stepMotor(int thisStep)
{
  switch (thisStep) {
    case 0:  // 1010
      digitalWrite(motor_pin_1, HIGH);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, LOW);
    break;
    case 1:  // 0110
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, HIGH);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, LOW);
    break;
    case 2:  //0101
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, HIGH);
      digitalWrite(motor_pin_4, LOW);
    break;
    case 3:  //1001
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, HIGH);
    break;
  }
}

