/* Matrix.h Library for commanding 8*8 RGB Matrix with two 
   MCP23017 controllers
   Created by Corentin BERGES May 20th 2017
*/

#ifndef Segdisp_h
#define Segdisp_h

#include <Arduino.h>
#include <Wire.h>
#include <MCP23017.h>

class Segdisp{
  public :
    Segdisp(byte addr);
    void begin(void);
    void write(byte nb, bool point); //envoie le masque du chiffre
    void disp(byte digit); //envoie le masque des digits à allumer
    void writedigit(byte nb, byte digit); //affiche "nb" au "digit" sélectionné
    void writedigit(byte nb, bool point, byte digit); //affiche "nb." au "digit" sélectionné si point = 1
    void writeint(int nbint); //affiche le int (<10000) passé en paramètre
    MCP23017 MCPSegDisp = MCP23017(_addr);

  private :
    byte _addr;
    byte _portNb = 0;
    byte _portDigit = 1;

    byte _digitTab[20] = 
    {  //a,b,c,d,e,f,g,.
        {B00111111},//0
        {B00000110},//1
        {B01011011},//2
        {B01001111},//3
        {B01100110},//4
        {B01101101},//5
        {B01111101},//6
        {B00000111},//7
        {B01111111},//8
        {B01101111},//9
        {B10111111},//0.
        {B10000110},//1.
        {B11011101},//2.
        {B11001111},//3.
        {B11100110},//4.
        {B11101101},//5.
        {B11111101},//6.
        {B10000111},//7.
        {B11111111},//8.
        {B11101111}//9.
    };
};

#endif
