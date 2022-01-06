#include "main.h"

//CONSTANTS / Hard-Coded Values
//Radius of tracking wheels in inches
double WHEEL_RADIUS = 4.15; //was 1.379 //1.43

//Starting angle (relative to field) (RADIANS)
double THETA_START = 0; //M_PI; //imagine the field is a unit circle

//The starting x and y coordinates of the bot (INCHES)
  //These distances are relative to some point (0,0) on the field
double X_START = 0.0;
double Y_START = 0.0;

//Distances of tracking wheels from tracking center (INCHES)
double LTrackRadius = 6.35;
double RTrackRadius = 6.35;
double STrackRadius = 0.842;

//Calculated Values (every loop)
//Angles (DEGREES) *NEEDS TO BE CONVERTED TO RADIANS FOR MATH*
double LPos = 0;
double RPos = 0;
double SPos = 0;

double LPrevPos = 0;
double RPrevPos = 0;
double SPrevPos = 0;

//Distances traveled by tracking wheels each loop (INCHES)
double deltaDistL = 0;
double deltaDistR = 0;
double deltaDistS = 0;

//Distance summations (since last reset)
double totalDeltaDistL = 0;
double totalDeltaDistR = 0;

//The current angle of the bot (RADIANS)
double currentAbsoluteOrientation = THETA_START;
int angleGlobal = 0;
//The previous angle of the bot (RADIANS)
double previousTheta = THETA_START;

//The change in Theta each loop (RADIANS)
double deltaTheta = 0;

//The Average angle Theta (In RADIANS) throughout the arc
  //currentAbsoluteOrientation + (deltaTheta / 2)
double avgThetaForArc = currentAbsoluteOrientation + (deltaTheta / 2);

//The changes in the X and Y positions (INCHES)
/*These are calculated on a local basis each loop,
then converted to global position changes */
double deltaXLocal = 0;
double deltaYLocal = 0;

//The X and Y offsets converted from their local forms (INCHES)
double deltaXGlobal = 0;
double deltaYGlobal = 0;

//The global position of the bot (INCHES)
double xPosGlobal = X_START;
double yPosGlobal = Y_START;

int odometry_control(){
  while(true){
    //Get encoder values (DEGREES)

    LPos = -l_motor.get_position();
    RPos = r_motor.get_position();
    //SPos = tracker_back.get_value();

    //Calculate distance traveled by tracking each wheel (INCHES)
      //Converts degrees to radians
    deltaDistL = ((LPos - LPrevPos) * M_PI / 180) * WHEEL_RADIUS;
    deltaDistR = ((RPos - RPrevPos) * M_PI / 180) * WHEEL_RADIUS;
    //deltaDistS = ((SPos - SPrevPos) * M_PI / 180) * WHEEL_RADIUS;

    //Update previous values to be used next loop (DEGREES)
    LPrevPos = LPos;
    RPrevPos = RPos;
    //SPrevPos = SPos;

    //Total change in each of the L and R encoders since last reset (INCHES)
    //These are used to calculate the absolute orientation of the bot
    totalDeltaDistL += deltaDistL;
    totalDeltaDistR += deltaDistR;

    //Calculate the current absolute orientation (RADIANS)
    currentAbsoluteOrientation =  (M_PI*get_gyro())/180; //THETA_START - ( (totalDeltaDistL - totalDeltaDistR) / (LTrackRadius + RTrackRadius) );

    //Calculate the change in the angle of the bot (RADIANS)
    deltaTheta = currentAbsoluteOrientation - previousTheta;

    //Update the previous Theta value (RADIANS)
    previousTheta = currentAbsoluteOrientation;

    //If we didn't turn, then we only translated
    if(deltaTheta == 0) {
      deltaXLocal = deltaDistS;
      // could be either L or R, since if deltaTheta == 0 we assume they're =
      deltaYLocal = deltaDistL;
    }
    //Else, caluclate the new local position
    else {
      //Calculate the changes in the X and Y values (INCHES)
      //General equation is:
        //Distance = 2 * Radius * sin(deltaTheta / 2)
      deltaXLocal = 2 * sin(deltaTheta / 2.0) * ((deltaDistS / deltaTheta) + STrackRadius);
      deltaYLocal = 2 * sin(deltaTheta / 2.0) * ((deltaDistR / deltaTheta) - RTrackRadius);

    }

    //The average angle of the robot during it's arc (RADIANS)
    avgThetaForArc = currentAbsoluteOrientation - (deltaTheta / 2);

    deltaXGlobal = (deltaYLocal * cos(avgThetaForArc)) - (deltaXLocal * sin(avgThetaForArc));
    deltaYGlobal = (deltaYLocal * sin(avgThetaForArc)) + (deltaXLocal * cos(avgThetaForArc));

    //Wraps angles back around if they ever go under 0 or over 2 pi
    while(currentAbsoluteOrientation >= 2 * M_PI) {
      currentAbsoluteOrientation -= 2 * M_PI;
    }

    while(currentAbsoluteOrientation < 0) {
      currentAbsoluteOrientation += 2 * M_PI;
    }

    //Update global positions
    xPosGlobal += deltaXGlobal;
    yPosGlobal += deltaYGlobal;

    angleGlobal = int((180*currentAbsoluteOrientation)/M_PI);




    pros::delay(5);
  }

  return 1;
}

void print_tracker_pos_to_screen(){
  pros::lcd::clear_line(3);
  pros::lcd::clear_line(4);
  pros::lcd::set_text(3, "left: " + std::to_string(tracker_left.get_value()) + "right: " + std::to_string(tracker_right.get_value()));
  pros::lcd::set_text(4, "back: " + std::to_string(tracker_back.get_value()));
}

void print_robot_pos_to_screen(){
  pros::lcd::clear_line(0);
  pros::lcd::clear_line(1);
  pros::lcd::set_text(0, "X: " + std::to_string(yPosGlobal) + " Y: " + std::to_string(xPosGlobal));
  pros::lcd::set_text(1, "angle: " + std::to_string(angleGlobal));
}
