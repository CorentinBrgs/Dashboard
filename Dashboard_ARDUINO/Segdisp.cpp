/* Segdisp.cpp Library for commanding one 4digits 7segments display with one MCP23017 i2c demux. 
   Created by Corentin BERGES June 14th 2017
*/

#include <Arduino.h>
#include <Wire.h>
#include <MCP23017.h>
#include "Segdisp.h"

Segdisp::Segdisp(byte addr) {
  _addr = addr;
}

void Segdisp::begin() {
  MCPSegDisp = MCP23017(_addr);
  MCPSegDisp.begin();
}

void Segdisp::write(byte nb, bool point) {
  if (point) {
    MCPSegDisp.write(_digitTab[nb+10], _portNb);
  }
  else {
    MCPSegDisp.write(_digitTab[nb], _portNb);
  }
}

void Segdisp::disp(byte digit) {
  MCPSegDisp.write(~(1<<digit), _portDigit);
}

void Segdisp::writedigit(byte nb, bool point, byte digit){ //affiche "nb" au "digit" sélectionné
  clear();
  write(nb, point);
  disp(digit);
}

void Segdisp::writedigit(byte nb, byte digit) { //affiche "nb" au "digit" sélectionné
  writedigit(nb, 0, digit);
}

void Segdisp::writeint(int nbint, bool seg){ //le boolen sert à sélectionner l'afficheur
  byte _digit3 = int(nbint/1000);
  writedigit(_digit3, 3+4*seg);
  //delayMicroseconds(10);
  byte _digit2 = int((nbint%1000)/100);
  writedigit(_digit2, 2+4*seg);
  //delayMicroseconds(10);
  byte _digit1 = int((nbint%100)/10);
  writedigit(_digit1, 1+4*seg);
  //delayMicroseconds(10);
  byte _digit0 = int(nbint%10);
  writedigit(_digit0, 0+4*seg);
  //delayMicroseconds(10);
  MCPSegDisp.write(255, _portDigit);
}

void Segdisp::writeint(int nbint1, int nbint2){
  byte _digit7 = int(nbint2/1000);
  byte _digit6 = int((nbint2%1000)/100);
  byte _digit5 = int((nbint2%100)/10);
  byte _digit4 = int(nbint2%10);
  byte _digit3 = int(nbint1/1000);
  byte _digit2 = int((nbint1%1000)/100);
  byte _digit1 = int((nbint1%100)/10);
  byte _digit0 = int(nbint1%10);

  if (_digit7 != 0) {
    writedigit(_digit7, 7);
  }
  else {
    writedigit(20, 7);
  }

  if (_digit6 + _digit7==0) {
    writedigit(20, 6);
  }
  else {
    writedigit(_digit6, 6);
  }

  if ((_digit5 + _digit6 + _digit7)==0) {
    writedigit(20, 5);
  }
  else {
    writedigit(_digit5, 5);
  }

  if ((_digit4 + _digit5 + _digit2 + _digit3)==0) {
    writedigit(20, 4);
  }
  else {
    writedigit(_digit4, 4);
  }

  if (_digit3 != 0) {
    writedigit(_digit3, 3);
  }
  else {
    writedigit(20, 3);
  }

  if (_digit2 + _digit3==0) {
    writedigit(20, 2);
  }
  else {
    writedigit(_digit2, 2);
  }

  if ((_digit1 + _digit2 + _digit3)==0) {
    writedigit(20, 1);
  }
  else {
    writedigit(_digit1, 1);
  }

  if ((_digit0 + _digit1 + _digit2 + _digit3)==0) {
    writedigit(20, 0);
  }
  else {
    writedigit(_digit0, 0);
  }

  clear();
}


void Segdisp::clear() {
  disp(255); 
}