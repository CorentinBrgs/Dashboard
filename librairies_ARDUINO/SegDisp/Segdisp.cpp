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
  /*if (point) {
    MCPSegDisp.write(_digitTab[nb+10], _portNb);
  }
  else {
    MCPSegDisp.write(_digitTab[nb], _portNb);
  }*/
  
  //debug 
  MCPSegDisp.write(B01010101, 0);
  MCPSegDisp.write(B1001, 1);
}

void Segdisp::disp(byte digit) {
  MCPSegDisp.write(~(1<<digit), _portDigit);
}

void Segdisp::writedigit(byte nb, bool point, byte digit){ //affiche "nb" au "digit" sélectionné
  disp(0);
  write(nb, point);
  disp(digit);
}

void Segdisp::writedigit(byte nb, byte digit) { //affiche "nb" au "digit" sélectionné
  writedigit(nb, 0, digit);
}

void Segdisp::writeint(int nbint){

}

