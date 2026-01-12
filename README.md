# Pololu 3pi Maze Solving

## Prerequisites
### Software
- [Arduino IDE](https://www.arduino.cc/en/software/)

### Hardware
- [Pololu 3pi+ 32U4](https://www.pololu.com/product/4975)

### Arduino IDE Setup
**To be able to use a Pololu with the Arduino IDE you must install the corresponding board and libraries**
- In the Arduino IDE, open the File menu (Windows/Linux) or the Arduino menu (macOS) and select "Preferences".
- In the Preferences dialog, find the "Additional Boards Manager URLs" text box. Copy and paste the following URL into said box:
*https://files.pololu.com/arduino/package_pololu_index.json*

- In the Arduino IDE's board manager, find and install the *"Pololu A-Star Boards"*
- In the Arduino IDE's library manager, find and install *"Pololu3piPlus32U4"*
- If prompted to install extra dependencies, hit "yes"

[Link to Pololu drivers](https://github.com/pololu/a-star?tab=readme-ov-file*)

## Getting Started
### Software
- Download the maze solving code and open it in the Arduino IDE
***Optional:*** *Modify the ***Proportional*** and ***Derivative*** variables in the ***.ino*** to change the accuracy of the Pololu*
- Upload the code to the Pololu

### Hardware
- Place the Pololu at the start of your maze
- Turn the Pololu on and press the "B" button to calibrate its sensors
- Press "B" to start the Pololu when it is done calibrating and it will start to solve the maze
- When the pololu has reached the finish line, place at back at the start
- Press "B" again and it will now take the shortest route to the finish line

### Code Structure
**The main file, LinMazeSolverBaseCode.ino, includes the setup code for the Pololu, the proportional and derivative values, and the main loop.**

**The 2 classes, MazeSolver and SolutionFollower, work together to guide the Pololu to the correct path**
- MazeSolver has the code to follow the maze, detect junctions, turn around at U turns, and correct mistakes made along the way.
- SolutionFollower takes the vector of decisions from MazeSolver and uses it to go directly to the finish line without ever making a wrong turn.

*The other files are default Pololu files and are required for the code to run.*


### Troubleshooting
**If the Pololu is stuttering:**
- Decrease the proportional value in the .ino

**If the Pololu is incorrectly detecting turns:**
- Move to an area with better lighting
- Decrease the maxSpeed and minSpeed values
- Adjust the proportional and derivative values

**If the Pololu starts spinning randomly, repeats the same mistake, or won't finish the maze:**
- Further troubleshoot by changing the erroring state to FAKE_END in the **MazeSolver.cc** file. This will stop the Pololu and display what values it is detecting to help you figure out what the underlying issue is.