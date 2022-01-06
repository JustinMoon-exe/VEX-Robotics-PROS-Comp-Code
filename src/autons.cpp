#include "main.h"

const int DRIVE_SPEED = 122; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries ot heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

///
// Constants
///

// Reset all constants to default (what's in setup.hpp is default)
void
reset_constants() {
  reset_slew_min_power();
  reset_slew_distance();
  reset_fw_drive_constants();
  reset_bw_drive_constants();
  reset_turn_constants();
  reset_turn_i_constants();
  reset_swing_constants();
}

// Functions to change constants
// (if the robot has different weight to it, sometimes we need to change constants)

void
one_mogo_constants() {
  set_slew_min_power(80, 80);
  set_slew_distance(7, 7);
  set_fw_drive_constants(0.45, 5);
  set_bw_drive_constants(0.375, 4);
  set_turn_constants(5, 0.003, 35);
  set_turn_i_constants(15, 30);
  set_swing_constants(12, 35);
}

void
two_mogo_constants() {
  set_slew_min_power(80, 80);
  set_slew_distance(7, 7);
  set_fw_drive_constants(0.45, 5);
  set_bw_drive_constants(0.375, 4);
  set_turn_constants(5, 0.003, 35);
  set_turn_i_constants(15, 30);
  set_swing_constants(12, 35);
}


void
example_auto() {
  // All drive movements use the "set_drive_pid" function
  // the first parameter is the type of motion (drive, turn, r_swing, l_swing)

  // drive example
  // The second parameter is target inches
  // The third parameter is max speed the robot will drive at
  // The fourth parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_drive();

  set_drive_pid(drive, -12, DRIVE_SPEED);
  wait_drive();

  // turn example
  // The second parameter is target degrees
  // The third parameter is max speed the robot will drive at


  set_drive_pid(turn, 90, TURN_SPEED);
  wait_drive();

  set_drive_pid(turn, 45, TURN_SPEED);
  wait_drive();

  // Wait Until and Changing Max Speed
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 12 inches, the robot will travel the remaining distance at a max speed of 40
  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_until(12);
  set_max_speed(40); // After driving 12 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  wait_drive();

  // swing example
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive

  set_drive_pid(l_swing, 45, SWING_SPEED);
  wait_drive();

  set_drive_pid(r_swing, 0, SWING_SPEED);
  wait_drive();
}

////
// R: 2M + Match Loads
////
void
auto_1(){
  pros::Task start_timer(check_for_time);

  start_flipout();

  set_drive_pid(drive, 44, DRIVE_SPEED);
  wait_drive();

  claw_close();

  set_drive_pid(drive, -36, DRIVE_SPEED);
  wait_until(-20);
  claw_open();

  wait_drive();

  set_drive_pid(turn, -33, TURN_SPEED);
  wait_drive();

  set_drive_pid(drive, 44, DRIVE_SPEED);
  wait_drive();

  claw_close();
  wait(100);

  set_drive_pid(drive, -34, DRIVE_SPEED);
  wait_drive(-22);

  claw_open();

  set_drive_pid(drive, -8, DRIVE_SPEED);
  wait_drive();

  set_drive_pid(turn, -90, TURN_SPEED);
  start_mogo_down(200);
  wait_drive();

  set_drive_pid(drive, -30, DRIVE_SPEED);
  wait_drive();

  start_lift_to(400, -120);
  mogo_mid(200);

  set_drive_pid(turn, -135, TURN_SPEED);
  wait_drive();

  start_intake(550);

  set_drive_pid(drive, 12, DRIVE_SPEED);
  wait_drive();

  while(!is_time_up){
    set_drive_pid(drive, 8, DRIVE_SPEED);
    wait_drive();

    set_drive_pid(drive, -8, DRIVE_SPEED);
    wait_drive();
  }

  start_timer.remove();
  stop_intake();
  mogo_down(55);
}

////
// L: 1M + Match Loads
////
void
auto_2(){

  set_heading_constants(8, 20);
  set_slew_min_power(100, 100);
  set_slew_distance(6, 6);
  set_drive_pid(drive, 24, DRIVE_SPEED, true);
  wait_drive();


  set_drive_pid(drive, -24, DRIVE_SPEED, true);
  wait_drive();

  set_heading_constants(8, 24);
  set_drive_pid(drive, 24, DRIVE_SPEED);
  wait_drive();


  set_drive_pid(drive, -24, DRIVE_SPEED);
  wait_drive();
}

////
// R: 1M + Match Load (not letting go of mogo)
////
void
auto_3(){

}

////
// R: 1M + fielding (not letting go of mogo)
////
void
auto_4(){

}

////
// R: 1M (mid) + Match Load
////
void
auto_5(){

}

////
// R: 1M (mid)(fake) + Match Load
////
void
auto_6(){

}

////
// R:
////
void
auto_7(){

}

////
//
////
void
auto_8(){

}

////
//
////
void
auto_9(){

}

////
//
////
void
auto_10(){

}
