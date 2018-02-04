#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<bits/stdc++.h>
#include<unistd.h> 

using namespace std;
#define HEIGHT 288
#define WIDTH 512
#define TILE 8
void attachPacman();
void attachPacmanRight();
void attachPacmanLeft();
void attachPacmanDown();
void attachPacmanUp();
void attachGhost();
void attachReferenceLines();
void attachCoins();
void drawPacman();
void drawGhost();
void drawCoins();
void drawWall();
void drawPacmanLeft();
void drawPacmanUp();
void drawPacmanRight();
void drawPacmanDown();
void drawReferenceLines();
void displayStablePacman();
void movePacmanLogic();
void movePacman();
void changeMode();
void moveBlinkyLogic0();
void moveBlinky();
void movePinkyLogic0();
void movePinky();
void moveInkyLogic0();
void moveInky();
void attachvao1();
void attachvao2();
void attachvao3();
void attachvao4();
void drawBigCoin1();
void drawBigCoin2();
void drawBigCoin3();
void drawBigCoin4();
void charPrint(float,float,char);
void checkGameOver();
void gameOverWindow(int);
void attachScore();
void drawStart(GLFWwindow*);
void moveClinkyLogic0();
void moveClinky();
void youWin();
int countFrame=0;
int soundd=5;
int gameOver=0;
float tempx=2.0/512 , tempy=2.0/288;
int currMode=0,lastMode=0,minn,minnCount;
float frameRate=88;
float lastPacmanMoveTime, currTime,lastBlinkyMoveTime,lastGhostMoveTime,lastModeChangeTime;
float pacmanSpeed=(int)(0.8*frameRate),ghostSpeed=(int)(0.45*frameRate),blinkySpeed=(int)(0.55*frameRate);
int i,j,nextState,last[2],clearCounter=0,boxCountArray[4];
float x,y,length[4];
int pacmanCentre[2],blinkyCentre[2],pinkyCentre[2],inkyCentre[2],clinkyCentre[2];
int boxCount;
int board[][28]={
/* 00 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 01 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 02 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 03 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 04 */{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
/* 05 */{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
/* 06 */{0,3,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,3,0},
/* 07 */{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
/* 08 */{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
/* 09 */{0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
/* 10 */{0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
/* 11 */{0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
/* 12 */{0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,2,0,0,0,0,0,1,0,0,0,0,0,0},
/* 13 */{0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,2,0,0,0,0,0,1,0,0,0,0,0,0},
/* 14 */{0,0,0,0,0,0,1,0,0,2,2,2,2,2,2,2,2,2,2,0,0,1,0,0,0,0,0,0},
/* 15 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 16 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 17 */{2,2,2,2,2,2,1,2,2,2,0,0,0,0,0,0,0,0,2,2,2,1,2,2,2,2,2,2},
/* 18 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 19 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 20 */{0,0,0,0,0,0,1,0,0,2,2,2,2,2,2,2,2,2,2,0,0,1,0,0,0,0,0,0},
/* 21 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 22 */{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
/* 23 */{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
/* 24 */{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
/* 25 */{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
/* 26 */{0,3,1,1,0,0,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,0,0,1,1,3,0},
/* 27 */{0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
/* 28 */{0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
/* 29 */{0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
/* 30 */{0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
/* 31 */{0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
/* 32 */{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
/* 33 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 34 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
/* 35 */{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int blinkyTargetScatter[2]={26,1};
int pinkyTargetScatter[2]={2,0};
int inkyTargetScatter[2]={28,35};
int clinkyTargetScatter[2]={0,35};
int blinkyTargetChase[2],pinkyTargetChase[2],inkyTargetChase[2],clinkyTargetChase[2];
queue <int> state;
int currState=1,pacmanShape=0,currBlinkyState,currPinkyState,currInkyState,currClinkyState;
long stopForSomeFrame=5 ,score=0;
int wallProgram, pacmanProgram,coinProgram,blinkyProgram,inkyProgram,pinkyProgram,clinkyProgram,referenceLineProgram,textProgram;
int currPacLoc[2],nextPacLoc[2],newPacCentre[2];
int currBlinkyLoc[2],currPinkyLoc[2],currInkyLoc[2],currClinkyLoc[2];
unsigned int vboReferenceLine[2][40],vaoReferenceLine[2][40],vaoWall,vboWall,vaoChar,vboChar;
unsigned int vboPacmanStable,vaoPacmanStable,vaoPacmanRight,vboPacmanRight,vaoPacmanLeft,vboPacmanLeft;
unsigned int vaoGhost,vboGhost,vaoPacmanUp,vboPacmanUp,vaoPacmanDown,vboPacmanDown;
unsigned int vaoCoin[35][28],vboCoin[35][28];
unsigned int vaoCentreLine,vboCentreLine;
unsigned int vaoBigCoin1,vaoBigCoin2,vaoBigCoin3,vaoBigCoin4,vboBigCoin1,vboBigCoin2,vboBigCoin3,vboBigCoin4;
void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
    glViewport(0,0,width,height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(state.empty())
    {
        if(key==GLFW_KEY_UP&& action==GLFW_PRESS && currState!=0)
    {
        state.push(0);
    }
    else if(key==GLFW_KEY_LEFT&& action==GLFW_PRESS && currState!=1)
    {
        state.push(1);
    }
    else if(key==GLFW_KEY_DOWN&& action==GLFW_PRESS && currState!=2)
    {
        state.push(2);
    }
    else if(key==GLFW_KEY_RIGHT&& action==GLFW_PRESS && currState!=3)
    {
        state.push(3);
    }
    }
    else
    {
    
    if(key==GLFW_KEY_UP&& action==GLFW_PRESS && state.back()!=0)
    {
        state.push(0);
    }
    else if(key==GLFW_KEY_LEFT&& action==GLFW_PRESS && state.back()!=1)
    {
        state.push(1);
    }
    else if(key==GLFW_KEY_DOWN&& action==GLFW_PRESS && state.back()!=2)
    {
        state.push(2);
    }
    else if(key==GLFW_KEY_RIGHT&& action==GLFW_PRESS && state.back()!=3)
    {
        state.push(3);
    }
    }
    cout<<state.back()<<endl;

}
void attachPacman()
{
    //cout<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
    float vertices[]={
        
        -1+(x*(pacmanCentre[0]-2)),(1-(y*(pacmanCentre[1]-5))),0.0,
        (-1+(x*(pacmanCentre[0]+2))),(1-(y*(pacmanCentre[1]-5))),0.0,
        -1+(x*(pacmanCentre[0]-4)),(1-(y*(pacmanCentre[1]-4))),0.0,
        (-1+(x*(pacmanCentre[0]+4))),(1-(y*(pacmanCentre[1]-4))),0.0,
        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-3)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-3)),0.0,
        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-2)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-2)),0.0,
        -1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]-1)),0.0,
        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]-1)),0.0,
        -1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1])),0.0,
        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1])),0.0,
        -1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+1)),0.0,
        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+1)),0.0,
        -1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+2)),0.0,
        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+2)),0.0,
        -1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+3)),0.0,
        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+3)),0.0,
        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+4)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+4)),0.0,
        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+5)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+5)),0.0,
        -1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]+6)),0.0,
        -1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]+6)),0.0,
        -1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]+7)),0.0,
        -1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+7)),0.0,
    };
    glBindVertexArray(vaoPacmanStable);
    glBindBuffer(GL_ARRAY_BUFFER,vboPacmanStable);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}
void attachPacmanRight()
{
    
    float vertices[]={
        
        -1+(x*(pacmanCentre[0]-2)),(1-(y*(pacmanCentre[1]-5))),0.0,
        (-1+(x*(pacmanCentre[0]+2))),(1-(y*(pacmanCentre[1]-5))),0.0,

        -1+(x*(pacmanCentre[0]-4)),(1-(y*(pacmanCentre[1]-4))),0.0,
        (-1+(x*(pacmanCentre[0]+4))),(1-(y*(pacmanCentre[1]-4))),0.0,

        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-3)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-3)),0.0,

        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-2)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-2)),0.0,

        -1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]-1)),0.0,
        -1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]-1)),0.0,

        -1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1])),0.0,
        -1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1])),0.0,

        -1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+1)),0.0,
        -1+(x*(pacmanCentre[0]-1)),1-(y*(pacmanCentre[1]+1)),0.0,

        -1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+2)),0.0,
        -1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]+2)),0.0,

        -1+(x*(pacmanCentre[0]-6)),1-(y*(pacmanCentre[1]+3)),0.0,
        -1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]+3)),0.0,

        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+4)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+4)),0.0,

        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+5)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+5)),0.0,

        -1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]+6)),0.0,
        -1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]+6)),0.0,

        -1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]+7)),0.0,
        -1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+7)),0.0,
    };

    glBindVertexArray(vaoPacmanRight);
    glBindBuffer(GL_ARRAY_BUFFER,vboPacmanRight);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}
void attachPacmanLeft()
{
    cout<<"l"<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
    float vertices[]={
        
        -1+(x*(pacmanCentre[0]-2)),(1-(y*(pacmanCentre[1]-5))),0.0,
        (-1+(x*(pacmanCentre[0]+2))),(1-(y*(pacmanCentre[1]-5))),0.0,

        -1+(x*(pacmanCentre[0]-4)),(1-(y*(pacmanCentre[1]-4))),0.0,
        (-1+(x*(pacmanCentre[0]+4))),(1-(y*(pacmanCentre[1]-4))),0.0,

        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-3)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-3)),0.0,

        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]-2)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]-2)),0.0,
        
        -1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]-1)),0.0,
        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]-1)),0.0,

        -1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1])),0.0,
        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1])),0.0,

        -1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+1)),0.0,
        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+1)),0.0,

        -1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]+2)),0.0,
        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+2)),0.0,

        -1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]+3)),0.0,
        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]+3)),0.0,

        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+4)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+4)),0.0,

        -1+(x*(pacmanCentre[0]-5)),1-(y*(pacmanCentre[1]+5)),0.0,
        -1+(x*(pacmanCentre[0]+5)),1-(y*(pacmanCentre[1]+5)),0.0,

        -1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]+6)),0.0,
        -1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]+6)),0.0,

        -1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]+7)),0.0,
        -1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+7)),0.0,
    };
    glBindVertexArray(vaoPacmanLeft);
    glBindBuffer(GL_ARRAY_BUFFER,vboPacmanLeft);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}
void attachPacmanDown()
{
    //cout<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
    float vertices[]={
        
        -1+(x*(pacmanCentre[0]-6)),(1-(y*(pacmanCentre[1]-1))),0.0,
        (-1+(x*(pacmanCentre[0]-6))),(1-(y*(pacmanCentre[1]+2))),0.0,

        -1+(x*(pacmanCentre[0]-5)),(1-(y*(pacmanCentre[1]-3))),0.0,
        (-1+(x*(pacmanCentre[0]-5))),(1-(y*(pacmanCentre[1]+4))),0.0,

        -1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]-4)),0.0,
        -1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]+5)),0.0,
//4
        -1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]-4)),0.0,
        -1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]+5)),0.0,
//5     
        -1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]-5)),0.0,
        -1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]+3)),0.0,
//6
        -1+(x*(pacmanCentre[0]-1)),1-(y*(pacmanCentre[1]-5)),0.0,
        -1+(x*(pacmanCentre[0]-1)),1-(y*(pacmanCentre[1]+1)),0.0,

//7     
        -1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]-5)),0.0,
        -1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]-1)),0.0,
//8
        -1+(x*(pacmanCentre[0]+1)),1-(y*(pacmanCentre[1]-5)),0.0,
        -1+(x*(pacmanCentre[0]+1)),1-(y*(pacmanCentre[1]+1)),0.0,

    //9 
        -1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]-5)),0.0,
        -1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+3)),0.0,

//10
        -1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]-4)),0.0,
        -1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]+5)),0.0,

        -1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]-4)),0.0,
        -1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]+5)),0.0,

    
        -1+(x*(pacmanCentre[0]+5)),(1-(y*(pacmanCentre[1]-3))),0.0,
        (-1+(x*(pacmanCentre[0]+5))),(1-(y*(pacmanCentre[1]+4))),0.0,


        -1+(x*(pacmanCentre[0]+6)),(1-(y*(pacmanCentre[1]-1))),0.0,
        (-1+(x*(pacmanCentre[0]+6))),(1-(y*(pacmanCentre[1]+2))),0.0,
    };
    glBindVertexArray(vaoPacmanDown);
    glBindBuffer(GL_ARRAY_BUFFER,vboPacmanDown);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}
void attachPacmanUp()
{
    float vertices[]={
        -1+(x*(pacmanCentre[0]-6)),(1-(y*(pacmanCentre[1]-1))),0.0,
        (-1+(x*(pacmanCentre[0]-6))),(1-(y*(pacmanCentre[1]+2))),0.0,

        -1+(x*(pacmanCentre[0]-5)),(1-(y*(pacmanCentre[1]-3))),0.0,
        (-1+(x*(pacmanCentre[0]-5))),(1-(y*(pacmanCentre[1]+4))),0.0,

        -1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]-5)),0.0,
        -1+(x*(pacmanCentre[0]-4)),1-(y*(pacmanCentre[1]+5)),0.0,
//4
        -1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]-5)),0.0,
        -1+(x*(pacmanCentre[0]-3)),1-(y*(pacmanCentre[1]+5)),0.0,
//5     
        -1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]-3)),0.0,
        -1+(x*(pacmanCentre[0]-2)),1-(y*(pacmanCentre[1]+5)),0.0,
//6
        -1+(x*(pacmanCentre[0]-1)),1-(y*(pacmanCentre[1]-1)),0.0,
        -1+(x*(pacmanCentre[0]-1)),1-(y*(pacmanCentre[1]+5)),0.0,

//7     
        -1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]+1)),0.0,
        -1+(x*(pacmanCentre[0])),1-(y*(pacmanCentre[1]+5)),0.0,
//8
        -1+(x*(pacmanCentre[0]+1)),1-(y*(pacmanCentre[1]-1)),0.0,
        -1+(x*(pacmanCentre[0]+1)),1-(y*(pacmanCentre[1]+5)),0.0,

    //9 
        -1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]-3)),0.0,
        -1+(x*(pacmanCentre[0]+2)),1-(y*(pacmanCentre[1]+5)),0.0,  //edited a bit

