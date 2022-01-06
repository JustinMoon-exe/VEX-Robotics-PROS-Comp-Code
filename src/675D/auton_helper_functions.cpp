#include "main.h"

bool is_time_up = false;

void claw_open(){
  clamp.set_value(true);
  clamp_current_state = true;
}
void claw_close(){
  clamp.set_value(false);
  clamp_current_state = false;
}

void start_mogo_down(int speed){
  mogo.move_absolute(mogo_bottom_pos, speed);
}
void start_mogo_mid(int speed){
  mogo.move_absolute(mogo_mid_pos, speed);
}
void start_mogo_up(){
  mogo.move_absolute(mogo_start_pos, 200);
}

void mogo_down(int speed){
  mogo.move_absolute(mogo_bottom_pos, speed);
  while(mogo.get_position() < (mogo_bottom_pos - 3)){
    wait(2);
  }
}
void mogo_mid(int speed){
  mogo.move_absolute(mogo_mid_pos, speed);
  while(mogo.get_position() > (mogo_mid_pos + 3)){
    wait(2);
  }
}
void mogo_up(){
  mogo.move_absolute(mogo_start_pos, 200);
  while(mogo.get_position() > (mogo_start_pos + 3)){
    wait(2);
  }
}

void start_lift_to(int pos, int speed){
  lift_l.move_absolute(-pos, speed);
  lift_r.move_absolute(-pos, speed);
}
void lift_to(int pos, int speed){
  lift_l.move_absolute(-pos, speed);
  lift_r.move_absolute(-pos, speed);

  while(fabs(lift_l.get_position() - lift_l.get_target_position()) > 2){
    wait(2);
  }
}

void start_intake(int speed){
  conveyor.move_velocity(speed);
}
void stop_intake(){
  conveyor.move_velocity(0);
}
void start_intake_for(int deg, int speed){
  conveyor.move_relative(deg, speed);
}

void intake_for(int deg, int speed){
  conveyor.tare_position();
  conveyor.move_absolute(deg, speed);

  while(fabs(conveyor.get_position() - conveyor.get_target_position()) > 2){
    wait(2);
  }
}

void wait(int time){
  pros::delay(time);
}

void start_flipout(){
  claw_open();
  start_intake_for(-350, 600);
}

int check_for_time(){
  is_time_up = false;
  wait(12000);
  is_time_up = true;
  master.rumble("---");
  return 1;
}
