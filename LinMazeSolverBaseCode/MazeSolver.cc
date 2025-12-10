
#include <Pololu3piPlus32U4.h>
#include <PololuMenu.h>

using namespace Pololu3piPlus32U4;

#include "MazeSolver.h"
#include "Shared.h"
MazeSolver::MazeSolver() {
  state = LINE_FOLLOWER;
}

void MazeSolver::followLine() {
  // get position & error
  int16_t position = lineSensors.readLineBlack(lineSensorValues);
  int16_t error = position - 2000;

  // calculate speed difference with PID formula
  int16_t speedDifference = error * (int32_t)proportional / 256 + (error - lastError) * (int32_t)derivative / 256;

  // store error
  lastError = error;

  // get new speed & constrain
  int16_t leftSpeed = (int16_t)baseSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)baseSpeed - speedDifference;
  leftSpeed = constrain(leftSpeed, minSpeed, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, minSpeed, (int16_t)maxSpeed);

  // update motor speed
  motors.setSpeeds(leftSpeed, rightSpeed);
}

void MazeSolver::checkIfPath() {
  if(lineSensorValues[0] > 400 && lineSensorValues[1] > 900 || lineSensorValues[3] > 900 && lineSensorValues[4] > 400){
    state = JUNCTION;
  }
}


bool isLeft = false;
void MazeSolver::pathChange() {
//keeps sensors from accidentally detecting the wrong direction if theres a slight misalignment
  motors.setSpeeds(baseSpeed, baseSpeed);
  delay(100);
  motors.setSpeeds(0, 0);

  lineSensors.readLineBlack(lineSensorValues);

//finish state
  if(lineSensorValues[0] > 900 && lineSensorValues[1] > 900 && lineSensorValues[2] > 900 && lineSensorValues[3] > 900 && lineSensorValues[4] > 900){
    state = FINISHED;
    return;
  }

//left turn state
  if(lineSensorValues[0] > 800 || lineSensorValues[0] > 800 && lineSensorValues[1] > 800){
    state = TURN_LEFT;
    isLeft = true;
    return;
  }

//block turning right
  if(lineSensorValues[3] > 800 && lineSensorValues[4] > 800 && lineSensorValues[2] > 10){
    motors.setSpeeds(baseSpeed, baseSpeed);
    delay(250);
    motors.setSpeeds(0, 0);
    state = LINE_FOLLOWER;
    return;
  }

  else{
    state = LINE_FOLLOWER;
    isLeft = false;
    return;
  }

}

void MazeSolver::turnLeft() {

motors.setSpeeds(minSpeed, maxSpeed);
delay(400);
state = LINE_FOLLOWER;

}

// void MazeSolver::findDeadEnd() {
//   if(lineSensorValues[0] < 10 && lineSensorValues[1] < 10 && lineSensorValues[2] < 10 && lineSensorValues[3] < 10 && lineSensorValues[4] < 10 && isLeft == false){
//     motors.setSpeeds(0, 0);
//     state = U_TURN;
//     return;
//   }
// }

// void MazeSolver::turnAround() {

// motors.setSpeeds(minSpeed, maxSpeed);
// delay(600);
// state = LINE_FOLLOWER;

// }


void MazeSolver::loop() {
  if (state == LINE_FOLLOWER) {
    display.clear();
    display.print(F("LINE"));
    followLine();
    checkIfPath();
    // findDeadEnd();
  }

  if (state == JUNCTION) {
    // call junciton identifier function
    motors.setSpeeds(0, 0);
    display.clear();
    display.print('J');
    pathChange();
  }
  if (state == TURN_LEFT) {
    // call left turn function
    motors.setSpeeds(0, 0);
    display.clear();
    display.print('L');
    turnLeft();
  }
  // if (state == U_TURN) {
  //   // call u turn function
  //   motors.setSpeeds(0, 0);
  //   display.clear();
  //   display.print('U');
  //   // turnAround();
  // }
  if (state == FINISHED) {
    motors.setSpeeds(0, 0);
    display.clear();
    display.print('F');
    return;
  }
}
