#include "vex.h"
using namespace vex;
competition Competition;
Drive chassis(vex::motor_group(leftMotorA, leftMotorB, leftMotorC),
              vex::motor_group(rightMotorA, rightMotorB, rightMotorC), PORT17);
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  vexcodeInit();
  default_constants();
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/

void autonomous(void) {  
  Park.set(1);
  chassis.drive_distance(495);
  chassis.turn_to_angle(-25);
  chassis.turn_to_angle(360);
  Park.set(0);
  chassis.drive_distance(-150);
  chassis.turn_to_angle(20);
  chassis.drive_distance(300);
  chassis.turn_to_angle(-30);
  Drivetrain.drive(fwd, 100, velocityUnits());
  wait(.7, sec);
  Drivetrain.stop();
  chassis.drive_distance(-500);
  chassis.turn_to_angle(-105);
  Itake.spin(fwd);
  chassis.drive_distance(1400);
  chassis.drive_distance(-200);
  chassis.turn_to_angle(18);
  chassis.drive_distance(550);
  Itake.spin(reverse);
  wait(.2, sec);
  chassis.drive_distance(-235);
  chassis.turn_to_angle(-91);  
  Itake.spin(fwd);
  chassis.drive_distance(500);
  chassis.turn_to_angle(45);

  wingL.set(1);
  wingR.set(1);
  Drivetrain.drive(fwd, 100, velocityUnits());
  wait(.7, sec);
  chassis.drive_distance(-200);
  wingL.set(0);
  wingR.set(0);


  
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
    prints();
    wait(10, msec);
  }
}