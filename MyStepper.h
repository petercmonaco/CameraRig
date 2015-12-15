/*
 * MyStepper.h - Stepper library for Wiring/Arduino - Version 1.1.0
 *
 * Drives a ULN2003 motor with the associated power driver board.
 *
 * The sequence of control signals for 4 control wires would normally be as follows:
 *
 * Step C0 C1 C2 C3
 *    1  1  0  1  0
 *    2  0  1  1  0
 *    3  0  1  0  1
 *    4  1  0  0  1
 *    
 *  But the little board that comes with the ULN2003 actually wants the following inputs:
 *
 * Step C0 C1 C2 C3
 *    1  1  0  0  0
 *    2  0  1  0  0
 *    3  0  0  1  0
 *    4  0  0  0  1
 *    
 * ...so I modified the library.

 */

// ensure this library description is only included once
#ifndef My_Stepper_h
#define My_Stepper_h

// library interface description
class MyStepper {
  public:
    // constructor:
    MyStepper(int number_of_steps, int motor_pin_1, int motor_pin_2,
                                 int motor_pin_3, int motor_pin_4);

    // speed setter method:
    void setRPMs(double rpms);

    // mover method:
    void step(int number_of_steps);

  private:
    void stepMotor(int this_step);

    int direction;            // Direction of rotation
    int speed;                // Speed in RPMs
    double step_delay; // delay between steps, in ms, based on speed
    int numMotorSteps;        // total number of steps this motor can take
    int stepsPerStep;         // Total number of pin output combinations per motor step
    int numMicroSteps;        // Product of previous two
    int step_number;          // which step the motor is on

    // motor pin numbers:
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;
};

#endif

