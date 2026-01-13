#ifndef MAZE_H
#define MAZE_H

// enum for "states" the Pololu can detect and be in
enum State {
  LINE_FOLLOWER,
  JUNCTION,
  TURN_LEFT,
  TURN_RIGHT,
  U_TURN,
  FINISHED,
  FAKE_END
};

// enum that lets the Pololu display what it is doing
enum Decision {
  EMPTY,
  LEFT,
  RIGHT,
  FORWARD,
  BACK
};

class MazeSolver {
  private:
  State state; // value of type state

  void followLine();

  void checkIfJunction();

  void checkIfDeadEnd();

  void identifyJunction();

  void turnLeft();

  void turnRight();

  void uTurn();

  void Screen();

  void addDecision(Decision d);

  char pathName(Decision name);

  
  public:

    // constructor
    MazeSolver();

    Decision path[64];

    int count = 0; 

    bool isFinished();

    // function to be called at every main loop
    void loop();

};

#endif

