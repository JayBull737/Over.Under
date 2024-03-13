using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern smartdrive Drivetrain;
extern motor_group LeftDriveSmart;
extern motor leftMotorA;
extern motor leftMotorB;
extern motor leftMotorC;
extern motor_group RightDriveSmart;
extern motor rightMotorA;
extern motor rightMotorB;
extern motor rightMotorC;
extern motor Itake;
extern motor Pun;
extern digital_out wingR;
extern digital_out wingL;
extern digital_out Park;
extern inertial DrivetrainInertial;
extern distance Distance1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );