/*
  Dashdata.cpp - Library for the Dashboard project. 
  Created by Corentin BERGES, 13-06-2017, France.
*/

#include <Arduino.h>
#include <Wire.h>
#include "Dashdata.h"

#define DUREE 20

Dashdata::Dashdata() {
  _temps = millis();
}

int Dashdata::read() {
	while (Serial.available()>0/* && (millis()-_temps<DUREE)*/) { 
    /*Serial.print("//_currentChar : ");
    Serial.println(_currentChar);
    Serial.print("//_currentNb : ");
    Serial.println(_currentNb);
    Serial.print("//_charCounter : ");
    Serial.println(_charCounter);*/
    
		_currentChar = Serial.read();
		if (_currentChar == char('/')){
			_dataBegin = true;
			_dataCounter = 0;
			_charCounter = 0;
			_currentNb = 0;  

		}
		else if ((_currentChar == char(';')) || (_currentChar == char(','))){
  		if (_dataBegin) {	
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
  					if (_currentNb>0) { //a  verifier en fonction de l'entier utuilise pour la marche arriere
  						this->gear = _currentNb;
  					}
  					break;
  				//parametres a ajouter si besoin 
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
		  }
			if (_currentChar == char(';')) {
        _dataBegin = false;
        return 1;
      }
			_currentNb = 0;
			_dataCounter ++;
		}
		else {
			_currentNb = 10*_currentNb + _currentChar -48 ;
			_charCounter++;
		}
	}
  //_temps = millis(); 
}

void Dashdata::write(int v1, int v2){
	Serial.print(v1);
	Serial.print(v2);
}

