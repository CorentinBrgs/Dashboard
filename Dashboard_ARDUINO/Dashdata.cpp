/*
  DashboardData.cpp - Library for the Dashboard project. 
  Created by Corentin BERGES, 13-06-2017, France.
*/

#include <Arduino.h>
#include <Wire.h>
#include "Dashdata.h"

Dashdata::Dashdata() {
	_dataBegin = false;
	_dataCounter = 0;
	_charCounter = 0;
	_currentNb = 0;

}

void Dashdata::read() {
	while (Serial.available()>0) {
		_currentChar = Serial.read();
		if (_currentChar == char('/')){
			_dataBegin = true;
			_dataCounter = 0;
			_charCounter = 0;
			_currentNb = 0;
		}
		else if (_currentChar == char(';')){
			_dataBegin = false;
			break;
		}
		else if (_dataBegin) {
			if (_currentChar == char(',')) {
				_charCounter = 0;
				switch (_dataCounter) {
					case 0 :
						this->carSpeed = _currentNb;
						break;
					case 1 :
						this->rpm = _currentNb;
						break;
					case 2 : 
						this->maxRpm = _currentNb;
						break;
					case 3 :
						if (_currentNb>0) { //à vérifier en fonction de l'entier utuilisé pour la marche arrière
							this->gear = _currentNb;
						}
						break;
					//paramètres à ajouter si besoin 
					/*case 4 :
						this.  = _currentNb
						break;
					case 5 : 
						this.  = _currentNb
						break;
					case 6 :
						this.  = _currentNb
						break;
					case 7 :
						this.  = _currentNb
						break;
					case 8 : 
						this.  = _currentNb
						break;*/

				}
				_currentNb = 0;
				_dataCounter ++;
			}
			else {
				_currentNb += pow((_currentChar-48), _charCounter);
				_charCounter++;
			}
		} 
	}
}

void Dashdata::write(int v1, int v2){
	Serial.print(v1);
	Serial.print(v2);
}
