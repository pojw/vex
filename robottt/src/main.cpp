/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\berna                                            */
/*    Created:      Fri Jan 10 2025                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// DigitalOutH          digital_out   H               
// DigitalOutC          digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"

using namespace vex;

competition Competition;

// Define motors for the drivetrain
motor leftMotor1(PORT8, ratio18_1, false);
motor leftMotor2(PORT9, ratio18_1, false);
motor leftMotor3(PORT10, ratio18_1, false);
motor rightMotor1(PORT17, ratio18_1, true);
motor rightMotor2(PORT18, ratio18_1, true);
motor rightMotor3(PORT19, ratio18_1, true);


// Define the intake motor
motor intakeMotor(PORT2, ratio18_1, false);

// Define the intake motor
motor Wheels(PORT3, ratio18_1, false);

//arms
motor armMotor(PORT1, ratio18_1,true);


// Define the target positions for the arm
int armPositions[4] = {0,160,460,660};

int currentPositionIndex = 0; // Index to track the current position

// Function to move the arm to the target position
void moveArmToPosition() {
    int targetPosition = armPositions[currentPositionIndex];
    armMotor.spinToPosition(targetPosition, degrees, 50, velocityUnits::pct); // Adjust velocity as needed
}
 
// Group the left and right motors
motor_group leftDrive(leftMotor1, leftMotor2, leftMotor3);
motor_group rightDrive(rightMotor1, rightMotor2, rightMotor3);


// Define the controller
controller Controller1;




void extendPiston() {
    DigitalOutC.set(true);
}
void retractPiston() {
    DigitalOutC.set(false);
}

void extendPistonH() {
    DigitalOutH.set(true);
}
void retractPistonH() {
    DigitalOutH.set(false);
}
void Autonomous(void) {
  leftDrive.setVelocity(70,percent);
  rightDrive.setVelocity(70,percent);

  leftDrive.spinFor(reverse, 1.5, rev, false);
  rightDrive.spinFor(reverse, 1.5, rev, false);

  wait(2, sec);
  extendPiston();
  wait(2, sec);
 // Set the intake motor to spin at 70% velocity by default
      intakeMotor.setVelocity(70, percent);
      intakeMotor.spin(reverse);
}

void UserControl(void){


    

      // // Reset the motor's position to zero
      // armMotor.resetPosition();
    while(true) {
      Controller1.ButtonX.pressed(extendPiston);
      Controller1.ButtonA.pressed(retractPiston);
      Controller1.ButtonY.pressed(extendPistonH);
      Controller1.ButtonB.pressed(retractPistonH);

        Wheels.setVelocity(90,percent);
       //Wheels.spin(reverse);

                // Check if the 'X' button is pressed
        if (Controller1.ButtonR1.pressing()) {
            // Increment the position index
            currentPositionIndex = (currentPositionIndex + 1) % 4; // Cycle through positions
            moveArmToPosition();
            wait(0.2, seconds); // Debounce delay
        }


      // Set the intake motor to spin at 70% velocity by default
      intakeMotor.setVelocity(80, percent);
      intakeMotor.spin(reverse);
      
// Get the joystick values
        int leftSpeed = Controller1.Axis3.position(percent);
        int rightSpeed = Controller1.Axis2.position(percent);

        // Set the speed of the left and right motor groups

        
        leftDrive.spin(forward, leftSpeed, percent);
        rightDrive.spin(forward, rightSpeed, percent);
        // Control the intake motor with the 'L2' and 'R2' buttons
        // if(Controller1.ButtonL2.pressing()) {
        //     intakeMotor.setVelocity(70,percent);
        //     intakeMotor.spin(reverse);

        // } else 
        if(Controller1.ButtonR2.pressing()) {
            intakeMotor.setVelocity(70,percent);
            intakeMotor.spin(forward);                                  
        }

        // Small delay to prevent overloading the CPU
        wait(20, msec);
    }
    
}

int main() {
  Autonomous();
  UserControl();
//     Controller1.ButtonX.pressed(extendPiston);
//     Controller1.ButtonA.pressed(retractPiston);
//     Controller1.ButtonY.pressed(extendPistonH);
//     Controller1.ButtonB.pressed(retractPistonH);

    Wheels.setVelocity(90,percent);
    Wheels.spin(reverse);

//       // Reset the motor's position to zero
//       armMotor.resetPosition();
//     while(true) {

//                 // Check if the 'X' button is pressed
//         if (Controller1.ButtonR1.pressing()) {
//             // Increment the position index
//             currentPositionIndex = (currentPositionIndex + 1) % 4; // Cycle through positions
//             moveArmToPosition();
//             wait(0.2, seconds); // Debounce delay
//         }


      // Set the intake motor to spin at 70% velocity by default
      intakeMotor.setVelocity(70, percent);
      intakeMotor.spin(reverse);
// Get the joystick values
        int leftSpeed = Controller1.Axis3.position(percent);
        int rightSpeed = Controller1.Axis2.position(percent);

        // Set the speed of the left and right motor groups
        leftDrive.spin(forward, leftSpeed, percent);
        rightDrive.spin(forward, rightSpeed, percent);
//         // Control the intake motor with the 'L2' and 'R2' buttons
//         if(Controller1.ButtonL2.pressing()) {
//             intakeMotor.setVelocity(70,percent);
//             intakeMotor.spin(reverse);

//         } else if(Controller1.ButtonR2.pressing()) {
//             intakeMotor.spin(forward);                                  
//         }
//         Wheels.setVelocity(90,percent);
//         Wheels.spin(reverse);
//         // Small delay to prevent overloading the CPU
//         wait(20, msec);
//     }
}