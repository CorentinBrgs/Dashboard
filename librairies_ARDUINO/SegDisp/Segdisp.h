/* Matrix.h Library for commanding 8*8 RGB Matrix with two 
   MCP23017 controllers
   Created by Corentin BERGES May 20th 2017
*/

#ifndef Segdisp_h
#define Segdisp_h

#include <Arduino.h>
#include <Wire.h>
#include <MCP23017.h>

class Segdisp {
  public :
    Segdisp(byte addr);
    void begin();
    void write(byte nb, bool point); //envoie le masque du chiffre
    void disp(byte digit); //envoie le masque des digits à allumer
    void writedigit(byte nb, byte digit); //affiche "nb" au "digit" sélectionné
    void writedigit(byte nb, bool point, byte digit); //affiche "nb." au "digit" sélectionné si point = 1
    void writeint(int nbint); //affiche le int (<10000) passé en paramètre
    MCP23017 MCPSegDisp;

  private :
    byte _addr;
    byte _portNb = 0;
    byte _portDigit = 1;

    byte _digitTab[20] = 
    {  //a,b,c,d,e,f,g,.
        {B11111100},//0
        {B01100000},//1
        {B11011010},//2
        {B11110010},//3
        {B01100110},//4
        {B10110110},//5
        {B00111110},//6
        {B11100000},//7
        {B11111110},//8
        {B11100110},//9
        {B11111101},//0.
        {B01100001},//1.
        {B11011011},//2.
        {B11110011},//3.
        {B01100111},//4.
        {B10110111},//5.
        {B00111111},//6.
        {B11100001},//7.
        {B11111111},//8.
        {B11100111},//9.

    }
};
#endif
