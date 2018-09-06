#ifndef Task1_h
#define Task1_h

// Core library - MCU-based
#if defined(__MSP430FR5739__) // FraunchPad only
#include "Energia.h"
#else // error
#error Platform not supported. FraunchPad only.
#endif

// Include application, user and local libraries
#include "FraunchPad_NTC.h"
#include "accelerometer.h"
#include "temprature.h"
#include "lcd.h"
#include "led.h"

#endif