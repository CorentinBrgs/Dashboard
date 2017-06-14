/*
  MCP23017.h - Library for simple command of up to two MCP23017 as output extenders.
  Created by Corentin BERGES, 19-05-2017, France.
  Released into the public domain.
*/
#ifndef MCP23017_h
#define MCP23017_h

#include <Arduino.h>
#include <Wire.h>

class MCP23017{
  public :
    MCP23017();
    MCP23017(byte addr);
    MCP23017(byte addr, byte port);
    void begin(void);
   // void pinMode();
    void write(byte value, bool port);
    void write(byte value);
    byte _addr;
    byte _port;
  private :
    
};
#endif 
