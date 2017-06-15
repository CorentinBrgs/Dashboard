/* Matrix.h Library for commanding 8*8 RGB Matrix with two 
   MCP23017 controllers
   Created by Corentin BERGES May 20th 2017
*/

#ifndef Matrix_h
#define Matrix_h

#include <Arduino.h>
#include <Wire.h>
#include <MCP23017.h>

class Matrix {
  public :
    Matrix(byte addr1, byte addr2, byte portLine, byte portRed, byte portGreen, byte portBlue);
    void begin();
    void disp();
    void input(byte matrixTab[8][8]); 
    void clear();

    void writeLine(byte lineMask);
    void writeRed(byte redMask);
    void writeGreen(byte greenMask);
    void writeBlue(byte blueMask);
    void lineDisp(byte lineNumber);
    void gearDisp(byte gear, byte color);
    void flagDisp(bool yellowFlag, bool blueFlag, bool whiteFlag);
    void bargraphDisp(int motorSpeed, int morotSpeedMin, int motorSpeedMax);
  
    byte _addrLine;
    byte _addrRed;
    byte _addrGreen;
    byte _addrBlue;

    MCP23017 MCPLine = MCP23017(_addrLine, _portLine[0]);
    MCP23017 MCPRed = MCP23017(_addrRed, _portRed[0]);
    MCP23017 MCPGreen = MCP23017(_addrGreen, _portGreen[0]);
    MCP23017 MCPBlue = MCP23017(_addrBlue, _portBlue[0]);



    //byte _portLine[2] ;


  private :
    byte _addr1;
    byte _addr2;

    byte _portLine[2] ;
    byte _portRed[2] ;
    byte _portGreen[2] ; 
    byte _portBlue[2] ;

    //byte _matrixTab[8][8] = 
       /* 1 = bleu
        * 2 = vert 
        * 3 = cyan
        * 4 = rouge
        * 5 = magenta
        * 6 = jaune
        * 7 = blanc
        */

    byte _halfDisp = 0;
    byte _matrixTab[8][8] = 
				{{2,2,2,2,6,6,4,4},
				 {0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0}};
    byte _colorTab[3] = {0,0,0};

    MCP23017 MCP_0 = MCP23017(_addr1);
    MCP23017 MCP_1 = MCP23017(_addr2);

    byte _gearColor = 0;
    byte _gear = 0;
    byte _gearTab[11][6][4]=
    {
        {{0,1,1,0},
         {1,0,0,1},
         {1,0,0,1},
         {1,0,0,1},
         {1,0,0,1},
         {0,1,1,0}},

        {{0,0,1,0},
         {0,1,1,0},
         {1,0,1,0},
         {0,0,1,0},
         {0,0,1,0},
         {0,0,1,0}},

        {{0,1,1,0},
         {1,0,0,1},
         {0,0,0,1},
         {0,0,1,0},
         {0,1,0,0},
         {1,1,1,1}},

        {{1,1,1,0},
         {0,0,0,1},
         {0,1,1,0},
         {0,0,0,1},
         {0,0,0,1},
         {1,1,1,0}},
        
        {{1,0,0,0},
         {1,0,0,0},
         {1,0,1,0},
         {1,1,1,1},
         {0,0,1,0},
         {0,0,1,0}},
        
        {{1,1,1,1},
         {1,0,0,0},
         {1,1,1,0},
         {0,0,0,1},
         {0,0,0,1},
         {1,1,1,0}},

        {{0,1,1,0},
         {1,0,0,0},
         {1,1,1,0},
         {1,0,0,1},
         {1,0,0,1},
         {0,1,1,0}},

        {{1,1,1,1},
         {0,0,0,1},
         {0,0,1,0},
         {0,1,0,0},
         {0,1,0,0},
         {0,1,0,0}},

        {{0,1,1,0},
         {1,0,0,1},
         {0,1,1,0},
         {1,0,0,1},
         {1,0,0,1},
         {0,1,1,0}},

        {{1,1,1,0},
         {1,0,0,1},
         {1,1,1,0},
         {1,1,0,0},
         {1,0,1,0},
         {1,0,0,1}},

        {{1,0,0,1},
         {1,1,0,1},
         {1,0,1,1},
         {1,0,0,1},
         {1,0,0,1},
         {1,0,0,1}},
    };

  byte _barGraphNumber ;
  byte _barGraphTab[8] = {2,2,2,2,6,6,4,4} ; 
  int _motorSpeed ; 
};

#endif
