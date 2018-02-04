# Pac-ManGL

## About
The project we intend to build is the famed arcade single player game Pac-Man. We intend to savor the original flavor of the game by writing it in C++ using OpenGL-GLFW library. The traditional game has some bugs related to the ghosts we encounter in the game and we intend to make it flawless by fixing those bugs. It will currently consist of a single level following all the constraints of the original PacMan game. Further levels of varying difficulty will be added to the game after the competition. We are bent on including all the features, minor details and the subtle complexities of the original game that drove people crazy for decades.

## CONTRIBUTORS
* Anubhaw Bhalotia
* Mayank Methi
* Shivani Joshi
* Karthik Vedantam

## COMPILE INSTUCTIONS
 
### Add GLFW and GL library to your /usr/include folder
1. Download GLFW source files from http://www.glfw.org/download.html
2. Install Build Dependencies by running sudo apt-get install cmake xorg-dev libglu1-mesa-dev
3. cd in GLFW directory downloaded in step 2
4. Run the command cmake -G "Unix Makefiles" in terminal and then run sudo make and then sudo make install

### Next step is to add glad libraries
1. Copy the glad and KHR folder into /usr/include/
2. Make sure to keep glad.c in the same directory as pacmanGL.cpp

### Compiling the program
1. cd into the cloned directory and run g++ -o pacman pacmanGL.cpp glad.c -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor
2. Run the project by ./pacman


## SCREENSHOTS
![alt tag](https://github.com/CSEC-NITH/Pacman-gl/blob/master/screenshots/Screenshot%20from%202018-02-04%2022-04-42.png)
![alt tag](https://github.com/CSEC-NITH/Pacman-gl/blob/master/screenshots/Screenshot%20from%202018-02-04%2022-04-47.png)
