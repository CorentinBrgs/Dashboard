#include <Matrix.h>
#include <Wire.h>
#include <MCP23017.h>
#include "Dashdata.h"
#include "Segdisp.h"
#include "Dashboard.h"

#define BLUE 1


Dashboard dash(0x20, 0x21, 0, 3, 1, 2, 0x22);  
Dashdata data = Dashdata(); //création de l'objet data ayant pour attribut 
                            //les paramètres envoyés par le jeu, voir Dashdata.h
Segdisp seg1 = Segdisp(0x22);
void setup() {
  dash.begin();
  seg1.begin();
  Serial.begin(115200); //initialisation liaison série à la vitesse de 115200 baud.
                        // Si  besoin de changer changer de même dans /Dashboard_MAIN/Dashboard_main.cpp
}

void loop() {
  data.read();
  dash.bargraphDisp(data.rpm, 6000, data.maxRpm);
  dash.gearDisp(data.gear, BLUE);
  dash.disp(data.carSpeed, data.position);
  data.read();
    //seg1.writeint(data.carSpeed, data.rpm);
}
