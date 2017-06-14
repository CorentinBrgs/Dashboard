/* Matrix.cpp Library for commanding 8*8 RGB Matrix with two 
   MCP23017 controllers
   Created by Corentin BERGES May 20th 2017
*/

//UPDATED : 13/06/2017 12:31

#include <Arduino.h>
#include <Wire.h>
#include <MCP23017.h>
#include "Matrix.h"

Matrix::Matrix(byte addr1, byte addr2, 
               byte portLine, byte portRed, byte portGreen, byte portBlue) 
{
                /* Paramètre sous la forme
                 * Addr MCP0, Addr MCP1
                 * port___ values are 0 to 3 : 
                 * 0 for port A of MCP 0
                 * 1 ---------B--------0
                 * 2----------A--------1
                 * 3----------B--------1
                 */
  _addr1 = addr1 ;
  _addr2 = addr2;
  _portLine[0] = portLine%2;
  _portRed[0] = portRed%2;
  _portGreen[0] = portGreen%2;
  _portBlue[0] = portBlue%2;
  _portLine[1] = portLine>1;
  _portRed[1] = portRed>1;
  _portGreen[1] = portGreen>1;
  _portBlue[1] = portBlue>1;

  _addrLine = (!_portLine[1]) * _addr1 + _portLine[1] * _addr2;
  _addrRed = (!_portRed[1]) * _addr1 + _portRed[1] * _addr2;
  _addrGreen = (!_portGreen[1]) * _addr1 + _portGreen[1] * _addr2;
  _addrBlue = (!_portBlue[1]) * _addr1 + _portBlue[1] * _addr2;

  MCPLine = MCP23017(_addrLine, _portLine[0]);
  MCPRed = MCP23017(_addrRed, _portRed[0]);
  MCPGreen = MCP23017(_addrGreen, _portGreen[0]);
  MCPBlue = MCP23017(_addrBlue, _portBlue[0]);

}


void Matrix::begin() {
  MCPLine.begin();
  MCPRed.begin();
  MCPGreen.begin();
  MCPBlue.begin();
}

void Matrix::writeLine(byte lineMask){
  MCPLine.write(lineMask);
}

void Matrix::writeRed(byte redMask){
  MCPRed.write(~redMask);
}

void Matrix::writeGreen(byte greenMask){
  MCPGreen.write(~greenMask);
}

void Matrix::writeBlue(byte blueMask){
  MCPBlue.write(~blueMask);
}

void Matrix::lineDisp(byte lineNumber){
  byte lineMask = 0 ;
  for (byte color=0; color<3; color++){
    byte mask = 0;
    for(byte i=0;i<8;i++){
      mask += ((_matrixTab[lineNumber][i]&(1<<color))>0)<<i ;
    }
    _colorTab[color] = mask ;
  }
  writeLine(0);
  writeRed(_colorTab[2]/*&(B01010101<<_halfDisp)*/);
  writeGreen(_colorTab[1]/*&(B01010101<<_halfDisp)*/);
  writeBlue(_colorTab[0]/*&(B01010101<<_halfDisp)*/);
  writeLine(1<<lineNumber);
}

void Matrix::disp() {
  for(byte i=0; i<8; i++) {
    /*if ((i%3)==0){
      lineDisp(0);
    }*/
    lineDisp(i);
    delayMicroseconds(50);
  }
  //_halfDisp = (_halfDisp+1)%2;

}

void Matrix::input(byte matrixTab[8][8]) {
  for (byte i=0;i<8;i++) {
    for (byte j=0;j<8;j++) { 
      _matrixTab[i][j] = matrixTab[i][j];
  
    }
  }
}

void Matrix::gearDisp(byte gear, byte color) {
  if (_gear != gear || color != _gearColor){
    _gear = gear;
    for(byte i=0;i<6;i++){
      for (byte j=0;j<4;j++){
        _matrixTab[i+2][j+1] = color * _gearTab[_gear][i][j];
      }
    }
  }
}

void Matrix::flagDisp(bool yellowFlag, bool blueFlag, bool whiteFlag) {
  for(byte i=0;i<2;i++) {
    for (byte j=0;j<2;j++){
      _matrixTab[i+4][j+6] = 6 * yellowFlag;
    }
  }
  for(byte i=0;i<2;i++) {
    for (byte j=0;j<2;j++){
      _matrixTab[i+2][j+6] = blueFlag;
    }
  }

  for(byte i=0;i<2;i++) {
    for (byte j=0;j<2;j++){
      _matrixTab[i+6][j+6] = 7*whiteFlag;
    }
  }
}

void Matrix::bargraphDisp(int motorSpeed, int motorSpeedMin, int motorSpeedMax){
  if (_motorSpeed != motorSpeed);
    _barGraphNumber = (motorSpeed>motorSpeedMin) * map(motorSpeed, motorSpeedMin, motorSpeedMax, 0, 8  );
    for(byte i=0;i<8;i++) {
      _matrixTab[0][i] = _barGraphTab[i] * (i<_barGraphNumber);
    }
  }

//void Matrix::input(byte matrixTab[8][8]) {
  
