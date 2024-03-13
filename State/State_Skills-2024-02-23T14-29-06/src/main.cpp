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
  // pushing under both the reds
  RightDriveSmart.spin(reverse, 50, velocityUnits());
  LeftDriveSmart.spin(reverse, 100, velocityUnits());
  wait(.95, sec);
  stopall();
  chassis.turn_to_angle(40);
  chassis.drive_distance(490);
  Drivetrain.turn(right, 100, velocityUnits());
  wait(.3, sec);
  Drivetrain.stop();
  Drivetrain.driveFor(120, mm);
  // shooting the triballs
  Pun.spin(reverse);
  void adj();
  adj();
  adj();
  adj();
  adj();
  wait(3.8, sec);
  Pun.stop();
  // done shooting
  Drivetrain.driveFor(reverse, 20, mm);
  chassis.turn_to_angle(360);
  chassis.drive_distance(845);
  chassis.turn_to_angle(-35);
  Itake.spin(fwd);
  chassis.drive_distance(2210);
  chassis.turn_to_angle(-86);
  chassis.drive_distance(900);
  chassis.turn_to_angle(-135);
  Drivetrain.drive(fwd, 100, velocityUnits());
  wait(.55, sec);
  Drivetrain.stop();
  chassis.drive_distance(-420);
  chassis.turn_to_angle(148);
  // infront of curve
  Itake.stop();
  chassis.drive_distance(1150);
  chassis.turn_to_angle(-137);
  chassis.drive_distance(340);  
  wingL.set(1);
  RightDriveSmart.spin(forward, 100, velocityUnits());
  wait(.55, sec);
  stopall();
  chassis.turn_to_angle(-59);
  bothwings(1);
  chassis.drive_distance(-230);
  Itake.spin(reverse);
  RightDriveSmart.spin(fwd, 90, velocityUnits());
  LeftDriveSmart.spin(fwd, 76, velocityUnits());
  wait(1.25, sec);
  stopall();
  bothwings(0);
  wait(.2, sec);
  chassis.drive_distance(-500);
  Itake.stop();
  RightDriveSmart.spin(reverse, 100, velocityUnits());
  LeftDriveSmart.spin(reverse, 25, velocityUnits());
  wait(.6, sec);
  stopall();
  wait(20, msec);
  chassis.turn_to_angle(-135);
  chassis.drive_distance(-600);
  chassis.turn_to_angle(-142);
  //left front push
  chassis.drive_distance(1970);
  chassis.turn_to_angle(-30);
  wingR.set(1);
  chassis.drive_distance(140); 
  bothwings(1);
  chassis.turn_to_angle(10);  
  chassis.drive_distance(600);
  chassis.turn_to_angle(-45); 
  wait(60, msec);
  Drivetrain.drive(fwd, 100, velocityUnits());
  wait(1, sec);
  Drivetrain.stop();  
  bothwings(0);
  chassis.drive_distance(-200);
  Park.set(1);
  RightDriveSmart.spin(reverse, 100, velocityUnits());
  LeftDriveSmart.spin(reverse, 22, velocityUnits());
  wait(1, sec);
  stopall();
  chassis.turn_to_angle(138);
  chassis.drive_distance(-640);
  Park.set(0);
  chassis.drive_distance(600);
  // Other corner push
  chassis.turn_to_angle(-111.5);
  chassis.drive_distance(2000);
  chassis.turn_to_angle(180);
  chassis.drive_distance(-500);
  RightDriveSmart.spin(reverse, 13, velocityUnits());
  LeftDriveSmart.spin(reverse, 100, velocityUnits());
  wait(1, sec);
  stopall();
  Itake.spin(reverse);
  chassis.turn_to_angle(-135);
  chassis.drive_distance(150);
  chassis.drive_distance(-325);
  chassis.drive_distance(200);
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
    prints();
    wait(10, msec);
    Controller1.Screen.clearLine();
  }
}