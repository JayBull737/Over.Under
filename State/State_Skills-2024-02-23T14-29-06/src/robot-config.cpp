#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT11, ratio18_1, false);
motor leftMotorB = motor(PORT12, ratio18_1, false);
motor leftMotorC = motor(PORT13, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor rightMotorA = motor(PORT18, ratio18_1, true);
motor rightMotorB = motor(PORT19, ratio18_1, true);
motor rightMotorC = motor(PORT20, ratio18_1, true);
motor_group RightDriveSmart =
motor_group(rightMotorA, rightMotorB, rightMotorC);
inertial DrivetrainInertial = inertial(PORT17);
smartdrive Drivetrain = smartdrive(RightDriveSmart, LeftDriveSmart,
                                   DrivetrainInertial, 319.19, 320, 40, mm, 1);
motor Itake = motor(PORT16, ratio18_1, false);
motor Pun = motor(PORT15, ratio6_1, false);
digital_out wingL = digital_out(Brain.ThreeWirePort.H);
digital_out wingR = digital_out(Brain.ThreeWirePort.A);
digital_out Park = digital_out(Brain.ThreeWirePort.B);
distance Distance1 = distance(PORT21); 

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while (true) {
    if (RemoteControlCodeEnabled) {
      // check the ButtonL1/ButtonL2 status to control Intake
      if (Controller1.ButtonL1.pressing()) {
        Itake.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        Itake.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        Itake.stop();
        // set the toggle so that we don't constantly tell the motor to stop
        // when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain Inertial
  wait(200, msec);
  DrivetrainInertial.calibrate();
  Brain.Screen.print("Calibrating Inertial for Drivetrain");
  // wait for the Inertial calibration process to finish
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}