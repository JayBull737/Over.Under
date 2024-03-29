#include "vex.h"

Drive::Drive(vex::motor_group LeftDriveSmart, vex::motor_group RightDriveSmart,
             int DrivetrainInertial_port)
    : LeftDriveSmart(LeftDriveSmart), RightDriveSmart(RightDriveSmart),
      DrivetrainInertial(inertial(DrivetrainInertial_port)){};

void Drive::drive_with_voltage(float leftVoltage, float rightVoltage) {
  LeftDriveSmart.spin(fwd, leftVoltage, volt);
  RightDriveSmart.spin(fwd, rightVoltage, volt);
}

void Drive::set_turn_constants(float turn_max_voltage, float turn_kp,
                               float turn_ki, float turn_kd,
                               float turn_starti) {
  this->turn_max_voltage = turn_max_voltage;
  this->turn_kp = turn_kp;
  this->turn_ki = turn_ki;
  this->turn_kd = turn_kd;
  this->turn_starti = turn_starti;
}

void Drive::set_drive_constants(float drive_max_voltage, float drive_kp,
                                float drive_ki, float drive_kd,
                                float drive_starti) {
  this->drive_max_voltage = drive_max_voltage;
  this->drive_kp = drive_kp;
  this->drive_ki = drive_ki;
  this->drive_kd = drive_kd;
  this->drive_starti = drive_starti;
}

void Drive::set_heading_constants(float heading_max_voltage, float heading_kp,
                                  float heading_ki, float heading_kd,
                                  float heading_starti) {
  this->heading_max_voltage = heading_max_voltage;
  this->heading_kp = heading_kp;
  this->heading_ki = heading_ki;
  this->heading_kd = heading_kd;
  this->heading_starti = heading_starti;
}

void Drive::set_swing_constants(float swing_max_voltage, float swing_kp,
                                float swing_ki, float swing_kd,
                                float swing_starti) {
  this->swing_max_voltage = swing_max_voltage;
  this->swing_kp = swing_kp;
  this->swing_ki = swing_ki;
  this->swing_kd = swing_kd;
  this->swing_starti = swing_starti;
}

void Drive::set_turn_exit_conditions(float turn_settle_error,
                                     float turn_settle_time,
                                     float turn_timeout) {
  this->turn_settle_error = turn_settle_error;
  this->turn_settle_time = turn_settle_time;
  this->turn_timeout = turn_timeout;
}

void Drive::set_drive_exit_conditions(float drive_settle_error,
                                      float drive_settle_time,
                                      float drive_timeout) {
  this->drive_settle_error = drive_settle_error;
  this->drive_settle_time = drive_settle_time;
  this->drive_timeout = drive_timeout;
}

void Drive::set_swing_exit_conditions(float swing_settle_error,
                                      float swing_settle_time,
                                      float swing_timeout) {
  this->swing_settle_error = swing_settle_error;
  this->swing_settle_time = swing_settle_time;
  this->swing_timeout = swing_timeout;
}

float Drive::get_absolute_heading() {
  return (reduce_0_to_360(DrivetrainInertial.rotation()));
}

float Drive::get_left_position_in() {
  return ((leftMotorA.position(deg) + leftMotorB.position(deg) +
           leftMotorC.position(deg) / 3) *
          0.7);
}

float Drive::get_right_position_in() {
  return ((rightMotorA.position(deg) + rightMotorB.position(deg) +
           rightMotorC.position(deg) / 3) *
          0.7);
}

