//
// FraunchPad_NTC.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project FRAM_TEMP
//
// Created by Rei Vilo, Oct 08, 2012
// http://embedxcode.weebly.com
//
//
// Copyright © Rei Vilo, 2012
// Licence CC = BY NC SA
//
// See FraunchPad_NTC.h and ReadMe.txt for references
//


#include "FraunchPad_NTC.h"

#define getRef(i) (((i) - 5) * 5)

//
// Table generated with TDK / Epcos NTC R/T Calculation 5.0
// http://www.epcos.com/designtools/ntc/index.html
// Select B57560G1104 for NTC 100 k = 25 oC
// with temperature scaling = 5 oC, lower limit = -25 oC and upper limit = + 75 oC
//

/*
int32_t table[21][2] = {
  {-25, 1344300},
  {-20,  998530},
  {-15,  748670},
  {-10,  566360},
  { -5,  432120},
  {  0,  332400},
  {  5,  257690},
  { 10,  201270},
  { 15,  158340},
  { 20,  125420},
  { 25,  100000},
  { 30,   80239},
  { 35,   64776},
  { 40,   52598},
  { 45,   42950},
  { 50,   35262},
  { 55,   29100},
  { 60,   24136},
  { 65,   20114},
  { 70,   16841},
  { 75,   14164}
};
*/

int table[21] = {
  1344300,
   998530,
   748670,
   566360,
   432120,
   332400,
   257690,
   201270,
   158340,
   125420,
   100000,
    80239,
    64776,
    52598,
    42950,
    35262,
    29100,
    24136,
    20114,
    16841,
    14164
};



// Class
//
NTC_FR::NTC_FR() {
  pinMode(NTC_ENABLE, OUTPUT);
  pinMode(A1, INPUT);
}


void NTC_FR::begin() {
  digitalWrite(NTC_ENABLE, HIGH);
  
  _vRef = 3000; // 3000 mV
  _rDiv = 470000000; // 
}


String NTC_FR::WhoAmI() {
  return "FraunchPad NTC thermometer";
}


void NTC_FR::get() {
  _t = analogRead(A1);
  _t = (_t * _vRef) / 1024;
  _t = (_t * _rDiv) / (_vRef - _t) / 1000;
}

/*
void NTC_FR::celsiusX10(int32_t &t) {
  t = 9999;
  
  //
  // Based on table algorithm by larsie — Tue Apr 03, 2012 1:18 pm
  // http://www.43oh.com/forum/viewtopic.php?f=10&p=18608#p18608
  //
  for (uint8_t i=1; i<21; i++) {
    if (table[i][1] < _t) {
      t = map(_t, table[i-1][1], table[i][1], 100*table[i-1][0], 100*table[i][0]);
      t /= 10;
      break;
    }
  }
}
*/

void NTC_FR::celsiusX10(int32_t &t) {
  int i;
  t = 9999;

  //
  // Based on table algorithm by larsie — Tue Apr 03, 2012 1:18 pm
  // http://www.43oh.com/forum/viewtopic.php?f=10&p=18608#p18608
  //
  for (i=1; i<21; i++) {
    if (table[i] < _t) {
      t = map(_t, table[i-1], table[i], 100*getRef(i-1), 100*getRef(i));
      t /= 10;
      break;
    }
  }
}

/*
void NTC_FR::fahrenheitX10(int32_t &t) {
  t = 9999;
  
  //
  // Based on table algorithm by larsie — Tue Apr 03, 2012 1:18 pm
  // http://www.43oh.com/forum/viewtopic.php?f=10&p=18608#p18608
  //
  for (uint8_t i=1; i<21; i++) {
    if (table[i][1] < _t) {
      t = map(_t, table[i-1][1], table[i][1], 100*table[i-1][0], 100*table[i][0]);
      t = (t*9 + 1600) / 50;
      break;
    }
  }
}
*/

void NTC_FR::fahrenheitX10(int32_t &t) {
  int i;
  t = 9999;

  //
  // Based on table algorithm by larsie — Tue Apr 03, 2012 1:18 pm
  // http://www.43oh.com/forum/viewtopic.php?f=10&p=18608#p18608
  //
  for (int i=1; i<21; i++) {
    if (table[i] < _t) {
      t = map(_t, table[i-1], table[i], 100*getRef(i-1), 100*getRef(i));
      t = (t*9 + 1600) / 50;
      break;
    }
  }
}

void NTC_FR::serialPrint(int32_t i, char c)
{
  if (i<0)
  {
    Serial.print("-");
    i = -i;
  }
  Serial.print(i/10, DEC);
  Serial.print(".");
  Serial.print(i%10, DEC);
  if (c == 'C')
  {
    Serial.print(" oC\n");
  }
  else if (c == 'F')
  {
    Serial.print(" oF\n");
  } 
}

void NTC_FR::lcdPrint(int32_t i, LiquidCrystal_I2C x, char c)
{
  if (c == 'C')
  { 
    x.setCursor(0,0);
    x.print("DEGC: ");
    x.print(i/10);
    x.print(".");
    x.print(i%10);  
  }
  else if (c == 'F')
  {
    x.setCursor(0,1);
    x.print("DEGF: ");
    x.print(i/10);
    x.print(".");
    x.print(i%10); 
  }
}
