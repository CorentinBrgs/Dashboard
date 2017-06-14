/*
  Dashdata.h - Library for the Dashboard project. 
  Created by Corentin BERGES, 13-06-2017, France.
*/

#ifndef Dashdata_h
#define Dashdata_h

#include <Arduino.h>
#include <Wire.h>

class Dashdata {
	public :
		Dashdata();
		int read();
		void write(int v1, int v2);

		int carSpeed = 0;
		int maxRpm = 0;
		int rpm = 0;
		int gear = 0;

	private :
		byte _currentChar = 0;
		int _currentNb = 0;
		bool _dataBegin = 0;
		int _dataCounter = 0;
		int _charCounter = 0;
    	long _temps;
};
#endif