void Drive::turn_to_angle(float angle) {
  turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time,
                turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void Drive::turn_to_angle(float angle, float turn_max_voltage) {
  turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time,
                turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void Drive::turn_to_angle(float angle, float turn_max_voltage,
                          float turn_settle_error, float turn_settle_time,
                          float turn_timeout) {
  turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time,
                turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void Drive::turn_to_angle(float angle, float turn_max_voltage,
                          float turn_settle_error, float turn_settle_time,
                          float turn_timeout, float turn_kp, float turn_ki,
                          float turn_kd, float turn_starti) {
  desired_heading = angle;
  PID turnPID(reduce_negative_180_to_180(angle - get_absolute_heading()),
              turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error,
              turn_settle_time, turn_timeout);
  while (turnPID.is_settled() == false) {
    float error = reduce_negative_180_to_180(angle - get_absolute_heading());
    float output = turnPID.compute(error);
    output = clamp(output, -turn_max_voltage, turn_max_voltage);
    drive_with_voltage(-output, output);
    task::sleep(10);
  }
  LeftDriveSmart.stop(hold);
  RightDriveSmart.stop(hold);
}

void Drive::drive_distance(float distance) {
  drive_distance(distance, desired_heading, drive_max_voltage,
                 heading_max_voltage, drive_settle_error, drive_settle_time,
                 drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti,
                 heading_kp, heading_ki, heading_kd, heading_starti);
}

void Drive::drive_distance(float distance, float heading) {
  drive_distance(distance, heading, drive_max_voltage, heading_max_voltage,
                 drive_settle_error, drive_settle_time, drive_timeout, drive_kp,
                 drive_ki, drive_kd, drive_starti, heading_kp, heading_ki,
                 heading_kd, heading_starti);
}

void Drive::drive_distance(float distance, float heading,
                           float drive_max_voltage, float heading_max_voltage,
                           float drive_settle_error, float drive_settle_time,
                           float drive_timeout, float drive_kp, float drive_ki,
                           float drive_kd, float drive_starti, float heading_kp,
                           float heading_ki, float heading_kd,
                           float heading_starti) {
  desired_heading = heading;
  PID drivePID(distance, drive_kp, drive_ki, drive_kd, drive_starti,
               drive_settle_error, drive_settle_time, drive_timeout);
  PID headingPID(reduce_negative_180_to_180(heading - get_absolute_heading()),
                 heading_kp, heading_ki, heading_kd, heading_starti);
  float start_average_position =
      (get_left_position_in() + get_right_position_in()) / 2.0;
  float average_position = start_average_position;
  while (drivePID.is_settled() == false) {
    average_position = (get_left_position_in() + get_right_position_in()) / 2.0;
    float drive_error = distance + start_average_position - average_position;
    float heading_error =
        reduce_negative_180_to_180(heading - get_absolute_heading());
    float drive_output = drivePID.compute(drive_error);
    float heading_output = headingPID.compute(heading_error);

    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage);
    heading_output =
        clamp(heading_output, -heading_max_voltage, heading_max_voltage);

    drive_with_voltage(drive_output - heading_output,
                       drive_output + heading_output);
    task::sleep(10);
  }
  LeftDriveSmart.stop(hold);
  RightDriveSmart.stop(hold);
}

void Drive::left_swing_to_angle(float angle) {
  left_swing_to_angle(angle, swing_max_voltage, swing_settle_error,
                      swing_settle_time, swing_timeout, swing_kp, swing_ki,
                      swing_kd, swing_starti);
}

void Drive::left_swing_to_angle(float angle, float swing_max_voltage,
                                float swing_settle_error,
                                float swing_settle_time, float swing_timeout,
                                float swing_kp, float swing_ki, float swing_kd,
                                float swing_starti) {
  desired_heading = angle;
  PID swingPID(reduce_negative_180_to_180(angle - get_absolute_heading()),
               swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error,
               swing_settle_time, swing_timeout);
  while (swingPID.is_settled() == false) {
    float error = reduce_negative_180_to_180(angle - get_absolute_heading());
    float output = swingPID.compute(error);
    output = clamp(output, -turn_max_voltage, turn_max_voltage);
    LeftDriveSmart.spin(fwd, -output, volt);
    RightDriveSmart.stop(hold);
    task::sleep(10);
  }
  LeftDriveSmart.stop(hold);
  RightDriveSmart.stop(hold);
}

void Drive::right_swing_to_angle(float angle) {
  right_swing_to_angle(angle, swing_max_voltage, swing_settle_error,
                       swing_settle_time, swing_timeout, swing_kp, swing_ki,
                       swing_kd, swing_starti);
}

void Drive::right_swing_to_angle(float angle, float swing_max_voltage,
                                 float swing_settle_error,
                                 float swing_settle_time, float swing_timeout,
                                 float swing_kp, float swing_ki, float swing_kd,
                                 float swing_starti) {
  desired_heading = angle;
  PID swingPID(reduce_negative_180_to_180(angle - get_absolute_heading()),
               swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error,
               swing_settle_time, swing_timeout);
  while (swingPID.is_settled() == false) {
    float error = reduce_negative_180_to_180(angle - get_absolute_heading());
    float output = swingPID.compute(error);
    output = clamp(output, -turn_max_voltage, turn_max_voltage);
    RightDriveSmart.spin(reverse, -output, volt);
    LeftDriveSmart.stop(hold);
    task::sleep(10);
  }
  LeftDriveSmart.stop(hold);
  RightDriveSmart.stop(hold);
}
