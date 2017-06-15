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
					byte addrSeg1) {
	_addrMatrix1 = addrMatrix1;
	_addrMatrix2 = addrMatrix2;
	_portLine = portLine;
	_portRed = portRed;
	_portGreen = portGreen;
	_portBlue = portBlue;
	_addrSeg1 = addrSeg1;

	matrice = Matrix(_addrMatrix1, _addrMatrix2, _portLine, _portRed, _portGreen, _portBlue);
	segdisp1 =  Segdisp(_addrSeg1);
}

void Dashboard::begin() {
	matrice.begin();
	segdisp1.begin();
}

//si un seul afficheur 4*7 segments
void Dashboard::disp(int nbint, bool numSegDisp){
	byte _digit3 = int(nbint/1000);
	byte _digit2 = int((nbint%1000)/100);
	byte _digit1 = int((nbint%100)/10);
	byte _digit0 = int(nbint%10);
	for(byte i=0; i<8; i++) {
	    matrice.lineDisp(i);
	    switch(i) {
	    	case 0 :
  				if (_digit3 != 0) {
  					segdisp1.writedigit(_digit3, 3+4*numSegDisp);
  				}
  				else {
  					segdisp1.writedigit(20, 3+4*numSegDisp);
  				}
	    		break;
	    	case 2 :
	    		if (_digit2 + _digit3==0) {
  					segdisp1.writedigit(20, 2+4*numSegDisp);
	    		}
	    		else {
  					segdisp1.writedigit(_digit2, 2+4*numSegDisp);
	    		}
	    		break;
	    	case 4 :
	    		if ((_digit1 + _digit2 + _digit3)==0) {
	    			segdisp1.writedigit(20, 2+4*numSegDisp);
	    		}
	    		else {
	  				segdisp1.writedigit(_digit1, 1+4*numSegDisp);
	    		}
	    		break;
	    	case 6 :
	    		if ((_digit0 + _digit1 + _digit2 + _digit3)==0) {
	    			segdisp1.writedigit(20, 0+4*numSegDisp);
	    		}
	    		else {
	  				segdisp1.writedigit(_digit0, 0+4*numSegDisp);
	    		}
	    		break;
	    }
	}
	matrice.clear();
	segdisp1.clear();
}

//si deux afficheurs 4*7 segments
void Dashboard::disp(int nbint1, int nbint2){
	
	byte _digit7 = int(nbint2/1000);
    byte _digit6 = int((nbint2%1000)/100);
	byte _digit5 = int((nbint2%100)/10);
	byte _digit4 = int(nbint2%10);
	byte _digit3 = int(nbint1/1000);
	byte _digit2 = int((nbint1%1000)/100);
	byte _digit1 = int((nbint1%100)/10);
	byte _digit0 = int(nbint1%10);

	for(byte i=0; i<8; i++) {
	    matrice.lineDisp(i);
	    switch(i) {
	    	case 0 :
				if (_digit7 != 0) {
					segdisp1.writedigit(_digit7, 7);
				}
				else {
					segdisp1.writedigit(20, 7);
				}
			break;
	    	case 1 :
	    		if (_digit6 + _digit7==0) {
						segdisp1.writedigit(20, 6);
	    		}
	    		else {
						segdisp1.writedigit(_digit6, 6);
	    		}
	    		break;
	    	case 2 :
	    		if ((_digit5 + _digit6 + _digit7)==0) {
	    			segdisp1.writedigit(20, 5);
	    		}
	    		else {
	  				segdisp1.writedigit(_digit5, 5);
	    		}
	    		break;
	    	case 3 :
	    		if ((_digit4 + _digit5 + _digit2 + _digit3)==0) {
	    			segdisp1.writedigit(20, 4);
	    		}
	    		else {
	  				segdisp1.writedigit(_digit4, 4);
	    		}
	    		break;
	    	case 4 :
				if (_digit3 != 0) {
					segdisp1.writedigit(_digit3, 3);
				}
				else {
					segdisp1.writedigit(20, 3);
				}
	    		break;
	    	case 5 :
	    		if (_digit2 + _digit3==0) {
						segdisp1.writedigit(20, 2);
	    		}
	    		else {
						segdisp1.writedigit(_digit2, 2);
	    		}
	    		break;
	    	case 6 :
	    		if ((_digit1 + _digit2 + _digit3)==0) {
	    			segdisp1.writedigit(20, 1);
	    		}
	    		else {
	  				segdisp1.writedigit(_digit1, 1);
	    		}
	    		break;
	    	case 7 :
	    		if ((_digit0 + _digit1 + _digit2 + _digit3)==0) {
	    			segdisp1.writedigit(20, 0);
	    		}
	    		else {
	  				segdisp1.writedigit(_digit0, 0);
	  				delay(1);
	    		}
	    		break;
	    }
	}
	matrice.clear();
	segdisp1.clear();
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
	    segdisp1.writedigit(nb, digit+seg*4);
		}
  	else {
    	segdisp1.writedigit(nb, digit);
  	}
}
void Dashboard::writedigit(byte nb, bool point, byte digit, bool seg) { //affiche "nb." au "digit" sélectionné si point = 1
	if (seg){
	    segdisp1.writedigit(nb, point, digit+seg*4);
		}
  	else {
    	segdisp1.writedigit(nb, point, digit);
  	}
}
void Dashboard::clear() {
	segdisp1.clear();
	matrice.clear();
}