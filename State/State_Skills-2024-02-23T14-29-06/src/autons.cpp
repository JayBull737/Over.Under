#include "vex.h"

extern Drive chassis;

void default_constants() {
  chassis.set_drive_constants(50, 1.0, 0, 1.0, 0);
  chassis.set_heading_constants(50, 1.0, 0, 0, 0);
  chassis.set_turn_constants(50, 1.0, 0, 8.0, 0);
  chassis.set_swing_constants(50, 1.0, 0, 8.0, 0);
  chassis.set_drive_exit_conditions(25, 200, 5000);
  chassis.set_turn_exit_conditions(5, 300, 3000);
  chassis.set_swing_exit_conditions(3, 300, 3000);
  Itake.setVelocity(100, percent);
  Pun.setVelocity(57, percent);
  Pun.setMaxTorque(100, percent);
}

void adj() {
  Drivetrain.drive(fwd, .45, velocityUnits());
  Drivetrain.turnToRotation(118, degrees);
  wait(5, seconds);
}

void stopall() {
  RightDriveSmart.stop();
  LeftDriveSmart.stop();
  RightDriveSmart.setVelocity(100, percentUnits());
  LeftDriveSmart.setVelocity(100, percentUnits());
}

void bothwings(const float &value) {
  wingL.set(value);
  wingR.set(value);
}

void usertime() {
    if (Controller1.ButtonR2.pressing()) {
      Pun.spin(reverse);
    } else {
      Pun.stop();
    }
    if (Controller1.ButtonX.pressing()) {
      wingR.set(true);
      wingL.set(true);
    } else if (Controller1.ButtonB.pressing()) {
      wingR.set(false);
      wingL.set(false);
    }
    if (Controller1.ButtonA.pressing()) {
      wingR.set(true);
    } else {} ;
    
    
    

}

void prints() {
    int x = Brain.Screen.xPosition();
    int y = Brain.Screen.yPosition();
    if (Brain.Screen.pressing()) {
      Brain.Screen.drawRectangle(x - 6, y - 35, 10, 15, white);
      Brain.Screen.drawRectangle(x - 21, y - 32, 10, 15, white);
      Brain.Screen.drawRectangle(x + 9, y - 32, 10, 15, white);
      Brain.Screen.drawRectangle(x - 12, y - 18, 22, 30, white);
    }
  }

  void Drawing() {
    Brain.Screen.setPenColor(transparent);

    Brain.Screen.drawRectangle(0, 0, 480, 240, white);
    Brain.Screen.drawCircle(480, 120, 120, black);
    Brain.Screen.drawCircle(0, 120, 120, black);
    Brain.Screen.drawCircle(440, 120, 120, green);
    Brain.Screen.drawCircle(40, 120, 120, green);
    Brain.Screen.drawCircle(400, 120, 120, black);
    Brain.Screen.drawCircle(80, 120, 120, black);
    Brain.Screen.drawCircle(360, 120, 120, green);
    Brain.Screen.drawCircle(120, 120, 120, green);
    Brain.Screen.drawCircle(320, 120, 120, black);
    Brain.Screen.drawCircle(160, 120, 120, black);
    Brain.Screen.drawCircle(280, 120, 120, green);
    Brain.Screen.drawCircle(200, 120, 120, green);
    Brain.Screen.drawCircle(240, 120, 120, black);
    Brain.Screen.drawCircle(240, 120, 85, green);
    Brain.Screen.drawCircle(240, 120, 55, black);
    Brain.Screen.drawCircle(240, 120, 20, green);
  }