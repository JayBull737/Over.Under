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
  Pun.setVelocity(49, percent);
  Pun.setMaxTorque(100, percent);
}

void stopall() {
  RightDriveSmart.stop();
  LeftDriveSmart.stop();
}

void bothwings(const float &value) {
  wingL.set(value);
  wingR.set(value);
}

void usertime() {
  float throttle = deadband(controller(primary).Axis3.value(), 5);
  float turn = deadband(controller(primary).Axis1.value(), 5);
  LeftDriveSmart.spin(fwd, to_volt(throttle-turn), volt);
  RightDriveSmart.spin(fwd, to_volt(throttle+turn), volt);
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
      Park.set(true);
     } else if (Controller1.ButtonY.pressing()) {
      Park.set(false);
    }

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

void WinPoint() {
  chassis.drive_distance(-200);
  Park.set(1);
  wait(0.2,seconds);
  chassis.drive_distance(500);
  chassis.turn_to_angle(-15);
  Itake.spin(reverse);
  Park.set(0);
  chassis.drive_distance(-300);
  chassis.turn_to_angle(10);
  chassis.drive_distance(500);
  chassis.turn_to_angle(-30);
  chassis.drive_distance(200);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(385);
  wait(0.5,seconds);
  Itake.stop();
}

void Tourney() {
  Itake.spin(fwd);
  // drive to middle
  chassis.drive_distance(1540);
  chassis.drive_distance(-180);
  // push triball over middle
  chassis.turn_to_angle(75);
  wingL.set(1);
  chassis.drive_distance(620);
  wingL.set(1);
  chassis.turn_to_angle(20);
  wingL.set(0);
  // drive to matchload bar
  chassis.drive_distance(-1570);
  chassis.turn_to_angle(119);
  // get triball out of corner
  chassis.drive_distance(-300);
  Park.set(1);
  wait(0.2,seconds);
  chassis.drive_distance(450);
  chassis.turn_to_angle(65);
  Park.set(0);
  chassis.drive_distance(-200);
  chassis.turn_to_angle(110);
  chassis.drive_distance(500);
  chassis.turn_to_angle(80);
  chassis.drive_distance(200);
  Itake.spin(reverse);
  chassis.turn_to_angle(66);
  chassis.drive_distance(510);
  wait(0.5,seconds);
  Itake.stop();
}
