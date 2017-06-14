/* Dashboard.cpp Library for the Dashboard Project. 
   Created by Corentin BERGES May 20th 2017
*/

#include <Arduino.h>
#include <Wire.h>
#include <MCP23017.h>
#include <Matrix.h>
#include "Segdisp.h"

#include "Dashboard.h"

//si un seul afficheur 4*7 segments
Dashboard::Dashboard(byte addrMatrix1, byte addrMatrix2, 
					byte portLine, byte portRed, byte portGreen, byte portBlue, 
					byte addrSeg) {
	Dashboard(addrMatrix1, addrMatrix2, portLine, portRed, portGreen, portBlue, addrSeg, 0x00);
}

//si deux afficheurs 4*7 segments
Dashboard::Dashboard(byte addrMatrix1, byte addrMatrix2, 
					byte portLine, byte portRed, byte portGreen, byte portBlue, 
					byte addrSeg1, byte addrSeg2) {

	Matrix matrice = Matrix(addrMatrix1, addrMatrix2, 
					portLine, portRed, portGreen, portBlue);
	Segdisp segdisp1 =  Segdisp(addrSeg1);
	Segdisp segdisp2 =  Segdisp(addrSeg2);
}

void Dashboard::begin() {
	matrice.begin();
	Segdisp1.begin();
	Segdisp2.begin();
}

//si un seul afficheur 4*7 segments
void Dashboard::disp(int nbint){
	for(byte i=0; i<8; i++) {
	    lineDisp(i);
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
	    lineDisp(i);
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
void Dashboard::writedigit(byte nb, byte digit){ //affiche "nb" au "digit" sélectionné
	matrice.writedigit(nb, digit);
}
void Dashboard::writedigit(byte nb, bool point, byte digit) { //affiche "nb." au "digit" sélectionné si point = 1
	matrice.writedigit(nb, point, digit);
}

void Dashboard::clear() {
	segdisp1.clear();
	segdisp2.clear();
	matrice.clear();
}