//10
        -1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]-5)),0.0,
        -1+(x*(pacmanCentre[0]+3)),1-(y*(pacmanCentre[1]+5)),0.0,

        -1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]-5)),0.0,
        -1+(x*(pacmanCentre[0]+4)),1-(y*(pacmanCentre[1]+4)),0.0,

    
        -1+(x*(pacmanCentre[0]+5)),(1-(y*(pacmanCentre[1]-4))),0.0,
        (-1+(x*(pacmanCentre[0]+5))),(1-(y*(pacmanCentre[1]+3))),0.0,


        -1+(x*(pacmanCentre[0]+6)),1-(y*(pacmanCentre[1]-2)),0.0,
        (-1+(x*(pacmanCentre[0]+6))),(1-(y*(pacmanCentre[1]+2))),0.0,
    };
    glBindVertexArray(vaoPacmanUp);
    glBindBuffer(GL_ARRAY_BUFFER,vboPacmanUp);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}   
void attachvao1(){
    float verticesvao1[]={
      -0.390625 , 0.666667 , 0.0 , 
     -0.40625 , 0.638889 , 0.0 , 
      -0.390625 , 0.611111 , 0.0 , 
      -0.390625 , 0.666667 , 0.0 , 
     -0.390625 , 0.611111 , 0.0 , 
       -0.375 , 0.638889 , 0.0 
    };
      glBindVertexArray(vaoBigCoin1);
        glBindBuffer(GL_ARRAY_BUFFER,vboBigCoin1);
        glBufferData(GL_ARRAY_BUFFER,sizeof(verticesvao1),verticesvao1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 

    
}

void drawBigCoin1(){
    glUseProgram(coinProgram);
    glBindVertexArray(vaoBigCoin1);
    glDrawArrays(GL_TRIANGLES,0,2000);
}

void attachvao2(){
    float verticesvao2[]={
      -0.390625 , -0.444444 , 0.0 , 
-0.40625 , -0.472222 , 0.0 , 
-0.390625 , -0.5 , 0.0 , 
-0.390625 , -0.5 , 0.0 , 
-0.390625 , -0.444444 , 0.0 , 
-0.375 , -0.472222 , 0.0 ,
    };
      glBindVertexArray(vaoBigCoin2);
        glBindBuffer(GL_ARRAY_BUFFER,vboBigCoin2);
        glBufferData(GL_ARRAY_BUFFER,sizeof(verticesvao2),verticesvao2,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 

    
}

void drawBigCoin2(){
    glUseProgram(coinProgram);
    glBindVertexArray(vaoBigCoin2);
    glLineWidth(1.0);
    glDrawArrays(GL_TRIANGLES,0,2000);
}

void attachvao3(){
    float verticesvao3[]={
    0.390625 , 0.666667 , 0.0 , 
0.40625 , 0.638889 , 0.0 , 
0.390625 , 0.611111 , 0.0 , 
0.390625 , 0.666667 , 0.0 , 
0.390625 , 0.611111 , 0.0 , 
0.375 , 0.638889 , 0.0 
    };
      glBindVertexArray(vaoBigCoin3);
        glBindBuffer(GL_ARRAY_BUFFER,vboBigCoin3);
        glBufferData(GL_ARRAY_BUFFER,sizeof(verticesvao3),verticesvao3,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 

    
}

void drawBigCoin3(){
    glUseProgram(coinProgram);
    glBindVertexArray(vaoBigCoin3);
    glDrawArrays(GL_TRIANGLES,0,2000);
}

void attachvao4(){
    float verticesvao4[]={
    0.390625 , -0.444444 , 0.0 , 
0.40625 , -0.472222 , 0.0 , 
0.390625 , -0.5 , 0.0 , 
0.390625 , -0.5 , 0.0 , 
0.390625 , -0.444444 , 0.0 , 
0.375 , -0.472222 , 0.0
    };
      glBindVertexArray(vaoBigCoin4);
        glBindBuffer(GL_ARRAY_BUFFER,vboBigCoin4);
        glBufferData(GL_ARRAY_BUFFER,sizeof(verticesvao4),verticesvao4,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 

    
}

void drawBigCoin4(){
    glUseProgram(coinProgram);
    glBindVertexArray(vaoBigCoin4);
    glLineWidth(1.0);
    glDrawArrays(GL_TRIANGLES,0,2000);
}
void attachGhost(int ghostCentre[])
{
    cout<<"ghostCentre "<<ghostCentre[0]<<" "<<ghostCentre[1]<<endl;
    float vertices[]={
        -1+(x*(ghostCentre[0]-6)),1-(y*(ghostCentre[1]-0)),0.0,-1+(x*(ghostCentre[0]-6)),1-(y*(ghostCentre[1]+7)),0.0,
        -1+(x*(ghostCentre[0]-5)),1-(y*(ghostCentre[1]-3)),0.0,-1+(x*(ghostCentre[0]-5)),1-(y*(ghostCentre[1]+6)),0.0,
        -1+(x*(ghostCentre[0]-4)),1-(y*(ghostCentre[1]-4)),0.0,-1+(x*(ghostCentre[0]-4)),1-(y*(ghostCentre[1]+5)),0.0,
        -1+(x*(ghostCentre[0]-3)),1-(y*(ghostCentre[1]-5)),0.0,-1+(x*(ghostCentre[0]-3)),1-(y*(ghostCentre[1]+6)),0.0,
        -1+(x*(ghostCentre[0]-2)),1-(y*(ghostCentre[1]-5)),0.0,-1+(x*(ghostCentre[0]-2)),1-(y*(ghostCentre[1]+7)),0.0,
        -1+(x*(ghostCentre[0]-1)),1-(y*(ghostCentre[1]-6)),0.0,-1+(x*(ghostCentre[0]-1)),1-(y*(ghostCentre[1]+7)),0.0,
        -1+(x*(ghostCentre[0]-0)),1-(y*(ghostCentre[1]-6)),0.0,-1+(x*(ghostCentre[0]-0)),1-(y*(ghostCentre[1]+5)),0.0,
        -1+(x*(ghostCentre[0]+1)),1-(y*(ghostCentre[1]-6)),0.0,-1+(x*(ghostCentre[0]+1)),1-(y*(ghostCentre[1]+5)),0.0,
        -1+(x*(ghostCentre[0]+2)),1-(y*(ghostCentre[1]-6)),0.0,-1+(x*(ghostCentre[0]+2)),1-(y*(ghostCentre[1]+7)),0.0,
        -1+(x*(ghostCentre[0]+3)),1-(y*(ghostCentre[1]-5)),0.0,-1+(x*(ghostCentre[0]+3)),1-(y*(ghostCentre[1]+7)),0.0,
        -1+(x*(ghostCentre[0]+4)),1-(y*(ghostCentre[1]-5)),0.0,-1+(x*(ghostCentre[0]+4)),1-(y*(ghostCentre[1]+6)),0.0,
        -1+(x*(ghostCentre[0]+5)),1-(y*(ghostCentre[1]-4)),0.0,-1+(x*(ghostCentre[0]+5)),1-(y*(ghostCentre[1]+5)),0.0,
        -1+(x*(ghostCentre[0]+6)),1-(y*(ghostCentre[1]-3)),0.0,-1+(x*(ghostCentre[0]+6)),1-(y*(ghostCentre[1]+6)),0.0,
        -1+(x*(ghostCentre[0]+7)),1-(y*(ghostCentre[1]-0)),0.0,-1+(x*(ghostCentre[0]+7)),1-(y*(ghostCentre[1]+7)),0.0,
    };
    glBindVertexArray(vaoGhost);
    glBindBuffer(GL_ARRAY_BUFFER,vboGhost);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

void attachReferenceLines()
{ 
    for(i=0;i<288;i+=8)
    {
        float vertices[]=
        {
            (-1+(x*144)),(1-(y*i)),0.0,
            (-1+(x*368)),(1-(y*i)),0.0
        };
        glBindVertexArray(vaoReferenceLine[0][(i+1)/8]);
        glBindBuffer(GL_ARRAY_BUFFER,vboReferenceLine[0][(i+1)/8]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 
    }
    for(i=144;i<368;i+=8)
    {
        float vertices[]=
        {
            -1+(x*i),-1.0,0.0,
            -1+(x*i),1.0,0.0
        };
        glBindVertexArray(vaoReferenceLine[1][(i-144)/8]);
        glBindBuffer(GL_ARRAY_BUFFER,vboReferenceLine[1][(i-144)/8]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 
    }
}
void attachCoins()
{
    for(i=0;i<35;i++)
    {
        for(j=0;j<28;j++)
        {
            if(board[i][j]==1)
            {
                float vertices[]={
                    -1+(x*((j*8)+144+3)),1-(y*((i*8)+5)),0.0,
                    -1+(x*((j*8)+144+6)),1-(y*((i*8)+5)),0.0,
                };
                glBindVertexArray(vaoCoin[i][j]);
                glBindBuffer(GL_ARRAY_BUFFER,vboCoin[i][j]);
                glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0); 
                glBindVertexArray(0);
            }
        }
    }
    attachvao1();
    attachvao2();
    attachvao3();
    attachvao4();
}

void drawCoins()
{
    for(i=0;i<35;i++)
    {
        for(j=0;j<28;j++)
        {
            if(board[i][j]==1)
            {
                glUseProgram(coinProgram);
                glBindVertexArray(vaoCoin[i][j]);
                glLineWidth(10);
                glDrawArrays(GL_LINES,0,100);
            }
            if(board[6][1]==3)
            {
                
                drawBigCoin1();
            }
            if(board[26][1]==3)
            {
                
                drawBigCoin2();
            }
            if(board[6][26]==3)
            {
                
                drawBigCoin3();
            }
            if(board[26][26]==3)
            {
                
                drawBigCoin4();
            }
        }
    }
}
void drawWall()
{
    glUseProgram(wallProgram);
    glBindVertexArray(vaoWall);
    glLineWidth(2.0);
    glDrawArrays(GL_LINES,0,2000);
    glUseProgram(pinkyProgram);
    glBindVertexArray(vaoCentreLine);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawReferenceLines()
{
    for(j=0;j<2;j++)
        {
            for(i=0;i<36;i++)
            {
                glUseProgram(referenceLineProgram);
                glBindVertexArray(vaoReferenceLine[j][i]);
                glLineWidth(0.5);
                glDrawArrays(GL_LINES,0,4);
                
            }
        }
}

void drawPacman()
{
    glUseProgram(pacmanProgram);
    glBindVertexArray(vaoPacmanStable);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawPacmanRight()
{
    cout<<"Right"<<endl;
    glUseProgram(pacmanProgram);
    glBindVertexArray(vaoPacmanRight);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawPacmanLeft()
{
    glUseProgram(pacmanProgram);
    glBindVertexArray(vaoPacmanLeft);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawPacmanUp()
{
    glUseProgram(pacmanProgram);
    glBindVertexArray(vaoPacmanUp);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawPacmanDown()
{
    glUseProgram(pacmanProgram);
    glBindVertexArray(vaoPacmanDown);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
}
void drawGhost(int shader)
{
    glUseProgram(shader);
    glBindVertexArray(vaoGhost);
    glLineWidth(4.0);
    glDrawArrays(GL_LINES,0,2000);
    
}
void displayStablePacman()
{
    if(pacmanShape)
    {
        switch(currState)
        {
            case 0:
                attachPacmanUp();
                drawPacmanUp();
                break;
            case 1:
                attachPacmanLeft();
                drawPacmanLeft();
                break;
            case 2:
                attachPacmanDown();
                drawPacmanDown();
                break;
            case 3:
                attachPacmanRight();
                drawPacmanRight();
                break;
        }
    }
    else
    {
        attachPacman();
        drawPacman();
    }
}
void attachWall()
{
    float vertices[] = {
                  -0.421875f, 0.833333f, 0.0f,  
         0.421875, 0.833333f, 0.0f, 
         -0.429688f, 0.826389f, 0.0f,  
         -0.421875, 0.826389f, 0.0f, 
          0.421875, 0.826389f, 0.0f,
            0.429688, 0.826389f, 0.0f, 
             -0.433594, 0.819444f, 0.0f,
              -0.433594, 0.805556f, 0.0f,
               0.433594, 0.819444f, 0.0f,
                0.433594,0.805556f, 0.0f, 
                 -0.421875,0.805556, 0.0f,
                 -0.421875,0.798611, 0.0f,
                 0.421875,0.805556, 0.0f, 
                 0.421875,0.798611, 0.0f, 
                 -0.4375,0.805556,   0.0f,
                 -0.4375,0.305556, 0.0f,  
 0.4375,0.805556,   0.0f,
                 0.4375,0.305556, 0.0f, 
                 -0.425781,0.798611,   0.0f,
                 -0.425781,0.3125, 0.0f,  
  0.425781,0.798611,   0.0f,
                 0.425781,0.3125, 0.0f,
                  -0.417969,0.8125  ,   0.0f,
                 -0.0195312,0.8125, 0.0f,  
0.417969,0.8125,   0.0f,
                 0.0195312,0.8125, 0.0f,  
                  -0.0195312,0.798611  ,   0.0f,
                 -0.0195312,0.805556, 0.0f,  

0.0195312,0.798611  ,   0.0f,
                 0.0195312,0.805556, 0.0f,  
                  -0.015625,0.798611  ,   0.0f,
                 -0.015625,0.597222, 0.0f,

                  0.015625,0.798611  ,   0.0f,
                 0.015625,0.597222, 0.0f,  
                    -0.351562,0.694444  ,   0.0f,
                 -0.273438,0.694444, 0.0f,
                 0.351562,0.694444  ,   0.0f,
                 0.273438,0.694444, 0.0f,
                 -0.195312,0.694444  ,   0.0f,
                 -0.0859375,0.694444, 0.0f,
                 0.195312,0.694444  ,   0.0f,
                 0.0859375,0.694444, 0.0f,
                -0.355469,0.6875  ,   0.0f,
                 -0.355469,0.680556, 0.0f,
0.355469,0.6875  ,   0.0f,
                 0.355469,0.680556, 0.0f,
                 -0.273438,0.6875  ,   0.0f,
                 -0.273438,0.680556, 0.0f,

                 0.273438,0.6875  ,   0.0f,
                 0.273438,0.680556, 0.0f,

                 -0.199219,0.6875  ,   0.0f,
                 -0.199219,0.680556, 0.0f,

                 0.199219,0.6875  ,   0.0f,
                 0.199219,0.680556, 0.0f,

                 -0.0859375,0.6875  ,   0.0f,
                 -0.0859375,0.680556, 0.0f,
                 0.0859375,0.6875  ,   0.0f,
                 0.0859375,0.680556, 0.0f,
-0.359375,0.680556  ,   0.0f,
                 -0.359375,0.597222, 0.0f,

0.359375,0.680556  ,   0.0f,
                 0.359375,0.597222, 0.0f,

-0.269531,0.680556  ,   0.0f,
                 -0.269531,0.597222, 0.0f,

0.269531,0.680556  ,   0.0f,
                 0.269531,0.597222, 0.0f,

-0.203125,0.680556  ,   0.0f,
                 -0.203125,0.597222, 0.0f,
0.203125,0.680556  ,   0.0f,
                 0.203125,0.597222, 0.0f,
                 -0.0820312,0.680556  ,   0.0f,
                 -0.0820312,0.597222, 0.0f,
                 0.203125,0.680556  ,   0.0f,
                 0.203125,0.597222, 0.0f,
                 -0.355469,0.597222  ,   0.0f,
                 -0.355469,0.590278, 0.0f,
                 0.355469,0.597222  ,   0.0f,
                 0.355469,0.590278, 0.0f,
                 -0.273438,0.597222  ,   0.0f,
                 -0.273438,0.590278, 0.0f,

                 0.273438,0.597222  ,   0.0f,
                 0.273438,0.590278, 0.0f,

                 -0.199219,0.597222  ,   0.0f,
                 -0.199219,0.590278, 0.0f,
0.199219,0.597222  ,   0.0f,
                 0.199219,0.590278, 0.0f,
                 -0.0859375,0.597222  ,   0.0f,
                 -0.0859375,0.590278, 0.0f,

                 0.0859375,0.597222  ,   0.0f,
                 0.0859375,0.590278, 0.0f,

                 -0.0117188,0.597222  ,   0.0f,
                 -0.0117188,0.590278, 0.0f,
0.0117188,0.597222  ,   0.0f,
                 0.0117188,0.590278, 0.0f,
-0.351562,0.590278  ,   0.0f,
                 -0.273438,0.590278, 0.0f,
                 0.0117188,0.597222  ,   0.0f,
                 0.0117188,0.590278, 0.0f,
-0.195312,0.590278  ,   0.0f,
                 -0.0859375,0.590278, 0.0f,
                 0.195312,0.590278  ,   0.0f,
                 0.0859375,0.590278, 0.0f,
                 -0.0859375,0.590278  ,   0.0f,
                 -0.0859375,0.583333, 0.0f,
                   0.0859375,0.590278  ,   0.0f,
                 0.0859375,0.583333, 0.0f,
  -0.351562 ,0.472222  ,   0.0f,
                 -0.273438,0.472222, 0.0f,

  0.351562 ,0.472222  ,   0.0f,
                 0.273438,0.472222, 0.0f,

  -0.195312 ,0.472222  ,   0.0f,
                 -0.179688,0.472222, 0.0f,

  0.195312 ,0.472222  ,   0.0f,
                 0.179688,0.472222, 0.0f,

  -0.101562 ,0.472222  ,   0.0f,
                 0.101562,0.472222, 0.0f,

  -0.355469 ,0.465278  ,   0.0f,
                 -0.355469,0.458333, 0.0f,
                 0.355469 ,0.465278  ,   0.0f,
                 0.355469,0.458333, 0.0f,
                 -0.273438 ,0.465278  ,   0.0f,
                 -0.273438,0.458333, 0.0f,

                 0.273438 ,0.465278  ,   0.0f,
                 0.273438,0.458333, 0.0f,

                 -0.199219 ,0.465278  ,   0.0f,
                 -0.199219,0.458333, 0.0f,

                 0.199219 ,0.465278  ,   0.0f,
                 0.199219,0.458333, 0.0f,

                 -0.179688 ,0.465278  ,   0.0f,
                 -0.179688,0.458333, 0.0f,

                 0.199219 ,0.465278  ,   0.0f,
                 0.199219,0.458333, 0.0f,

                 -0.105469 ,0.465278  ,   0.0f,
                 -0.105469,0.458333, 0.0f,
                 0.105469 ,0.465278  ,   0.0f,
                 0.105469,0.458333, 0.0f,
                 -0.359375 ,0.458333  ,   0.0f,
                 -0.359375,0.430556, 0.0f,

                 0.359375 ,0.458333  ,   0.0f,
                 0.359375,0.430556, 0.0f,

                 -0.269531 ,0.458333  ,   0.0f,
                 -0.269531,0.430556, 0.0f,

                 0.269531 ,0.458333  ,   0.0f,
                 0.269531,0.430556, 0.0f,

                 -0.203125 ,0.458333  ,   0.0f,
                 -0.203125,0.0972222, 0.0f,
                  0.203125 ,0.458333  ,   0.0f,
                 0.203125,0.0972222, 0.0f,
                  -0.175781 ,0.458333  ,   0.0f,
                 -0.175781,0.3125, 0.0f,
0.175781 ,0.458333  ,   0.0f,
                 0.175781,0.3125, 0.0f,
                 -0.109375 ,0.458333  ,   0.0f,
                 -0.109375,0.430556, 0.0f,
                 0.109375 ,0.458333  ,   0.0f,
                 0.109375,0.430556, 0.0f,
                 -0.355469 ,0.430556  ,   0.0f,
                 -0.355469,0.423611, 0.0f,
                  0.355469 ,0.430556  ,   0.0f,
                 0.355469,0.423611, 0.0f,
 -0.273438 ,0.430556  ,   0.0f,
                 -0.273438,0.423611, 0.0f,
                 0.273438 ,0.430556  ,   0.0f,
                 0.273438,0.423611, 0.0f,
                 -0.105469 ,0.430556  ,   0.0f,
                 -0.105469,0.423611, 0.0f,
                 0.105469 ,0.430556  ,   0.0f,
                 0.105469,0.423611, 0.0f,
-0.351562 ,0.423611  ,   0.0f,
                 -0.273438,0.423611, 0.0f,
                 0.351562 ,0.423611  ,   0.0f,
                 0.273438,0.423611, 0.0f,
                 -0.0195312 ,0.416667  ,   0.0f,
                 -0.0195312,0.409722, 0.0f,
0.0195312 ,0.416667  ,   0.0f,
                 0.0195312,0.409722, 0.0f,
                 -0.015625 ,0.409722  ,   0.0f,
                 -0.015625,0.263889, 0.0f,
 0.015625 ,0.409722  ,   0.0f,
                 0.015625,0.263889, 0.0f,
                  -0.421875 ,0.3125  ,   0.0f,
                 -0.421875,0.305556, 0.0f,
                 0.421875 ,0.3125  ,   0.0f,
                 0.421875,0.305556, 0.0f,
                 -0.171875 ,0.3125  ,   0.0f,
                 -0.171875,0.305556, 0.0f,
                 0.171875 ,0.3125  ,   0.0f,
                 0.171875,0.305556, 0.0f,
                 -0.433594 ,0.305556  ,   0.0f,
                 -0.433594,0.291667, 0.0f,
                 0.433594 ,0.305556  ,   0.0f,
                 0.433594,0.291667, 0.0f,
-0.417969 ,0.305556  ,   0.0f,
                 -0.273438,0.305556, 0.0f,
                 0.417969 ,0.305556  ,   0.0f,
                 0.273438,0.305556, 0.0f,
-0.167969 ,0.305556  ,   0.0f,
                 -0.0859375,0.305556, 0.0f,
                 0.167969 ,0.305556  ,   0.0f,
                 0.0859375,0.305556, 0.0f,
                 -0.273438 ,0.298611  ,   0.0f,
                 -0.273438,0.291667, 0.0f,
                  0.273438 ,0.298611  ,   0.0f,
                 0.273438,0.291667, 0.0f,
                  -0.0859375 ,0.298611  ,   0.0f,
                 -0.0859375,0.291667, 0.0f,
                  0.0859375 ,0.298611  ,   0.0f,
                 0.0859375,0.291667, 0.0f,
                  -0.0820312 ,0.298611  ,   0.0f,
                 -0.0820312,0.291667, 0.0f,
                        0.0820312 ,0.298611  ,   0.0f,
                 0.0820312,0.291667, 0.0f,
       -0.269531 ,0.298611  ,   0.0f,
                 -0.269531,0.291667, 0.0f,
                  0.269531 ,0.298611  ,   0.0f,
                 0.269531,0.291667, 0.0f,
 -0.429688 ,0.291667  ,   0.0f,
                 -0.421875,0.291667, 0.0f,
                 0.429688 ,0.291667  ,   0.0f,
                 0.421875,0.291667, 0.0f,
                 -0.269531 ,0.291667  ,   0.0f,
                 -0.269531,0.0972222, 0.0f,
0.269531 ,0.291667  ,   0.0f,
                 0.269531,0.0972222, 0.0f,
                 -0.0820312 ,0.291667  ,   0.0f,
                 -0.0820312,0.263889, 0.0f,
                    0.0820312 ,0.291667  ,   0.0f,
                 0.0820312,0.263889, 0.0f,
    -0.0820312 ,0.291667  ,   0.0f,
                 -0.0820312,0.263889, 0.0f,
                 0.0820312 ,0.291667  ,   0.0f,
                 0.0820312,0.263889, 0.0f,
                 -0.421875 ,0.284722  ,   0.0f,
                 -0.28125,0.284722, 0.0f,

                 0.421875 ,0.284722  ,   0.0f,
                 0.28125,0.284722, 0.0f,

                 -0.0859375 ,0.590278  ,   0.0f,
                 -0.0859375,0.583333, 0.0f,
                 0.0859375 ,0.590278  ,   0.0f,
                 0.0859375,0.583333, 0.0f,
                 
-0.0078125 ,0.590278  ,   0.0f,
                 0.0078125,0.590278, 0.0f,
                -0.101562 ,0.472222  ,   0.0f,
                 0.101562,0.472222, 0.0f,
                 0.0820312 ,0.680556  ,   0.0f,
                 0.0820312,0.597222, 0.0f,
 -0.351562 ,0.590278  ,   0.0f,
                 -0.273438,0.590278, 0.0f,
                 0.351562 ,0.590278  ,   0.0f,
                 0.273438,0.590278, 0.0f,
                 -0.101562 ,0.423611  ,   0.0f,
                 -0.0195312,0.423611, 0.0f,
                   0.101562 ,0.423611  ,   0.0f,
                 0.0195312,0.423611, 0.0f,
                 -0.28125 ,0.277778  ,   0.0f,
                 -0.28125,0.111111, 0.0f,
 
                 0.28125 ,0.277778  ,   0.0f,
                 0.28125,0.111111, 0.0f,
  
                 -0.0859375 ,0.263889  ,   0.0f,
                 -0.0820312,0.263889, 0.0f,
  
                 0.0859375 ,0.263889  ,   0.0f,
                 0.0820312,0.263889, 0.0f,

                 -0.0117188 ,0.263889  ,   0.0f,
                 -0.0078125,0.263889, 0.0f,
 
0.0117188 ,0.263889  ,   0.0f,
                 0.0078125,0.263889, 0.0f,
                 -0.167969 ,0.256944  ,   0.0f,
                 -0.0859375,0.256944, 0.0f,
                 0.167969 ,0.256944  ,   0.0f,
                 0.0859375,0.256944, 0.0f,
                 -0.0078125 ,0.256944  ,   0.0f,
                 0.0078125,0.256944, 0.0f,
                 -0.171875 ,0.25  ,   0.0f,
                 -0.167969,0.25, 0.0f,
                 0.171875 ,0.25  ,   0.0f,
                 0.167969,0.25, 0.0f, 
                                  -0.175781 ,0.243056  ,   0.0f,
                 -0.175781,0.0972222, 0.0f,
                  0.171875 ,0.25  ,   0.0f,
                 0.167969,0.25, 0.0f,
                   -0.109375 ,0.138889  ,   0.0f,
                 -0.109375,-0.0833333, 0.0f,
0.109375 ,0.138889  ,   0.0f,
                 0.109375,-0.0833333, 0.0f, 
-0.0976562 ,0.118056  ,   0.0f,
                 -0.03125,0.118056, 0.0f,

0.0976562 ,0.118056  ,   0.0f,
                 0.03125,0.118056, 0.0f,


-0.0351562 ,0.138889  ,   0.0f,
                 -0.0351562,0.111111, 0.0f,
                 0.0351562 ,0.138889  ,   0.0f,
                 0.0351562,0.111111, 0.0f,
-0.0976562 ,-0.0625  ,   0.0f,
                 0.0976562,-0.0625, 0.0f,
-0.109375 ,-0.0833333  ,   0.0f,
                 0.109375,-0.0833333, 0.0f,
                 -0.0976562 ,   0.118056  ,   0.0f,
                 -0.0976562,-0.0625, 0.0f,
 0.0976562 ,   0.118056  ,   0.0f,
                 0.0976562,-0.0625, 0.0f,
                 -0.109375 ,   0.138889  ,   0.0f,
                 -0.03125,0.138889, 0.0f,
0.109375 ,   0.138889  ,   0.0f,
                 0.03125,0.138889, 0.0f,
                 -0.4375 ,   0.111111  ,   0.0f,
                 -0.28125,0.111111, 0.0f,
                 0.4375 ,   0.111111  ,   0.0f,
                 0.28125,0.111111, 0.0f,
-0.273438 ,   0.0972222  ,   0.0f,
                 -0.269531,0.0972222, 0.0f,

0.273438 ,   0.0972222  ,   0.0f,
                 0.269531,0.0972222, 0.0f,
-0.199219 ,   0.0972222  ,   0.0f,
                 -0.195312,0.0972222, 0.0f,

0.199219 ,   0.0972222  ,   0.0f,
                 0.195312,0.0972222, 0.0f,

-0.179688 ,   0.0972222  ,   0.0f,
                 -0.175781,0.0972222, 0.0f,
                 0.179688 ,   0.0972222  ,   0.0f,
                 0.175781,0.0972222, 0.0f,
                 -0.4375 ,   0.0902778  ,   0.0f,
                 -0.273438,0.0902778, 0.0f,
                 0.4375 ,   0.0902778  ,   0.0f,
                 0.273438,0.0902778, 0.0f,
                 -0.195312 ,   0.0902778  ,   0.0f,
                 -0.179688,0.0902778, 0.0f, 
               0.195312 ,   0.0902778  ,   0.0f,
                 0.179688,0.0902778, 0.0f, 
                 -0.4375 ,   -0.0277778  ,   0.0f,
                 -0.273438,-0.0277778, 0.0f, 
0.4375 ,   -0.0277778  ,   0.0f,
                 0.273438,-0.0277778, 0.0f, 
               -0.195312 ,   -0.0277778  ,   0.0f,
                 -0.179688,-0.0277778, 0.0f, 

               0.195312 ,   -0.0277778  ,   0.0f,
                 0.179688,-0.0277778, 0.0f,

               -0.273438 ,   -0.0347222  ,   0.0f,
                 -0.269531,-0.0347222, 0.0f,

               0.273438 ,   -0.0347222  ,   0.0f,
                 0.269531,-0.0347222, 0.0f, 

               -0.199219 ,   -0.0347222  ,   0.0f,
                 -0.195312,-0.0347222, 0.0f,

               0.199219 ,   -0.0347222  ,   0.0f,
                 0.195312,-0.0347222, 0.0f,

               -0.179688 ,   -0.0347222  ,   0.0f,
                 -0.175781,-0.0347222, 0.0f,

               0.179688 ,   -0.0347222  ,   0.0f,
                 0.175781,-0.0347222, 0.0f,

               -0.269531 ,   -0.0416667  ,   0.0f,
                 -0.269531,-0.236111, 0.0f,
                   0.269531 ,   -0.0416667  ,   0.0f,
                 0.269531,-0.236111, 0.0f,              
  -0.203125 ,   -0.0416667  ,   0.0f,
                 -0.203125,-0.236111, 0.0f,
                 0.203125 ,   -0.0416667  ,   0.0f,
                 0.203125,-0.236111, 0.0f,
-0.175781 ,   -0.0416667  ,   0.0f,
                 -0.175781,-0.236111, 0.0f,
                 0.175781 ,   -0.0416667  ,   0.0f,
                 0.175781,-0.236111, 0.0f,
                 -0.4375 ,   -0.0416667  ,   0.0f,
                 -0.28125,-0.0416667, 0.0f,

                 0.4375 ,   -0.0416667  ,   0.0f,
                 0.28125,-0.0416667, 0.0f,

                 -0.28125 ,   -0.0555556  ,   0.0f,
                 -0.28125,-0.222222, 0.0f,

                 0.28125 ,   -0.0555556  ,   0.0f,
                 0.28125,-0.222222, 0.0f,

                 -0.421875 ,   -0.222222  ,   0.0f,
                 -0.28125,-0.222222, 0.0f,
                 0.421875 ,   -0.222222  ,   0.0f,
                 0.28125,-0.222222, 0.0f,
                 -0.429688 ,   -0.229167  ,   0.0f,
                 -0.421875,-0.229167, 0.0f,
                   0.429688 ,   -0.229167  ,   0.0f,
                 0.421875,-0.229167, 0.0f,
                   -0.433594 ,   -0.236111  ,   0.0f,
                 -0.433594,-0.25, 0.0f,

                   0.433594 ,   -0.236111  ,   0.0f,
                 0.433594,-0.25, 0.0f,

                   -0.273438 ,   -0.236111  ,   0.0f,
                 -0.273438,-0.243056, 0.0f,

                   0.273438 ,   -0.236111  ,   0.0f,
                 0.273438,-0.243056, 0.0f,

                   -0.199219 ,   -0.236111  ,   0.0f,
                 -0.199219,-0.243056, 0.0f,

                   0.199219 ,   -0.236111  ,   0.0f,
                 0.199219,-0.243056, 0.0f,

                   -0.179688 ,   -0.236111  ,   0.0f,
                 -0.179688,-0.243056, 0.0f,

                   0.179688 ,   -0.236111  ,   0.0f,
                 0.179688,-0.243056, 0.0f,

                   -0.417969 ,   -0.243056  ,   0.0f,
                 -0.273438,-0.243056, 0.0f,
                 0.417969 ,   -0.243056  ,   0.0f,
                 0.273438,-0.243056, 0.0f,
                 -0.195312 ,   -0.243056  ,   0.0f,
                 -0.179688,-0.243056, 0.0f,
 0.195312 ,   -0.243056  ,   0.0f,
                 0.179688,-0.243056, 0.0f,
                  -0.101562 ,   -0.194444  ,   0.0f,
                 -0.0,-0.194444, 0.0f,
                 0.101562 ,   -0.194444  ,   0.0f,
                 0.0,-0.194444, 0.0f,
-0.105469 ,   -0.201389  ,   0.0f,
                 -0.105469,-0.208333, 0.0f,
                 0.105469 ,   -0.201389  ,   0.0f,
                 0.105469,-0.208333, 0.0f,
                 -0.109375 ,   -0.208333  ,   0.0f,
                 -0.109375,-0.236111, 0.0f,
0.109375 ,   -0.208333  ,   0.0f,
                 0.109375,-0.236111, 0.0f,
-0.105469 ,   -0.236111  ,   0.0f,
                 -0.101562,-0.236111, 0.0f,
                 0.105469 ,   -0.236111  ,   0.0f,
                 0.101562,-0.236111, 0.0f,
                 -0.101562 ,   -0.243056  ,   0.0f,
                 -0.0195312,-0.243056, 0.0f,
       0.101562 ,   -0.243056  ,   0.0f,
                 0.0195312,-0.243056, 0.0f,
                 -0.0195312 ,   -0.25  ,   0.0f,
                 -0.0195312,-0.25, 0.0f,
                  0.0195312 ,   -0.25  ,   0.0f,
                 0.0195312,-0.25, 0.0f,
                            -0.015625 ,   -0.256944  ,   0.0f,
                 -0.015625,-0.402778, 0.0f,
 0.015625 ,   -0.256944  ,   0.0f,
                 0.015625,-0.402778, 0.0f,
                  -0.0117188 ,   -0.402778  ,   0.0f,
                 -0.0078125,-0.402778, 0.0f,
                  0.015625 ,   -0.256944  ,   0.0f,
                 0.015625,-0.402778, 0.0f,
                  -0.0078125 ,   -0.409722  ,   0.0f,
                 -0.0,-0.409722, 0.0f,
                0.0078125 ,   -0.409722  ,   0.0f,
                 0.0,-0.409722, 0.0f,
                 -0.4375 ,   -0.25  ,   0.0f,
                 -0.4375,-0.861111, 0.0f,
                 0.4375 ,   -0.25  ,   0.0f,
                 0.4375,-0.861111, 0.0f,
                 -0.425781 ,   -0.256944  ,   0.0f,
                 -0.425781,-0.520833, 0.0f,
                 0.425781 ,   -0.256944  ,   0.0f,
                 0.425781,-0.520833, 0.0f,
-0.351562  , -0.361111,0.0f,
                 -0.273438,-0.361111, 0.0f,
                 0.351562  , -0.361111,0.0f,
                 0.273438,-0.361111, 0.0f,
-0.195312 ,  -0.361111,0.0f,
                 -0.0859375,-0.361111, 0.0f,
                 0.195312  , -0.361111,0.0f,
                 0.0859375,-0.361111, 0.0f,
                 -0.355469 ,  -0.368056,0.0f,
                 -0.351562,-0.368056, 0.0f,
                 0.355469 ,  -0.368056,0.0f,
                 0.351562,-0.368056, 0.0f,
                 -0.273438 ,  -0.368056,0.0f,
                 -0.269531,-0.368056, 0.0f,

                 0.273438 ,  -0.368056,0.0f,
                 0.269531,-0.368056, 0.0f,

                 -0.199219  , -0.368056,0.0f,
                 -0.195312,-0.368056, 0.0f,
                 0.199219 ,  -0.368056,0.0f,
                 0.195312,-0.368056, 0.0f,
                 -0.0859375  , -0.368056,0.0f,
                 -0.0820312,-0.368056, 0.0f, 
                 0.0859375  , -0.368056,0.0f,
                 0.0820312,-0.368056, 0.0f,
                                  -0.359375  , -0.375,0.0f,
                 -0.359375,-0.402778, 0.0f, 
 0.359375 ,  -0.375,0.0f,
                 0.359375,-0.402778, 0.0f,  
 -0.269531  , -0.375,0.0f,
                 -0.269531,-0.569444, 0.0f,

 0.269531  , -0.375,0.0f,
                 0.269531,-0.569444, 0.0f,

 -0.203125  , -0.375,0.0f,
                 -0.203125,-0.402778, 0.0f, 

 0.203125  , -0.375,0.0f,
                 0.203125,-0.402778, 0.0f,

 -0.0820312  , -0.375,0.0f,
                 -0.0820312,-0.402778, 0.0f,
                  0.0820312 ,  -0.375,0.0f,
                 0.0820312,-0.402778, 0.0f,
                  -0.355469  , -0.402778,0.0f,
                 -0.351562,-0.402778, 0.0f,
0.355469  , -0.402778,0.0f,
                 0.351562,-0.402778, 0.0f,
-0.199219  , -0.402778,0.0f,
                 -0.195312,-0.402778, 0.0f,
                 0.199219  , -0.402778,0.0f,
                 0.195312,-0.402778, 0.0f,
                 -0.0859375  , -0.402778,0.0f,
                 -0.0820312,-0.402778, 0.0f,
                 0.0859375  , -0.402778,0.0f,
                 0.0820312,-0.402778, 0.0f,
-0.351562  , -0.409722,0.0f,
                 -0.300781,-0.409722, 0.0f,
                 0.351562  , -0.409722,0.0f,
                 0.300781,-0.409722, 0.0f,
                 -0.195312  , -0.409722,0.0f,
                 -0.0859375,-0.409722, 0.0f,
 0.195312  , -0.409722,0.0f,
                 0.0859375,-0.409722, 0.0f,
 -0.300781  , -0.416667,0.0f,
                 -0.296875,-0.409722, 0.0f,
                 0.300781  , -0.416667,0.0f,
                 0.296875,-0.409722, 0.0f,
                 -0.296875  , -0.423611,0.0f,
                 -0.296875,-0.569444, 0.0f,
                 0.296875  , -0.423611,0.0f,
                 0.296875,-0.569444, 0.0f,
-0.421875  , -0.520833,0.0f,
                 -0.417969,-0.520833, 0.0f,
                 0.296875  , -0.423611,0.0f,
                 0.296875,-0.569444, 0.0f,
                 -0.417969  , -0.527778,0.0f,
                 -0.367188,-0.527778, 0.0f,
                 0.417969  , -0.527778,0.0f,
                 0.367188,-0.527778, 0.0f,  
                 -0.195312  , -0.527778,0.0f,
                 -0.179688,-0.527778, 0.0f,

                 0.195312  , -0.527778,0.0f,
                 0.179688,-0.527778, 0.0f,

                 -0.101562  , -0.527778,0.0f,
                 -0.0,-0.527778, 0.0f, 
                 0.101562  , -0.527778,0.0f,
                 0.0,-0.527778, 0.0f, 
                 -0.367188  , -0.534722,0.0f,
                 -0.363281,-0.534722, 0.0f,              

                 0.367188  , -0.534722,0.0f,
                 0.363281,-0.534722, 0.0f,

                 -0.199219  , -0.534722,0.0f,
                 -0.195312,-0.534722, 0.0f,
                 0.199219  , -0.534722,0.0f,
                 0.195312,-0.534722, 0.0f,
                 -0.179688  , -0.534722,0.0f,
                 -0.175781,-0.534722, 0.0f,
                 0.179688  , -0.534722,0.0f,
                 0.175781,-0.534722, 0.0f,
                 -0.105469  , -0.534722,0.0f,
                 -0.101562,-0.534722, 0.0f,
                 0.105469  , -0.534722,0.0f,
                 0.101562,-0.534722, 0.0f,
                 -0.363281  , -0.541667,0.0f,
                 -0.363281,-0.569444, 0.0f,
                 0.363281  , -0.541667,0.0f,
                 0.363281,-0.569444, 0.0f,
                 -0.203125  , -0.541667,0.0f,
                 -0.203125,-0.6875, 0.0f,
                 0.203125  , -0.541667,0.0f,
                 0.203125,-0.6875, 0.0f,
-0.175781  , -0.541667,0.0f,
                 -0.175781,-0.6875, 0.0f,

0.175781  , -0.541667,0.0f,
                 0.175781,-0.6875, 0.0f,
  
-0.175781  , -0.541667,0.0f,
                 -0.175781,-0.6875, 0.0f,



                 -0.109375 , -0.541667 , 0.0 , 
-0.109375 , -0.569444 , 0.0 , 
-0.367188 , -0.569444 , 0.0 , 
-0.363281 , -0.569444 , 0.0 , 
-0.292969 , -0.569444 , 0.0 , 
-0.289062 , -0.569444 , 0.0 , 
-0.273438 , -0.569444 , 0.0 , 
-0.269531 , -0.569444 , 0.0 , 
-0.105469 , -0.569444 , 0.0 , 
-0.101562 , -0.569444 , 0.0 ,                
                 
                
                 0.109375 , -0.541667 , 0.0 , 
0.109375 , -0.569444 , 0.0 , 
0.367188 , -0.569444 , 0.0 , 
0.363281 , -0.569444 , 0.0 , 
0.292969 , -0.569444 , 0.0 , 
0.289062 , -0.569444 , 0.0 , 
0.273438 , -0.569444 , 0.0 , 
0.269531 , -0.569444 , 0.0 , 
0.105469 , -0.569444 , 0.0 , 
0.101562 , -0.569444 , 0.0 , 
                 
                 

                 -0.417969 , -0.576389 , 0.0 , 
-0.367188 , -0.576389 , 0.0 , 
-0.289062 , -0.576389 , 0.0 , 
-0.273438 , -0.576389 , 0.0 , 
-0.101562 , -0.576389 , 0.0 , 
-0.0195312 , -0.576389 , 0.0 , 
-0.421875 , -0.583333 , 0.0 , 
-0.417969 , -0.583333 , 0.0 , 
-0.0195312 , -0.583333 , 0.0 , 
-0.015625 , -0.583333 , 0.0 , 
-0.425781 , -0.590278 , 0.0 , 
-0.425781 , -0.854167 , 0.0 , 
-0.015625 , -0.590278 , 0.0 , 
-0.015625 , -0.736111 , 0.0 , 
-0.207031 , -0.6875 , 0.0 , 
-0.203125 , -0.6875 , 0.0 , 
-0.1875 , -0.6875 , 0.0 , 
-0.183594 , -0.6875 , 0.0 , 
-0.351562 , -0.694444 , 0.0 , 
-0.207031 , -0.694444 , 0.0 , 
-0.167969 , -0.694444 , 0.0 , 
-0.0859375 , -0.694444 , 0.0 , 
-0.355469 , -0.701389 , 0.0 , 
-0.351562 , -0.701389 , 0.0 , 
-0.0859375 , -0.701389 , 0.0 , 
-0.0820312 , -0.701389 , 0.0 , 
-0.359375 , -0.708333 , 0.0 , 
-0.359375 , -0.736111 , 0.0 , 
-0.0820312 , -0.708333 , 0.0 , 
-0.0820312 , -0.736111 , 0.0 , 
-0.355469 , -0.736111 , 0.0 , 
-0.351562 , -0.736111 , 0.0 , 
-0.0859375 , -0.736111 , 0.0 , 
-0.0820312 , -0.736111 , 0.0 , 
-0.0117188 , -0.736111 , 0.0 , 
-0.0078125 , -0.736111 , 0.0 , 
-0.351562 , -0.743056 , 0.0 , 
-0.0859375 , -0.743056 , 0.0 , 
-0.0078125 , -0.743056 , 0.0 , 
0 , -0.743056 , 0.0 , 


 0.417969 , -0.576389 , 0.0 , 
0.367188 , -0.576389 , 0.0 , 
0.289062 , -0.576389 , 0.0 , 
0.273438 , -0.576389 , 0.0 , 
0.101562 , -0.576389 , 0.0 , 
0.0195312 , -0.576389 , 0.0 , 
0.421875 , -0.583333 , 0.0 , 
0.417969 , -0.583333 , 0.0 , 
0.0195312 , -0.583333 , 0.0 , 
0.015625 , -0.583333 , 0.0 , 
0.425781 , -0.590278 , 0.0 , 
0.425781 , -0.854167 , 0.0 , 
0.015625 , -0.590278 , 0.0 , 
0.015625 , -0.736111 , 0.0 , 
0.207031 , -0.6875 , 0.0 , 
0.203125 , -0.6875 , 0.0 , 
0.1875 , -0.6875 , 0.0 , 
0.183594 , -0.6875 , 0.0 , 
0.351562 , -0.694444 , 0.0 , 
0.207031 , -0.694444 , 0.0 , 
0.167969 , -0.694444 , 0.0 , 
0.0859375 , -0.694444 , 0.0 , 
0.355469 , -0.701389 , 0.0 , 
0.351562 , -0.701389 , 0.0 , 
0.0859375 , -0.701389 , 0.0 , 
0.0820312 , -0.701389 , 0.0 , 
0.359375 , -0.708333 , 0.0 , 
0.359375 , -0.736111 , 0.0 , 
0.0820312 , -0.708333 , 0.0 , 
0.0820312 , -0.736111 , 0.0 , 
0.355469 , -0.736111 , 0.0 , 
0.351562 , -0.736111 , 0.0 , 
0.0859375 , -0.736111 , 0.0 , 
0.0820312 , -0.736111 , 0.0 , 
0.0117188 , -0.736111 , 0.0 , 
0.0078125 , -0.736111 , 0.0 , 
0.351562 , -0.743056 , 0.0 , 
0.0859375 , -0.743056 , 0.0 , 
0.0078125 , -0.743056 , 0.0 , 
0 , -0.743056 , 0.0 , 

-0.421875 , -0.854167 , 0.0 , 
-0.417969 , -0.854167 , 0.0 , 
-0.417969 , -0.861111 , 0.0 , 
0 , -0.861111 , 0.0 , 
-0.433594 , -0.861111 , 0.0 , 
-0.433594 , -0.875 , 0.0 , 
-0.429688 , -0.875 , 0.0 , 
-0.421875 , -0.875 , 0.0 , 
-0.421875 , -0.881944 , 0.0 , 
0 , -0.881944 , 0.0 , 


0.421875 , -0.854167 , 0.0 , 
0.417969 , -0.854167 , 0.0 , 
0.417969 , -0.861111 , 0.0 , 
0 , -0.861111 , 0.0 , 
0.433594 , -0.861111 , 0.0 , 
0.433594 , -0.875 , 0.0 , 
0.429688 , -0.875 , 0.0 , 
0.421875 , -0.875 , 0.0 , 
0.421875 , -0.881944 , 0.0 , 
0 , -0.881944 , 0.0 , 
0.171875 , 0.243056 , 0.0 , 
0.171875 , 0.0972222 , 0.0


   
 

        
    }; 
    glBindVertexArray(vaoWall);
    glBindBuffer(GL_ARRAY_BUFFER,vboWall);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 

        float vertices1[]={
        -0.03125,0.131944,0.0,
        0.03125,0.131944,0.0
    };
    glBindVertexArray(vaoCentreLine);
    glBindBuffer(GL_ARRAY_BUFFER,vboCentreLine);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}
void movePacmanLogic()
{
    if((currTime-lastPacmanMoveTime)>(1.0/pacmanSpeed))
        {
            if(stopForSomeFrame<=0)
            {
                lastPacmanMoveTime=currTime;
                cout<<"movePacman"<<endl;
                movePacman();
                if(board[currPacLoc[1]][currPacLoc[0]]==1)
                {
                    stopForSomeFrame=1;
                    board[currPacLoc[1]][currPacLoc[0]]=2; 
                    score+=10;
                }
                else if(board[currPacLoc[1]][currPacLoc[0]]==3)
                {
                    stopForSomeFrame=3;
                    board[currPacLoc[1]][currPacLoc[0]]=2;
                    score+=50;
                }
            }
            else
            {
                stopForSomeFrame--;
            }
        }
        else
        {
            displayStablePacman();
        }
}

void movePacman()
{
    last[0]=pacmanCentre[0];
    last[1]=pacmanCentre[1];
    pacmanShape=!pacmanShape;
    currPacLoc[0]=(((pacmanCentre[0]))/8)-18;
    currPacLoc[1]=(pacmanCentre[1])/8;
    cout<<currPacLoc[0]<<" "<<currPacLoc[1]<<endl;;
    if(!state.empty())
    {
        nextState=state.front();
        switch(nextState)
        {
            case 0:
                if(currPacLoc[1]>4)
                {
                    if(board[currPacLoc[1]-1][currPacLoc[0]]!=0)
                    {
                        currState=nextState;
                        state.pop();
                        pacmanCentre[0]=(((currPacLoc[0]+18)*8)+4);
                        pacmanCentre[1]=(((currPacLoc[1])*8)+4);
                    }   
                    break;
                }
                state.pop();
                break;
            case 1:
                if(currPacLoc[0]>1)
                {
                    if(board[currPacLoc[1]][currPacLoc[0]-1]!=0)
                    {
                        currState=nextState;
                        state.pop();
                        pacmanCentre[0]=(((currPacLoc[0]+18)*8)+4);
                        pacmanCentre[1]=(((currPacLoc[1])*8)+4);
                    }   
                    break;
                }
                state.pop();    
                break;
            case 2:
                if(currPacLoc[0]<32)
                {
                    if(board[currPacLoc[1]+1][currPacLoc[0]]!=0)
                    {
                        currState=nextState;
                        state.pop();
                        pacmanCentre[0]=(((currPacLoc[0]+18)*8)+4);
                        pacmanCentre[1]=(((currPacLoc[1])*8)+4);
                    }   
                    break;
                }
                state.pop();
                break;
            case 3:
                if(currPacLoc[0]<26)
                {
                    if(board[currPacLoc[1]][currPacLoc[0]+1]!=0)
                    {
                        currState=nextState;
                        state.pop();
                        pacmanCentre[0]=(((currPacLoc[0]+18)*8)+4);
                        pacmanCentre[1]=(((currPacLoc[1])*8)+4);
                    }   
                    break;
                }
                state.pop();
                break;
        }
        cout<<"a"<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
    }


        switch(currState)
        {
            case 0: 
                newPacCentre[0]=pacmanCentre[0];
                newPacCentre[1]=pacmanCentre[1]-1;
                nextPacLoc[0]=currPacLoc[0];
                nextPacLoc[1]=((pacmanCentre[1]-1)/8);
                break;
            case 1:
                
                newPacCentre[0]=(pacmanCentre[0]-1);
                newPacCentre[1]=pacmanCentre[1];
                nextPacLoc[0]=((pacmanCentre[0]-1)/8)-18;
                nextPacLoc[1]=currPacLoc[1];
                if(newPacCentre[0]==156)
                {
                    newPacCentre[0]=363;
                    nextPacLoc[0]=27;
                }
                break;
            case 2:
                newPacCentre[0]=pacmanCentre[0];
                newPacCentre[1]=pacmanCentre[1]+1;
                nextPacLoc[0]=currPacLoc[0];
                nextPacLoc[1]=(pacmanCentre[1]+1)/8;
                break;
            case 3:
                newPacCentre[0]=pacmanCentre[0]+1;
                newPacCentre[1]=pacmanCentre[1];
                nextPacLoc[0]=((pacmanCentre[0]+1)/8)-18;
                nextPacLoc[1]=currPacLoc[1];
                if(newPacCentre[0]==363)
                {
                    newPacCentre[0]=156;
                    nextPacLoc[0]=0;
                }
        }
        /*cout<<"currState "<<currState<<endl;
        cout<<"npc "<<newPacCentre[0]<<" "<<newPacCentre[1]<<endl;
        cout<<"pc "<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;*/
        if(newPacCentre[0]>=156 && newPacCentre[0]<364 && board[nextPacLoc[1]][nextPacLoc[0]]!=0)
        {
            //cout<<"c1"<<endl;
            pacmanCentre[0]=newPacCentre[0];
            currPacLoc[0]=nextPacLoc[0];
        }
        if(newPacCentre[1]>=36 && newPacCentre[1]<264 && board[nextPacLoc[1]][nextPacLoc[0]]!=0)
        {
            //cout<<"c2"<<endl;
            pacmanCentre[1]=newPacCentre[1];
            currPacLoc[1]=nextPacLoc[1];
        }
        //cout<<"pc "<<pacmanCentre[0]<<" "<<pacmanCentre[1]<<endl;
        if(pacmanShape)
        {
            switch(currState)
            {
                case 0:
                    attachPacmanUp();
                    drawPacmanUp();
                    break;
                case 1:
                    attachPacmanLeft();
                    drawPacmanLeft();
                    break;
                case 2:
                    attachPacmanDown();
                    drawPacmanDown();
                    break;
                case 3:
                    attachPacmanRight();
                    drawPacmanRight();
                    break;
            }
        }
        else
        {
            attachPacman();
            drawPacman();
        }
        if(last[0]==pacmanCentre[0] && last[1]==pacmanCentre[1])
        {
            clearCounter++;
        }
        else
        {
            clearCounter=0;
        }
        if(clearCounter>=2)
        {
            while(!state.empty())
            {
                state.pop();
            }
            clearCounter=0;
        }
}
void changeMode()
{
    if(currMode==1 && currTime - lastModeChangeTime >=15)
    {
        lastModeChangeTime=currTime;
        currMode=0;
    }
    else if(currMode==0 && currTime - lastModeChangeTime>=7)
    {
        lastModeChangeTime=currTime;
        currMode=1;
    }
}

void moveBlinkyLogic0()
{
    cout<<"moveBlinkyLogic0 state = "<<currBlinkyState<<"blinkySpeed"<<1.0/blinkySpeed<< endl;
    if((currTime - lastBlinkyMoveTime)>=(1.0/blinkySpeed))
    {
        cout<<"Timer true"<<endl;
        for(i=0;i<4;i++)
        {
            length[i]=9999;
            boxCountArray[i]=0;
        }
        lastBlinkyMoveTime=currTime;
        boxCount=0;
        switch(currBlinkyState)
        {
            case 0:

                if(board[currBlinkyLoc[1]-1][currBlinkyLoc[0]]!=0)
                {
                    boxCountArray[0]=1;
                    boxCount++;
                }
                if(board[currBlinkyLoc[1]][currBlinkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currBlinkyLoc[1]][currBlinkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currBlinkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[0]==1)
                    {
                        length[0]=((currBlinkyLoc[0])-(blinkyTargetScatter[0]))*((currBlinkyLoc[0])-(blinkyTargetScatter[0]));
                        length[0]+=((currBlinkyLoc[1]-1)-(blinkyTargetScatter[1]))*((currBlinkyLoc[1]-1)-(blinkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currBlinkyLoc[0]-1)-(blinkyTargetScatter[0]))*((currBlinkyLoc[0]-1)-(blinkyTargetScatter[0]));
                        length[1]+=((currBlinkyLoc[1])-(blinkyTargetScatter[1]))*((currBlinkyLoc[1])-(blinkyTargetScatter[1]));
                    }
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currBlinkyLoc[0]+1)-(blinkyTargetScatter[0]))*((currBlinkyLoc[0]+1)-(blinkyTargetScatter[0]));
                        length[3]+=((currBlinkyLoc[1])-(blinkyTargetScatter[1]))*((currBlinkyLoc[1])-(blinkyTargetScatter[1]));
                    }
                    minn=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currBlinkyState=minn;
                }
                break;
            case 1:
                if(board[currBlinkyLoc[1]-1][currBlinkyLoc[0]]!=0)
                {
                    boxCountArray[0]=1;
                    boxCount++;
                }
                if(board[currBlinkyLoc[1]][currBlinkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currBlinkyLoc[1]+1][currBlinkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currBlinkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[0]==1)
                    {
                        length[0]=((currBlinkyLoc[0])-(blinkyTargetScatter[0]))*((currBlinkyLoc[0])-(blinkyTargetScatter[0]));
                        length[0]+=((currBlinkyLoc[1]-1)-(blinkyTargetScatter[1]))*((currBlinkyLoc[1]-1)-(blinkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currBlinkyLoc[0]-1)-(blinkyTargetScatter[0]))*((currBlinkyLoc[0]-1)-(blinkyTargetScatter[0]));
                        length[1]+=((currBlinkyLoc[1])-(blinkyTargetScatter[1]))*((currBlinkyLoc[1])-(blinkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currBlinkyLoc[0])-(blinkyTargetScatter[0]))*((currBlinkyLoc[0])-(blinkyTargetScatter[0]));
                        length[2]+=((currBlinkyLoc[1]+1)-(blinkyTargetScatter[1]))*((currBlinkyLoc[1]+1)-(blinkyTargetScatter[1]));
                    }
                    minn=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currBlinkyState=minn;
                }  
                break;  
            case 2:
                if(board[currBlinkyLoc[1]][currBlinkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(board[currBlinkyLoc[1]][currBlinkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currBlinkyLoc[1]+1][currBlinkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currBlinkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currBlinkyLoc[0]+1)-(blinkyTargetScatter[0]))*((currBlinkyLoc[0]+1)-(blinkyTargetScatter[0]));
                        length[3]+=((currBlinkyLoc[1])-(blinkyTargetScatter[1]))*((currBlinkyLoc[1])-(blinkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currBlinkyLoc[0]-1)-(blinkyTargetScatter[0]))*((currBlinkyLoc[0]-1)-(blinkyTargetScatter[0]));
                        length[1]+=((currBlinkyLoc[1])-(blinkyTargetScatter[1]))*((currBlinkyLoc[1])-(blinkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currBlinkyLoc[0])-(blinkyTargetScatter[0]))*((currBlinkyLoc[0])-(blinkyTargetScatter[0]));
                        length[2]+=((currBlinkyLoc[1]+1)-(blinkyTargetScatter[1]))*((currBlinkyLoc[1]+1)-(blinkyTargetScatter[1]));
                    }
                    minn=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currBlinkyState=minn;
                }    
                break;
            case 3:
                if(board[currBlinkyLoc[1]][currBlinkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(board[currBlinkyLoc[1]-1][currBlinkyLoc[0]]!=0)
                {
                    boxCountArray[0]=1;
                    boxCount++;
                }   
                if(board[currBlinkyLoc[1]+1][currBlinkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currBlinkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currBlinkyLoc[0]+1)-(blinkyTargetScatter[0]))*((currBlinkyLoc[0]+1)-(blinkyTargetScatter[0]));
                        length[3]+=((currBlinkyLoc[1])-(blinkyTargetScatter[1]))*((currBlinkyLoc[1])-(blinkyTargetScatter[1]));
                    }
                    if(boxCountArray[0]==1)
                    {
                        length[0]=((currBlinkyLoc[0])-(blinkyTargetScatter[0]))*((currBlinkyLoc[0])-(blinkyTargetScatter[0]));
                        length[0]+=((currBlinkyLoc[1]-1)-(blinkyTargetScatter[1]))*((currBlinkyLoc[1]-1)-(blinkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currBlinkyLoc[0])-(blinkyTargetScatter[0]))*((currBlinkyLoc[0])-(blinkyTargetScatter[0]));
                        length[2]+=((currBlinkyLoc[1]+1)-(blinkyTargetScatter[1]))*((currBlinkyLoc[1]+1)-(blinkyTargetScatter[1]));
                    }
                    minn=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currBlinkyState=minn;
                }    
                break;
        }
        cout<<"boxCount"<<boxCount<<endl;
        cout<<"currBlinkyState"<<currBlinkyState<<endl;
        for(i=0;i<4;i++)
        {
            cout<<length[i]<<endl;
        }
        moveBlinky();
    }
    else
    {
        cout<<"timer False"<<endl;
        attachGhost(blinkyCentre);
        drawGhost(blinkyProgram);
    }
}
void moveBlinky()
{
    currBlinkyLoc[0]=(blinkyCentre[0]/8) -18;
    currBlinkyLoc[1]=blinkyCentre[1]/8;
    switch(currBlinkyState)
    {
        case 0:
            blinkyCentre[1]--;
            currBlinkyLoc[1]=blinkyCentre[1]/8;
            break;
        case 1:
            blinkyCentre[0]--;
            currBlinkyLoc[0]=blinkyCentre[0]/8 - 18;
            break;
        case 2:
            blinkyCentre[1]++;
            currBlinkyLoc[1]=blinkyCentre[1]/8;
            break;
        case 3:
            blinkyCentre[0]++;
            currBlinkyLoc[0]=blinkyCentre[0]/8 -18;
            break;
    }
    cout<<"loopcurrBlinkyLoc"<<currBlinkyLoc[0]<<" "<<currBlinkyLoc[1]<<endl;
    attachGhost(blinkyCentre);
    drawGhost(blinkyProgram);
}
void movePinkyLogic0()
{
    currPinkyLoc[0]=(pinkyCentre[0]/8) -18;
    currPinkyLoc[1]=pinkyCentre[1]/8;
    cout<<"movePinkyLogic0 state = "<<currPinkyState<<"ghostSpeed"<<1.0/ghostSpeed<< endl;
    if((currTime - lastGhostMoveTime)>=(1.0/ghostSpeed))
    {
        //lastGhostMoveTime=currTime;
        cout<<"Timer true"<<endl;
        for(i=0;i<4;i++)
        {
            length[i]=9999;
            boxCountArray[i]=0;
        }
        
        boxCount=0;
        
        switch(currPinkyState)
        {
            case 0:

                if(board[currPinkyLoc[1]-1][currPinkyLoc[0]]!=0)
                {
                    boxCountArray[0]=1;
                    boxCount++;
                }
                if(board[currPinkyLoc[1]][currPinkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currPinkyLoc[1]][currPinkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currPinkyState=i;
                            break;
                        }
                    }
                }
                else 
                {
                    
                    if(boxCountArray[0]==1)
                    {
                        length[0]=((currPinkyLoc[0])-(pinkyTargetScatter[0]))*((currPinkyLoc[0])-(pinkyTargetScatter[0]));
                        length[0]+=((currPinkyLoc[1]-1)-(pinkyTargetScatter[1]))*((currPinkyLoc[1]-1)-(pinkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currPinkyLoc[0]-1)-(pinkyTargetScatter[0]))*((currPinkyLoc[0]-1)-(pinkyTargetScatter[0]));
                        length[1]+=((currPinkyLoc[1])-(pinkyTargetScatter[1]))*((currPinkyLoc[1])-(pinkyTargetScatter[1]));
                    }
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currPinkyLoc[0]+1)-(pinkyTargetScatter[0]))*((currPinkyLoc[0]+1)-(pinkyTargetScatter[0]));
                        length[3]+=((currPinkyLoc[1])-(pinkyTargetScatter[1]))*((currPinkyLoc[1])-(pinkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currPinkyState=minn;
                }
               
                break;
            case 1:
                if(board[currPinkyLoc[1]-1][currPinkyLoc[0]]!=0)
                {
                    boxCountArray[0]=1;
                    boxCount++;
                }
                if(board[currPinkyLoc[1]][currPinkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currPinkyLoc[1]+1][currPinkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currPinkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    
                    if(boxCountArray[0]==1)
                    {
                        length[0]=((currPinkyLoc[0])-(pinkyTargetScatter[0]))*((currPinkyLoc[0])-(pinkyTargetScatter[0]));
                        length[0]+=((currPinkyLoc[1]-1)-(pinkyTargetScatter[1]))*((currPinkyLoc[1]-1)-(pinkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currPinkyLoc[0]-1)-(pinkyTargetScatter[0]))*((currPinkyLoc[0]-1)-(pinkyTargetScatter[0]));
                        length[1]+=((currPinkyLoc[1])-(pinkyTargetScatter[1]))*((currPinkyLoc[1])-(pinkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currPinkyLoc[0])-(pinkyTargetScatter[0]))*((currPinkyLoc[0])-(pinkyTargetScatter[0]));
                        length[2]+=((currPinkyLoc[1]+1)-(pinkyTargetScatter[1]))*((currPinkyLoc[1]+1)-(pinkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currPinkyState=minn;
                }  
               
                break;  
            case 2:
                if(board[currPinkyLoc[1]][currPinkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(board[currPinkyLoc[1]][currPinkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currPinkyLoc[1]+1][currPinkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currPinkyState=i;
                            break;
                        }
                    }
                }
                else 
                {
                   
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currPinkyLoc[0]+1)-(pinkyTargetScatter[0]))*((currPinkyLoc[0]+1)-(pinkyTargetScatter[0]));
                        length[3]+=((currPinkyLoc[1])-(pinkyTargetScatter[1]))*((currPinkyLoc[1])-(pinkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currPinkyLoc[0]-1)-(pinkyTargetScatter[0]))*((currPinkyLoc[0]-1)-(pinkyTargetScatter[0]));
                        length[1]+=((currPinkyLoc[1])-(pinkyTargetScatter[1]))*((currPinkyLoc[1])-(pinkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currPinkyLoc[0])-(pinkyTargetScatter[0]))*((currPinkyLoc[0])-(pinkyTargetScatter[0]));
                        length[2]+=((currPinkyLoc[1]+1)-(pinkyTargetScatter[1]))*((currPinkyLoc[1]+1)-(pinkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currPinkyState=minn;
                }    
               
                break;
            case 3:
                if(board[currPinkyLoc[1]][currPinkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(board[currPinkyLoc[1]-1][currPinkyLoc[0]]!=0)
                {
                    boxCountArray[0]=1;
                    boxCount++;
                }   
                if(board[currPinkyLoc[1]+1][currPinkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currPinkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currPinkyLoc[0]+1)-(pinkyTargetScatter[0]))*((currPinkyLoc[0]+1)-(pinkyTargetScatter[0]));
                        length[3]+=((currPinkyLoc[1])-(pinkyTargetScatter[1]))*((currPinkyLoc[1])-(pinkyTargetScatter[1]));
                    }
                    if(boxCountArray[0]==1)
                    {
                        length[0]=((currPinkyLoc[0])-(pinkyTargetScatter[0]))*((currPinkyLoc[0])-(pinkyTargetScatter[0]));
                        length[0]+=((currPinkyLoc[1]-1)-(pinkyTargetScatter[1]))*((currPinkyLoc[1]-1)-(pinkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currPinkyLoc[0])-(pinkyTargetScatter[0]))*((currPinkyLoc[0])-(pinkyTargetScatter[0]));
                        length[2]+=((currPinkyLoc[1]+1)-(pinkyTargetScatter[1]))*((currPinkyLoc[1]+1)-(pinkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currPinkyState=minn;
                }    
                
                break;
        }
        
        cout<<"boxCount"<<boxCount<<endl;
        cout<<"currPinkyState"<<currPinkyState<<endl;
        for(i=0;i<4;i++)
        {
            cout<<length[i]<<endl;
        }
        movePinky();
    }
    else
    {
        cout<<"timer False"<<endl;
        attachGhost(pinkyCentre);
        drawGhost(pinkyProgram);
    }
}
void movePinky()
{
    currPinkyLoc[0]=(pinkyCentre[0]/8) -18;
    currPinkyLoc[1]=pinkyCentre[1]/8;
    switch(currPinkyState)
    {
        case 0:
            pinkyCentre[1]--;
            currPinkyLoc[1]=pinkyCentre[1]/8;
            break;
        case 1:
            pinkyCentre[0]--;
            currPinkyLoc[0]=pinkyCentre[0]/8 - 18;
            break;
        case 2:
            pinkyCentre[1]++;
            currPinkyLoc[1]=pinkyCentre[1]/8;
            break;
        case 3:
            pinkyCentre[0]++;
            currPinkyLoc[0]=pinkyCentre[0]/8 -18;
            break;
    }
    cout<<"loopcurrPinkyLoc"<<currPinkyLoc[0]<<" "<<currPinkyLoc[1]<<endl;
    attachGhost(pinkyCentre);
    drawGhost(pinkyProgram);
}
void moveInkyLogic0()
{
    currInkyLoc[0]=(inkyCentre[0]/8) -18;
    currInkyLoc[1]=inkyCentre[1]/8;
    cout<<"moveInkyLogic0 state = "<<currInkyState<<"ghostSpeed"<<1.0/ghostSpeed<< endl;
    if((currTime - lastGhostMoveTime)>=(1.0/ghostSpeed))
    {
        cout<<"Timer true"<<endl;
        for(i=0;i<4;i++)
        {
            length[i]=9999;
            boxCountArray[i]=0;
        }
        //lastGhostMoveTime=currTime;
        boxCount=0;
        switch(currInkyState)
        {
            case 0:

                if(board[currInkyLoc[1]-1][currInkyLoc[0]]!=0)
                {
                    cout<<"Empty1"<<endl;
                    boxCountArray[0]=1;
                    boxCount++;
                }
                if(board[currInkyLoc[1]][currInkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currInkyLoc[1]][currInkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currInkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[0]==1)
                    {
                        cout<<"Empty"<<endl;
                        length[0]=((currInkyLoc[0])-(inkyTargetScatter[0]))*((currInkyLoc[0])-(inkyTargetScatter[0]));
                        length[0]+=((currInkyLoc[1]-1)-(inkyTargetScatter[1]))*((currInkyLoc[1]-1)-(inkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currInkyLoc[0]-1)-(inkyTargetScatter[0]))*((currInkyLoc[0]-1)-(inkyTargetScatter[0]));
                        length[1]+=((currInkyLoc[1])-(inkyTargetScatter[1]))*((currInkyLoc[1])-(inkyTargetScatter[1]));
                    }
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currInkyLoc[0]+1)-(inkyTargetScatter[0]))*((currInkyLoc[0]+1)-(inkyTargetScatter[0]));
                        length[3]+=((currInkyLoc[1])-(inkyTargetScatter[1]))*((currInkyLoc[1])-(inkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currInkyState=minn;
                }
                break;
            case 1:
                if(board[currInkyLoc[1]-1][currInkyLoc[0]]!=0)
                {
                    boxCountArray[0]=1;
                    boxCount++;
                }
                if(board[currInkyLoc[1]][currInkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currInkyLoc[1]+1][currInkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currInkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[0]==1)
                    {
                        length[0]=((currInkyLoc[0])-(inkyTargetScatter[0]))*((currInkyLoc[0])-(inkyTargetScatter[0]));
                        length[0]+=((currInkyLoc[1]-1)-(inkyTargetScatter[1]))*((currInkyLoc[1]-1)-(inkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currInkyLoc[0]-1)-(inkyTargetScatter[0]))*((currInkyLoc[0]-1)-(inkyTargetScatter[0]));
                        length[1]+=((currInkyLoc[1])-(inkyTargetScatter[1]))*((currInkyLoc[1])-(inkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currInkyLoc[0])-(inkyTargetScatter[0]))*((currInkyLoc[0])-(inkyTargetScatter[0]));
                        length[2]+=((currInkyLoc[1]+1)-(inkyTargetScatter[1]))*((currInkyLoc[1]+1)-(inkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currInkyState=minn;
                }  
                break;  
            case 2:
                if(board[currInkyLoc[1]][currInkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(board[currInkyLoc[1]][currInkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currInkyLoc[1]+1][currInkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currInkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currInkyLoc[0]+1)-(inkyTargetScatter[0]))*((currInkyLoc[0]+1)-(inkyTargetScatter[0]));
                        length[3]+=((currInkyLoc[1])-(inkyTargetScatter[1]))*((currInkyLoc[1])-(inkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currInkyLoc[0]-1)-(inkyTargetScatter[0]))*((currInkyLoc[0]-1)-(inkyTargetScatter[0]));
                        length[1]+=((currInkyLoc[1])-(inkyTargetScatter[1]))*((currInkyLoc[1])-(inkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currInkyLoc[0])-(inkyTargetScatter[0]))*((currInkyLoc[0])-(inkyTargetScatter[0]));
                        length[2]+=((currInkyLoc[1]+1)-(inkyTargetScatter[1]))*((currInkyLoc[1]+1)-(inkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currInkyState=minn;
                }    
                break;
            case 3:
                if(board[currInkyLoc[1]][currInkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(board[currInkyLoc[1]-1][currInkyLoc[0]]!=0)
                {
                    boxCountArray[0]=1;
                    boxCount++;
                }   
                if(board[currInkyLoc[1]+1][currInkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currInkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currInkyLoc[0]+1)-(inkyTargetScatter[0]))*((currInkyLoc[0]+1)-(inkyTargetScatter[0]));
                        length[3]+=((currInkyLoc[1])-(inkyTargetScatter[1]))*((currInkyLoc[1])-(inkyTargetScatter[1]));
                    }
                    if(boxCountArray[0]==1)
                    {
                        length[0]=((currInkyLoc[0])-(inkyTargetScatter[0]))*((currInkyLoc[0])-(inkyTargetScatter[0]));
                        length[0]+=((currInkyLoc[1]-1)-(inkyTargetScatter[1]))*((currInkyLoc[1]-1)-(inkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currInkyLoc[0])-(inkyTargetScatter[0]))*((currInkyLoc[0])-(inkyTargetScatter[0]));
                        length[2]+=((currInkyLoc[1]+1)-(inkyTargetScatter[1]))*((currInkyLoc[1]+1)-(inkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currInkyState=minn;
                }    
                break;
        }
        cout<<"boxCount"<<boxCount<<endl;
        cout<<"currInkyState"<<currInkyState<<endl;
        for(i=0;i<4;i++)
        {
            cout<<length[i]<<endl;
        }
        moveInky();
    }
    else
    {
        cout<<"timer False"<<endl;
        attachGhost(inkyCentre);
        drawGhost(inkyProgram);
    }
}
void moveInky()
{
    currInkyLoc[0]=(inkyCentre[0]/8) -18;
    currInkyLoc[1]=inkyCentre[1]/8;
    switch(currInkyState)
    {
        case 0:
            inkyCentre[1]--;
            currInkyLoc[1]=inkyCentre[1]/8;
            break;
        case 1:
            inkyCentre[0]--;
            currInkyLoc[0]=inkyCentre[0]/8 - 18;
            break;
        case 2:
            inkyCentre[1]++;
            currInkyLoc[1]=inkyCentre[1]/8;
            break;
        case 3:
            inkyCentre[0]++;
            currInkyLoc[0]=inkyCentre[0]/8 -18;
            break;
    }
    cout<<"centre"<<inkyCentre[0]<<" "<<inkyCentre[1];
    cout<<"loopcurrInkyLoc"<<currInkyLoc[0]<<" "<<currInkyLoc[1]<<endl;
    attachGhost(inkyCentre);
    drawGhost(inkyProgram);
}
void moveClinkyLogic0()
{
    currClinkyLoc[0]=(clinkyCentre[0]/8) -18;
    currClinkyLoc[1]=clinkyCentre[1]/8;
    cout<<"moveClinkyLogic0 state = "<<currClinkyState<<"ghostSpeed"<<1.0/ghostSpeed<< endl;
    if((currTime - lastGhostMoveTime)>=(1.0/ghostSpeed))
    {
        cout<<"Timer true"<<endl;
        for(i=0;i<4;i++)
        {
            length[i]=9999;
            boxCountArray[i]=0;
        }
        lastGhostMoveTime=currTime;
        boxCount=0;
        switch(currClinkyState)
        {
            case 0:

                if(board[currClinkyLoc[1]-1][currClinkyLoc[0]]!=0)
                {
                    cout<<"Empty1"<<endl;
                    boxCountArray[0]=1;
                    boxCount++;
                }
                if(board[currClinkyLoc[1]][currClinkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currClinkyLoc[1]][currClinkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currClinkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[0]==1)
                    {
                        cout<<"Empty"<<endl;
                        length[0]=((currClinkyLoc[0])-(clinkyTargetScatter[0]))*((currClinkyLoc[0])-(clinkyTargetScatter[0]));
                        length[0]+=((currClinkyLoc[1]-1)-(clinkyTargetScatter[1]))*((currClinkyLoc[1]-1)-(clinkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currClinkyLoc[0]-1)-(clinkyTargetScatter[0]))*((currClinkyLoc[0]-1)-(clinkyTargetScatter[0]));
                        length[1]+=((currClinkyLoc[1])-(clinkyTargetScatter[1]))*((currClinkyLoc[1])-(clinkyTargetScatter[1]));
                    }
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currClinkyLoc[0]+1)-(clinkyTargetScatter[0]))*((currClinkyLoc[0]+1)-(clinkyTargetScatter[0]));
                        length[3]+=((currClinkyLoc[1])-(clinkyTargetScatter[1]))*((currClinkyLoc[1])-(clinkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currClinkyState=minn;
                }
                break;
            case 1:
                if(board[currClinkyLoc[1]-1][currClinkyLoc[0]]!=0)
                {
                    boxCountArray[0]=1;
                    boxCount++;
                }
                if(board[currClinkyLoc[1]][currClinkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currClinkyLoc[1]+1][currClinkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currClinkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[0]==1)
                    {
                        length[0]=((currClinkyLoc[0])-(clinkyTargetScatter[0]))*((currClinkyLoc[0])-(clinkyTargetScatter[0]));
                        length[0]+=((currClinkyLoc[1]-1)-(clinkyTargetScatter[1]))*((currClinkyLoc[1]-1)-(clinkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currClinkyLoc[0]-1)-(clinkyTargetScatter[0]))*((currClinkyLoc[0]-1)-(clinkyTargetScatter[0]));
                        length[1]+=((currClinkyLoc[1])-(clinkyTargetScatter[1]))*((currClinkyLoc[1])-(clinkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currClinkyLoc[0])-(clinkyTargetScatter[0]))*((currClinkyLoc[0])-(clinkyTargetScatter[0]));
                        length[2]+=((currClinkyLoc[1]+1)-(clinkyTargetScatter[1]))*((currClinkyLoc[1]+1)-(clinkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currClinkyState=minn;
                }  
                break;  
            case 2:
                if(board[currClinkyLoc[1]][currClinkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(board[currClinkyLoc[1]][currClinkyLoc[0]-1]!=0)
                {
                    boxCountArray[1]=1;
                    boxCount++;
                }   
                if(board[currClinkyLoc[1]+1][currClinkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currClinkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currClinkyLoc[0]+1)-(clinkyTargetScatter[0]))*((currClinkyLoc[0]+1)-(clinkyTargetScatter[0]));
                        length[3]+=((currClinkyLoc[1])-(clinkyTargetScatter[1]))*((currClinkyLoc[1])-(clinkyTargetScatter[1]));
                    }
                    if(boxCountArray[1]==1)
                    {
                        length[1]=((currClinkyLoc[0]-1)-(clinkyTargetScatter[0]))*((currClinkyLoc[0]-1)-(clinkyTargetScatter[0]));
                        length[1]+=((currClinkyLoc[1])-(clinkyTargetScatter[1]))*((currClinkyLoc[1])-(clinkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currClinkyLoc[0])-(clinkyTargetScatter[0]))*((currClinkyLoc[0])-(clinkyTargetScatter[0]));
                        length[2]+=((currClinkyLoc[1]+1)-(clinkyTargetScatter[1]))*((currClinkyLoc[1]+1)-(clinkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currClinkyState=minn;
                }    
                break;
            case 3:
                if(board[currClinkyLoc[1]][currClinkyLoc[0]+1]!=0)
                {
                    boxCountArray[3]=1;
                    boxCount++;
                }
                if(board[currClinkyLoc[1]-1][currClinkyLoc[0]]!=0)
                {
                    boxCountArray[0]=1;
                    boxCount++;
                }   
                if(board[currClinkyLoc[1]+1][currClinkyLoc[0]]!=0)
                {
                    boxCountArray[2]=1;
                    boxCount++;
                }
                if(boxCount==1)
                {
                    for(i=0;i<4;i++)
                    {
                        if(boxCountArray[i]==1)
                        {
                            currClinkyState=i;
                            break;
                        }
                    }
                }
                else
                {
                    if(boxCountArray[3]==1)
                    {
                        length[3]=((currClinkyLoc[0]+1)-(clinkyTargetScatter[0]))*((currClinkyLoc[0]+1)-(clinkyTargetScatter[0]));
                        length[3]+=((currClinkyLoc[1])-(clinkyTargetScatter[1]))*((currClinkyLoc[1])-(clinkyTargetScatter[1]));
                    }
                    if(boxCountArray[0]==1)
                    {
                        length[0]=((currClinkyLoc[0])-(clinkyTargetScatter[0]))*((currClinkyLoc[0])-(clinkyTargetScatter[0]));
                        length[0]+=((currClinkyLoc[1]-1)-(clinkyTargetScatter[1]))*((currClinkyLoc[1]-1)-(clinkyTargetScatter[1]));
                    }
                    if(boxCountArray[2]==1)
                    {
                        length[2]=((currClinkyLoc[0])-(clinkyTargetScatter[0]))*((currClinkyLoc[0])-(clinkyTargetScatter[0]));
                        length[2]+=((currClinkyLoc[1]+1)-(clinkyTargetScatter[1]))*((currClinkyLoc[1]+1)-(clinkyTargetScatter[1]));
                    }
                    minn=0;
                    minnCount=0;
                    for(i=0;i<4;i++)
                    {
                        if(length[i]<length[minn])
                        {
                            minn=i;
                        }
                    }
                    currClinkyState=minn;
                }    
                break;
        }
        cout<<"boxCount"<<boxCount<<endl;
        cout<<"currClinkyState"<<currClinkyState<<endl;
        for(i=0;i<4;i++)
        {
            cout<<length[i]<<endl;
        }
        moveClinky();
    }
    else
    {
        cout<<"timer False"<<endl;
        attachGhost(clinkyCentre);
        drawGhost(clinkyProgram);
    }
}
void moveClinky()
{
    currClinkyLoc[0]=(clinkyCentre[0]/8) -18;
    currClinkyLoc[1]=clinkyCentre[1]/8;
    switch(currClinkyState)
    {
        case 0:
            clinkyCentre[1]--;
            currClinkyLoc[1]=clinkyCentre[1]/8;
            break;
        case 1:
            clinkyCentre[0]--;
            currClinkyLoc[0]=clinkyCentre[0]/8 - 18;
            break;
        case 2:
            clinkyCentre[1]++;
            currClinkyLoc[1]=clinkyCentre[1]/8;
            break;
        case 3:
            clinkyCentre[0]++;
            currClinkyLoc[0]=clinkyCentre[0]/8 -18;
            break;
    }
    cout<<"centre"<<clinkyCentre[0]<<" "<<clinkyCentre[1];
    cout<<"loopcurrClinkyLoc"<<currClinkyLoc[0]<<" "<<currClinkyLoc[1]<<endl;
    attachGhost(clinkyCentre);
    drawGhost(clinkyProgram);
}

/*
void splashScreen()
{

}
void pause()
{

}
void gameOver()
{

}
void levelWon()
{

}
*/
void gameOverWindow(int score1){
    int temp=0,d;
    
    charPrint(218 , 137 , 'G');
    charPrint(226 , 137 , 'A');
    charPrint(234 , 137 , 'M');
    charPrint(242 , 137 , 'E');
    charPrint(258 , 137 , 'O');
    charPrint(264 , 137 , 'V');
    charPrint(272 , 137 , 'E');
    charPrint(280 , 137 , 'R');
    while(score1!=0)
    {
        d=score1%10;
        score1/=10;
        charPrint(258 -temp, 157 , d+48);
        temp+=8;
    }

}
void youWin(){
    int temp=192;
   /* charPrint(temp,137 , 'L');
    charPrint(temp+8,137 , 'E');
    charPrint(temp+16,137 , 'V');
    charPrint(temp+24,137 , 'E');*/
    charPrint(temp+32,137 , 'Y');
    charPrint(temp+40,137 , 'O');
    charPrint(temp+48,137 , 'U');
    //charPrint(temp+72,137 , 'M');
    charPrint(temp+72,137 , 'W');
    charPrint(temp+80,137 , 'O');
    charPrint(temp+88,137 , 'N');
    /*charPrint(temp+96,137 , 'T');
    charPrint(temp+104,137 , 'E');*/
    charPrint(temp+48,157 , '2');
    charPrint(temp+56,157 , '6');
    charPrint(temp+64,157 , '0');
    charPrint(temp+72,157 , '0');





}

void charPrint(float x , float y , char m)
{
  

    switch(m)
    { case '5' :
      case 'S' :
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 
        }; 
           glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
       } break;
    

    case 'R':
       { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+4)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+4)*(tempy)), 0.0 ,
          ((x+2)*(tempx))-1 ,1-((y+4)*(tempy)), 0.0 ,
          ((x+2)*(tempx))-1 ,1-((y+4)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,


          };     glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
           } break;
    case 'E':
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          
        };     glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;
    case 'A':
        { float vertices1[]={
          (x*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
        };      glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;   
    case 'M':
        {float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,

        };     glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break; 

         case 'O':
         case '0':
        {float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,

        };     glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;        
    case 'V':
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 
         
        };     glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;
         case 'H':
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0
         

        };      glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break; 
       case 'I':
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 
         

        };       glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;    
      
    case 'X':
        {float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0
          

        };      glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;     
     case 'T':
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0
          

        };    glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;
     case 'N':
        { float vertices1[]={
          (x*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 
          

        };     glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;  
      case 'U':
        {float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 
        

        };     glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break; 
           case 'W':
        { float vertices1[]={
          ((x)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0, 
          
         
        };      glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;    
      case 'P':
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 
         
        };      glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;  
      case 'C':
        {float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
           ((x)*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
            ((x+7)*(tempx))-1 ,1-(y*(tempy)), 0.0 
         };
   glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;
     case 'Y':
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 
         

        };    glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;                                                                                                     
     case 'G':
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+4)*(tempy)), 0.0 ,
           ((x+7)*(tempx))-1 ,1-((y+4)*(tempy)), 0.0 ,
            ((x+2)*(tempx))-1 ,1-((y+4)*(tempy)), 0.0 ,
            //((x+2)*(tempx))-1 ,1-((y+4)*(tempy)), 0.0 ,

        };     glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;
     case '1':
       { float vertices1[]={
          (x*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+3)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0
         

        };        glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;
      case '2':
        {float vertices1[]={
                (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
           ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
         

        };     glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;  
      case '3':
        { float vertices1[]={
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
           ((x)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
            ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0
            
         

        };      glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;    
       case '6':
        { float vertices1[]={
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
           ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
            ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0,
             ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0,
              ((x)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0
         

        };      glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;    
     
    case '4':
        {
            float vertices1[]={
          ((x+5)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+5)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+5)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+6)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+6)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+6)*(tempy)), 0.0 
          
          };      glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
       } break;
    case '7':
        { float vertices1[]={
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 
          
         

        };    glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;     
     case '8':
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          (x*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
        ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
        };      glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);
         } break;     
                
      case '9':
        { float vertices1[]={
          (x*(tempx))-1 ,1-(y*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+7)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 ,
          ((x+7)*(tempx))-1 ,1-((y+3)*(tempy)), 0.0 
         
        };      glBindVertexArray(vaoChar);
        glBindBuffer(GL_ARRAY_BUFFER,vboChar);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);  
          glUseProgram(textProgram);
    glBindVertexArray(vaoChar);
    glLineWidth(1.0);
    glDrawArrays(GL_LINES,0,2000);

         } break;    
     
} 
}
void checkGameOver()
{
    if(((currPacLoc[0]==currBlinkyLoc[0] && currPacLoc[1]==currBlinkyLoc[1]))
        || ((currPacLoc[0]==currPinkyLoc[0] && currPacLoc[1]==currPinkyLoc[1]))
        || ((currPacLoc[0]==currInkyLoc[0] && currPacLoc[1]==currInkyLoc[1]))
        ||  ((currPacLoc[0]==currClinkyLoc[0] && currPacLoc[1]==currClinkyLoc[1])))
    {
        gameOver=1;
    }
}
void attachScore(int score1)
{
    int d,temp=0;
    charPrint(216,8,'S');
    charPrint(224,8,'C');
    charPrint(232,8,'O');
    charPrint(240,8,'R');
    charPrint(248,8,'E');
    while(score1!=0)
    {
        d=score1%10;
        score1=score1/10;
        charPrint(296-temp,8,(char)d+48);
        temp+=8;
    }
}
void drawStart(GLFWwindow* window)
{   
   
float startCurrTime,startScreenStartTime;
int startScreenSpeed=20;
    //displaying Pacman
    
    int posx=0 , posy=0;
    startScreenStartTime=glfwGetTime();
     startCurrTime=startScreenStartTime;
    while(!glfwWindowShouldClose(window))
    {
      glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if(glfwGetKey(window,GLFW_KEY_ENTER)==GLFW_PRESS)
        {
        glfwSwapBuffers(window);
        glfwPollEvents();
        break;
        }
      startCurrTime=glfwGetTime();
      charPrint(218 , 80 , 'P');
    charPrint(226 , 80 , 'A');
    charPrint(234 , 80 , 'C');
    charPrint(250 , 80 , 'M');
    charPrint(258 , 80 , 'A');
    charPrint(264 , 80 , 'N');
    cout<<startCurrTime- startScreenStartTime<<" "<<1.0/startScreenSpeed<<endl;
      if((startCurrTime- startScreenStartTime) > (1.0/startScreenSpeed))
      {
        cout<<"True"<<endl;
        startScreenStartTime=startCurrTime;
        posx+=3;
      }
    posx=posx%224;

    pacmanCentre[0]=144+posx,pacmanCentre[1]=170;
    attachPacmanRight();
    drawPacmanRight();

    blinkyCentre[0]=160+posx,blinkyCentre[1]=170;
    attachGhost(blinkyCentre);
    drawGhost(blinkyProgram);

    inkyCentre[0]=172+posx,inkyCentre[1]=170;
    attachGhost(inkyCentre);
    drawGhost(inkyProgram);
    
    pinkyCentre[0]=188+posx,pinkyCentre[1]=170;
    attachGhost(pinkyCentre);
    drawGhost(pinkyProgram);
    
    clinkyCentre[0]=104+posx,clinkyCentre[1]=170;
    attachGhost(clinkyCentre);
    drawGhost(clinkyProgram);
    

    glfwSwapBuffers(window);
    glfwPollEvents();
    }

}
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *referenceLineShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";
const char *wallShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
    "}\n\0";
const char *pacmanShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";
const char *coinShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.8f, 0.6f, 1.0f);\n"
    "}\n\0";
const char *blinkyShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";
const char *pinkyShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.6f, 0.8f, 1.0f);\n"
    "}\n\0";
const char *inkyShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.4f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";
const char *clinkyShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.8f, 0.4f, 1.0f);\n"
    "}\n\0";
const char *textShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";
int main()
{
    int success,i,j;
    char infoLog[512];
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window=glfwCreateWindow(WIDTH,HEIGHT,"Pac-ManGL",NULL,NULL);
    if(window==NULL)
    {
        cout<<"Failed to create GLFW window"<<endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout<<"Failed to initialize GLAD"<<endl;
        return -1;
    }
    glViewport(0,0,WIDTH,HEIGHT);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    int vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int referenceLineShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(referenceLineShader, 1, &referenceLineShaderSource, NULL);
    glCompileShader(referenceLineShader);
    glGetShaderiv(referenceLineShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(referenceLineShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::referenceLine::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int wallShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(wallShader, 1, &wallShaderSource, NULL);
    glCompileShader(wallShader);
    glGetShaderiv(wallShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(wallShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::wall::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int pacmanShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(pacmanShader, 1, &pacmanShaderSource, NULL);
    glCompileShader(pacmanShader);
    glGetShaderiv(pacmanShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(pacmanShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::pacman::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    

    int coinShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(coinShader, 1, &coinShaderSource, NULL);
    glCompileShader(coinShader);
    glGetShaderiv(coinShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(coinShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::coin::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int blinkyShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(blinkyShader, 1, &blinkyShaderSource, NULL);
    glCompileShader(blinkyShader);
    glGetShaderiv(blinkyShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(blinkyShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::blinky::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int pinkyShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(pinkyShader, 1, &pinkyShaderSource, NULL);
    glCompileShader(pinkyShader);
    glGetShaderiv(pinkyShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(pinkyShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::pinky::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int inkyShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(inkyShader, 1, &inkyShaderSource, NULL);
    glCompileShader(inkyShader);
    glGetShaderiv(inkyShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(inkyShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::inky::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int clinkyShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(clinkyShader, 1, &clinkyShaderSource, NULL);
    glCompileShader(clinkyShader);
    glGetShaderiv(clinkyShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(clinkyShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::clinky::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int textShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(textShader, 1, &textShaderSource, NULL);
    glCompileShader(textShader);
    glGetShaderiv(textShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(textShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::text::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    wallProgram=glCreateProgram();
    glAttachShader(wallProgram,vertexShader);
    glAttachShader(wallProgram,wallShader);
    glLinkProgram(wallProgram);
    glGetProgramiv(wallProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(wallProgram, 512, NULL, infoLog);
        std::cout << "ERROR::wall::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    referenceLineProgram=glCreateProgram();
    glAttachShader(referenceLineProgram,vertexShader);
    glAttachShader(referenceLineProgram,referenceLineShader);
    glLinkProgram(referenceLineProgram);
    glGetProgramiv(referenceLineProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(referenceLineProgram, 512, NULL, infoLog);
        std::cout << "ERROR::referenceLine::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    pacmanProgram=glCreateProgram();
    glAttachShader(pacmanProgram,vertexShader);
    glAttachShader(pacmanProgram,pacmanShader);
    glLinkProgram(pacmanProgram);
    glGetProgramiv(pacmanProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(pacmanProgram, 512, NULL, infoLog);
        std::cout << "ERROR::pacman::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    coinProgram=glCreateProgram();
    glAttachShader(coinProgram,vertexShader);
    glAttachShader(coinProgram,coinShader);
    glLinkProgram(coinProgram);
    glGetProgramiv(coinProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(coinProgram, 512, NULL, infoLog);
        std::cout << "ERROR::coin::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    blinkyProgram=glCreateProgram();
    glAttachShader(blinkyProgram,vertexShader);
    glAttachShader(blinkyProgram,blinkyShader);
    glLinkProgram(blinkyProgram);
    glGetProgramiv(blinkyProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(blinkyProgram, 512, NULL, infoLog);
        std::cout << "ERROR::blinky::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    pinkyProgram=glCreateProgram();
    glAttachShader(pinkyProgram,vertexShader);
    glAttachShader(pinkyProgram,pinkyShader);
    glLinkProgram(pinkyProgram);
    glGetProgramiv(pinkyProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(pinkyProgram, 512, NULL, infoLog);
        std::cout << "ERROR::pinky::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    inkyProgram=glCreateProgram();
    glAttachShader(inkyProgram,vertexShader);
    glAttachShader(inkyProgram,inkyShader);
    glLinkProgram(inkyProgram);
    glGetProgramiv(inkyProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(inkyProgram, 512, NULL, infoLog);
        std::cout << "ERROR::inky::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    clinkyProgram=glCreateProgram();
    glAttachShader(clinkyProgram,vertexShader);
    glAttachShader(clinkyProgram,clinkyShader);
    glLinkProgram(clinkyProgram);
    glGetProgramiv(clinkyProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(clinkyProgram, 512, NULL, infoLog);
        std::cout << "ERROR::clinky::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    textProgram=glCreateProgram();
    glAttachShader(textProgram,vertexShader);
    glAttachShader(textProgram,textShader);
    glLinkProgram(textProgram);
    glGetProgramiv(textProgram,GL_LINK_STATUS,&success);
    if (!success) 
    {
        glGetProgramInfoLog(textProgram, 512, NULL, infoLog);
        std::cout << "ERROR::text::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(referenceLineShader);
    glDeleteShader(wallShader);
    glDeleteShader(coinShader);
    glDeleteShader(blinkyShader);
    glDeleteShader(pinkyShader);
    glDeleteShader(inkyShader);
    glDeleteShader(clinkyShader);
    glDeleteShader(textShader);

    glfwSetKeyCallback(window, key_callback);
    
    glGenVertexArrays(2*40,&vaoReferenceLine[0][0]);
    glGenBuffers(2*40,&vboReferenceLine[0][0]);
    glGenVertexArrays(1,&vaoWall);
    glGenBuffers(1,&vboWall);
    glGenVertexArrays(1,&vaoPacmanStable);
    glGenBuffers(1,&vboPacmanStable);
    glGenVertexArrays(1,&vaoPacmanRight);
    glGenBuffers(1,&vboPacmanRight);
    glGenVertexArrays(1,&vaoPacmanLeft);
    glGenBuffers(1,&vboPacmanLeft);
    glGenVertexArrays(1,&vaoPacmanUp);
    glGenBuffers(1,&vboPacmanUp);
    glGenVertexArrays(1,&vaoPacmanDown);
    glGenBuffers(1,&vboPacmanDown);
    glGenVertexArrays(1,&vaoGhost);
    glGenBuffers(1,&vboGhost);
    glGenVertexArrays(35*28,&vaoCoin[0][0]);
    glGenBuffers(35*28,&vboCoin[0][0]);
    glGenVertexArrays(1,&vaoCentreLine);
    glGenBuffers(1,&vboCentreLine);
    glGenVertexArrays(1,&vaoChar);
    glGenBuffers(1,&vboChar);
    glGenVertexArrays(1,&vaoBigCoin1);
    glGenBuffers(1,&vboBigCoin1);
    glGenVertexArrays(1,&vaoBigCoin2);
    glGenBuffers(1,&vboBigCoin2);
    glGenVertexArrays(1,&vaoBigCoin3);
    glGenBuffers(1,&vboBigCoin3);
    glGenVertexArrays(1,&vaoBigCoin4);
    glGenBuffers(1,&vboBigCoin4);
    
    x=(2.0/WIDTH),y=(2.0/HEIGHT);
    attachReferenceLines();
    attachWall();
    long long xx=0;
    pacmanCentre[0]=256;
    pacmanCentre[1]=((26*8)+4);
    blinkyCentre[0]=256;
    blinkyCentre[1]=(14*8)+4;
    //pinkyCentre[0]=256;
    //pinkyCentre[1]=(17*8)+4;
    //inkyCentre[0]=256;
    //inkyCentre[1]=(17*8)+4;
    //clinkyCentre[0]=272;
    //clinkyCentre[1]=(17*8)+4;
    //drawStart(window);
    pinkyCentre[0]=blinkyCentre[0];
    pinkyCentre[1]=blinkyCentre[1];
    inkyCentre[0]=blinkyCentre[0];
    inkyCentre[1]=blinkyCentre[1];
    clinkyCentre[0]=blinkyCentre[0];
    clinkyCentre[1]=blinkyCentre[1];
    attachCoins();
    currBlinkyState=1;
    currPinkyState=1;
    currInkyState=1;
    currClinkyState=1;
    float startTime=glfwGetTime();
    lastPacmanMoveTime=startTime;
    lastBlinkyMoveTime=startTime;
    currPacLoc[0]=pacmanCentre[0]/8 -18;
    currPacLoc[1]=pacmanCentre[1]/8;
    currBlinkyLoc[0]=blinkyCentre[0]/8 -18;
    currBlinkyLoc[1]=blinkyCentre[1]/8;
    currPinkyLoc[0]=pinkyCentre[0]/8 -18;
    currPinkyLoc[1]=pinkyCentre[1]/8;
    currInkyLoc[0]=inkyCentre[0]/8 -18;
    currInkyLoc[1]=inkyCentre[1]/8;
    cout<<"Reached"<<endl;
    currMode=0;
    lastModeChangeTime=glfwGetTime();
    float ttt=glfwGetTime();
    system("canberra-gtk-play -f pacman_beginning.wav");
    while(!glfwWindowShouldClose(window))
    {
        
        
        //cout<<stopForSomeFrame<<endl;
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if(gameOver==0)
        {
            checkGameOver();
        }
        else
        {
            gameOverWindow(score);
            soundd--;
            
        }
        if(score==2600 && gameOver==0)
        {
            youWin();
        }
        else if(gameOver==0)
        {
        
            currTime=glfwGetTime();
        movePacmanLogic();
        changeMode();
        switch(currMode)
        {
            case 0:
                blinkyTargetScatter[0]=26;
                blinkyTargetScatter[1]=1;
                pinkyTargetScatter[0]=2;
                pinkyTargetScatter[1]=0;
                inkyTargetScatter[0]=28;
                inkyTargetScatter[1]=35;
                clinkyTargetScatter[0]=0;
                clinkyTargetScatter[1]=35;
                moveBlinkyLogic0();
                movePinkyLogic0();
                moveInkyLogic0();
                moveClinkyLogic0();
                break;
            case 1:
                blinkyTargetScatter[0]=currPacLoc[0];
                blinkyTargetScatter[1]=currPacLoc[1];
                pinkyTargetScatter[0]=currPacLoc[0]x;
                pinkyTargetScatter[1]=currPacLoc[1];
                inkyTargetScatter[0]=currPacLoc[0];
                inkyTargetScatter[1]=currPacLoc[1];
                clinkyTargetScatter[0]=26;
                clinkyTargetScatter[1]=1;
                moveBlinkyLogic0();
                movePinkyLogic0();
                moveInkyLogic0();
                moveClinkyLogic0();
                break;
                //moveBlinkyLogic1();
                break;
            case 2:
                //moveBlinkyLogic2();
                break;
        }

        
        drawCoins();

        attachGhost(blinkyCentre);
        drawGhost(blinkyProgram);
        attachGhost(pinkyCentre);
        drawGhost(pinkyProgram);
        attachGhost(inkyCentre);
        drawGhost(inkyProgram);
        attachGhost(clinkyCentre);
        drawGhost(clinkyProgram);
        drawWall();
        attachScore(score);
        cout<<"score "<<score<<endl; 
        
        }
    
        glfwSwapBuffers(window);
        glfwPollEvents();
        if(gameOver==1 && soundd==0)
              {
               soundd=5;
               system("canberra-gtk-play -f pacman_intermission.wav");
                 }

        cout<<"c "<<currPacLoc[0]<<" "<<currPacLoc[1]<<endl;
        
    }
    glDeleteVertexArrays(1,&vaoReferenceLine[0][0]);
    glDeleteBuffers(1,&vboReferenceLine[0][0]);
    glfwTerminate();


    

}