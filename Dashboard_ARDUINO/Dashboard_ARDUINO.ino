#include <Matrix.h>
#include <Wire.h>
#include <MCP23017.h>
#include "Dashdata.h"
#include "Segdisp.h"


#define BLUE 1


Matrix matrice = Matrix(0x20, 0x21, 0, 3, 1, 2);  
Dashdata data = Dashdata(); //création de l'objet data ayant pour attribut 
                            //les paramètres envoyés par le jeu, voir Dashdata.h
Segdisp affich(0x22);
MCP23017 mcp(0x22);
int j=0, k=0;
void setup() {
  matrice.begin(); //initialise la matrice et les démultiplexeurs i2c
  Serial.begin(115200); //initialisation liaison série à la vitesse de 115200 baud.
                        // Si  besoin de changer changer de même dans /Dashboard_MAIN/Dashboard_main.cpp
  affich.begin();
  mcp.begin();
}

void loop() {
  data.read();
  affich.writeint(data.carSpeed);
  matrice.bargraphDisp(data.rpm, 6000, data.maxRpm);
  matrice.gearDisp(data.gear, BLUE);
  matrice.disp();
}
