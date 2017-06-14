/*
  MCP23017.cpp - Library for simple command of up to two MCP23017 as output extenders.
  Created by Corentin BERGES, 19-05-2017, France.
  Released into the public domain.
*/

#include <Arduino.h>
#include "MCP23017.h"
#include <Wire.h>

MCP23017::MCP23017() {
  
}

MCP23017::MCP23017(byte addr){
  _addr = addr;
}

MCP23017::MCP23017(byte addr, byte port){
  _addr = addr;
  _port = 0x13 * port + (!port)*0x12;
}

void MCP23017::begin(){
  Wire.begin();
  Wire.beginTransmission(_addr);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission(_addr);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00);  // set all of port B to outputs
  Wire.endTransmission();
}

void MCP23017::write(byte value, bool port){
  switch (port){
    case 0 :
      Wire.beginTransmission(_addr);
      Wire.write(0x12); // address port A
      Wire.write(value); // value to send
      Wire.endTransmission();
      break;
    case 1 :   
      Wire.beginTransmission(_addr);
      Wire.write(0x13); // address port B 
      Wire.write(value); // value to send
      Wire.endTransmission();  
    break;
  }
}

void MCP23017::write(byte value){
  Wire.beginTransmission(_addr);
  Wire.write(_port);
  Wire.write(value);
  Wire.endTransmission();
}