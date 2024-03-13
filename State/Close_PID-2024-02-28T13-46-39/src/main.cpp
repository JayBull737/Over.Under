#include "vex.h"
using namespace vex;
competition Competition;
Drive chassis(vex::motor_group(leftMotorA, leftMotorB, leftMotorC),
              vex::motor_group(rightMotorA, rightMotorB, rightMotorC), PORT17);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  WinPoint();
  //Tourney();
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  Drivetrain.setStopping(brake);
  while (1) {
    usertime();
    wait(10, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    Controller1.Screen.setCursor(1, 1);
    int avgmotemp = LeftDriveSmart.temperature()+RightDriveSmart.temperature()/2;
    Controller1.Screen.print(avgmotemp);
    //Controller1.Screen.print(Distance1.objectDistance(mm));
    prints();
    wait(10, msec);
    Controller1.Screen.clearLine();
  }
}