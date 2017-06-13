#include <Matrix.h>
#include <Wire.h>
#include <MCP23017.h>

Matrix matrice(0x20, 0x21, 0, 3, 1, 2);  
long temps ;
int gear = 0;
int rpm = 0;

void setup() {
  // put your setup code here, to run once:
  matrice.begin();
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()>0) {
    rpm = Serial.read()-48;
    gear = Serial.read()-48;
  }
  matrice.bargraphDisp(rpm,0,9);
  if (gear>0){
      matrice.gearDisp(gear, 1);
  }
  matrice.disp();
//  Serial.print(matrice.MCPLine._addr, HEX);
//  Serial.print(matrice.MCPLine._port, HEX);
//  Serial.println(matrice._portLine[0], HEX);
//  Serial.println(matrice._addrBlue, HEX);
//  delay(1000);
  
}
