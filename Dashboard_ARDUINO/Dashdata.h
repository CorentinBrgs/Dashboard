/*
  DashboardData.h - Library for the Dashboard project. 
  Created by Corentin BERGES, 13-06-2017, France.
*/

#ifndef Dashdata_h
#define Dashdata_h

#include <Arduino.h>
#include <Wire.h>

class Dashdata {
	public :
		Dashdata();
		void read();
		void write(int v1, int v2);

		int carSpeed;
		int maxRpm;
		int rpm;
		int gear;

	private :
		char _currentChar;
		int _currentNb;
		bool _dataBegin;
		int _dataCounter;
		char _charCounter;
};
#endif
