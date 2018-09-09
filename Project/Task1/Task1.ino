/*
    Copyright (C) 2018  Amir Raajbifar

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Task1.h"
#define MAX_PROCESSES 3

volatile int flag = LOW;
int counter = 0; // A counter for number of pprocesses

void setup()
{
	pinMode(PUSH2, INPUT_PULLUP); //set the push button 2 as input with the pull up resistor
	pinMode(LED1, OUTPUT);
	attachInterrupt(PUSH2, count, FALLING); //Interrupt id fired whenever button is pressed	
	Serial.begin(9600);
	Serial.println("Initialized");
}

void loop()
{
	if (flag)
	{
		if (counter == MAX_PROCESSES)
		{
			counter = 1;
		}
		else
		{
			counter++;
		}
		flag = LOW;
	}
	#ifdef DEBUG
		Serial.println(counter);
	#endif
	switch (counter) 
	{
	    case 1:
	      // Name -> LCE
	    	#ifdef DEBUG
		    	Serial.print(counter);
		    	Serial.print('\t');
		    	Serial.println("Mode 1");
	    	#endif
	      break;
	    case 2:
	      // Temp -> LCD
	      // Temp (trigger) -> servo
	    	#ifdef DEBUG
		    	Serial.print(counter);
		    	Serial.print('\t');
		    	Serial.println("Mode 2");
	    	#endif
	    	break;
	    case 3:
	      // acce -> LCD
	      // acce -> LEDs
	    	#ifdef DEBUG
		    	Serial.print(counter);
		    	Serial.print('\t');
		    	Serial.println("Mode 3");
	    	#endif
	      break;
	    default:
	      // ERROR
	      break;
	}
}

void count()
{
	static unsigned long last_int_time = 0;
	unsigned long int_time = millis();
	if (int_time - last_int_time > 200)
	{
		flag = HIGH;
	}
	last_int_time = int_time;
}