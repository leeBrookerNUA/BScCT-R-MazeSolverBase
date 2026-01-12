#ifndef SOLUTION_H
#define SOLUTION_H

#include "MazeSolver.h"

class SolutionFollower {

  private:
  State state;

  void Screen();

  void followLine();

  void checkIfJunction();

  void identifyJunction();

  void turnLeft();

  void turnRight();


  public:

  void loop();


};

#endif