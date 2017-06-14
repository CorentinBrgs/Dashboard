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
		//si un seul afficheur 4*7 segments
		Dashboard(byte addrMatrix1, byte addrMatrix2, 
					byte portLine, byte portRed, byte portGreen, byte portBlue, 
					byte addrSeg);

		//si deux afficheurs 4*7 segments
		Dashboard(byte addrMatrix1, byte addrMatrix2, 
					byte portLine, byte portRed, byte portGreen, byte portBlue, 
					byte addrSeg1, byte addrSeg2);

		void begin();
		void disp();
		void clear();

		void gearDisp(byte gear, byte color);
	    void flagDisp(bool yellowFlag, bool blueFlag, bool whiteFlag);
	    void bargraphDisp(int motorSpeed, int morotSpeedMin, int motorSpeedMax);

	    void writedigit(byte nb, byte digit); //affiche "nb" au "digit" sélectionné
	    void writedigit(byte nb, bool point, byte digit); //affiche "nb." au "digit" sélectionné si point = 1
	    void writeint(int nbint); //affiche le int (<10000) passé en paramètre

		Matrix matrice = Matrix(addrMatrix1, addrMatrix2, portLine, portRed, portGreen, portBlue);
		Segdisp segdisp1 =  Segdisp(addrSeg1);
		Segdisp segdisp2 =  Segdisp(addrSeg2);

	private :
};


#endif
