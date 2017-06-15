/* Dashboard.cpp Library for the Dashboard Project. 
   Created by Corentin BERGES May 20th 2017
*/

#include <Arduino.h>
#include <Wire.h>
#include <MCP23017.h>
#include <Matrix.h>
#include "Segdisp.h"

#include "Dashboard.h"

Dashboard::Dashboard(byte addrMatrix1, byte addrMatrix2, 
					byte portLine, byte portRed, byte portGreen, byte portBlue, 
					byte addrSeg1, byte addrSeg2) {
	_addrMatrix1 = addrMatrix1;
	_addrMatrix2 = addrMatrix2;
	_portLine = portLine;
	_portRed = portRed;
	_portGreen = portGreen;
	_portBlue = portBlue;
	_addrSeg1 = addrSeg1;
	_addrSeg2 = addrSeg2;

	matrice = Matrix(_addrMatrix1, _addrMatrix2, _portLine, _portRed, _portGreen, _portBlue);
	segdisp1 =  Segdisp(_addrSeg1);
	segdisp2 =  Segdisp(_addrSeg2);
}

void Dashboard::begin() {
	matrice.begin();
	segdisp1.begin();
	segdisp2.begin();
}

//si un seul afficheur 4*7 segments
void Dashboard::disp(int nbint){
	for(byte i=0; i<8; i++) {
	    matrice.lineDisp(i);
	    switch(i) {
	    	case 0 :
  				segdisp1.writedigit(int(nbint/1000), 3);
	    		break;
	    	case 2 :
  				segdisp1.writedigit(int((nbint%1000)/100), 2);
	    		break;
	    	case 4 :
				segdisp1.writedigit(int((nbint%100)/10), 1);
	    		break;
	    	case 6 :
  				segdisp1.writedigit(int(nbint%10), 0);
	    		break;
	    }
	}
	matrice.clear();
	segdisp1.clear();
}

//si deux afficheurs 4*7 segments
void Dashboard::disp(int nbint1, int nbint2){
	for(byte i=0; i<8; i++) {
	    matrice.lineDisp(i);
	    switch(i) {
	    	case 0 :
  				segdisp1.writedigit(int(nbint1/1000), 3);
  				segdisp2.writedigit(int(nbint2/1000), 3);
	    		break;
	    	case 2 :
  				segdisp1.writedigit(int((nbint1%1000)/100), 2);
  				segdisp2.writedigit(int((nbint2%1000)/100), 2);
	    		break;
	    	case 4 :
				segdisp1.writedigit(int((nbint1%100)/10), 1);
				segdisp2.writedigit(int((nbint2%100)/10), 1);
	    		break;
	    	case 6 :
  				segdisp1.writedigit(int(nbint1%10), 0);
  				segdisp2.writedigit(int(nbint2%10), 0);
	    		break;
	    }
	}
	matrice.clear();
	segdisp1.clear();
	segdisp2.clear();
}

void Dashboard::gearDisp(byte gear, byte color){
	matrice.gearDisp(gear, color);
}
void Dashboard::flagDisp(bool yellowFlag, bool blueFlag, bool whiteFlag){
	matrice.flagDisp(yellowFlag, blueFlag, whiteFlag);
}
void Dashboard::bargraphDisp(int motorSpeed, int morotSpeedMin, int motorSpeedMax){
	matrice.bargraphDisp(motorSpeed, morotSpeedMin, motorSpeedMax);
}


void Dashboard::writedigit(byte nb, byte digit, bool seg){ //affiche "nb" au "digit" sélectionné
	if (seg){
	    segdisp2.writedigit(nb, digit);
		}
  	else {
    	segdisp1.writedigit(nb, digit);
  	}
}
void Dashboard::writedigit(byte nb, bool point, byte digit, bool seg) { //affiche "nb." au "digit" sélectionné si point = 1
	if (seg){
	    segdisp2.writedigit(nb, point, digit);
		}
  	else {
    	segdisp1.writedigit(nb, point, digit);
  	}
}
void Dashboard::clear() {
	segdisp1.clear();
	segdisp2.clear();
	matrice.clear();
}