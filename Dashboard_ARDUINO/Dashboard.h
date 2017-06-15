/* Dashboard.h Library for the Dashboard Project. 
   Created by Corentin BERGES May 20th 2017
*/

#ifndef Dashboard_h
#define Dashboard_h

#include <Arduino.h>
#include <Wire.h>
#include <MCP23017.h>
#include <Matrix.h>
#include "Segdisp.h"

class Dashboard{
	public :
		//si deux afficheurs 4*7 segments, si un seul mettre 0 en addresse pour le deuxième
		Dashboard(byte addrMatrix1, byte addrMatrix2, 
					byte portLine, byte portRed, byte portGreen, byte portBlue, 
					byte addrSeg1, byte addrSeg2);

		void begin();
		void disp(int nbint);
		void disp(int nbint1, int nbint2);
		void clear();

		void gearDisp(byte gear, byte color);
	    void flagDisp(bool yellowFlag, bool blueFlag, bool whiteFlag);
	    void bargraphDisp(int motorSpeed, int morotSpeedMin, int motorSpeedMax);

	    void writedigit(byte nb, byte digit, bool seg); //affiche "nb" au "digit" sélectionné
	    void writedigit(byte nb, bool point, byte digit, bool seg); //affiche "nb." au "digit" sélectionné si point = 1
	    void writeint(int nbint); //affiche le int (<10000) passé en paramètre

		Matrix matrice = Matrix(_addrMatrix1, _addrMatrix2, _portLine, _portRed, _portGreen, _portBlue);
		Segdisp segdisp1 =  Segdisp(_addrSeg1);
		Segdisp segdisp2 =  Segdisp(_addrSeg2);

	private :

	byte _addrMatrix1;
	byte _addrMatrix2;
	byte _portLine;
	byte _portRed;
	byte _portGreen; 
	byte _portBlue;	
	byte _addrSeg1; 
	byte _addrSeg2;
};


#endif
