// Q1.cpp : main project file.

#include "stdafx.h"

#include "conio.h"

using namespace System;


int main()
{
	/////////////////////////////////////////////////////////////////// Q1 ///////////////////////////////////////////////////////////////////////////
    float a, b; // Defining a and b as float
	_cscanf_s("%f", &a); // Reading a from input
    _cscanf_s("%f", &b); // Reading b from input

	float zi1[50], zi2[50], zo1[50]; // Defining 3 arrays for results with lentgh of 50

	float y = 0; // Defining y
	float step = 0.2; // Defining step size

	for(int i = 0; i < sizeof(zi1)/sizeof(*zi1); i++){
		zi1[i] = (y * y) - a; // zi1 = y^2 - a
		zi2[i] = (y * y) + b; // zi2 = y^2 + b
		zo1[i] = 1 / (2 * zi1[i] * zi2[i]); // 1 / (2 * (y^4 + (b - a)y^2 - a * b)
		y += step; // updating y with the step
	}

	for(int i = 0; i < sizeof(zi1)/sizeof(*zi1); i++){
		_cprintf("zi1: %f       zi2: %f       zo1: %f \n",zi1[i] , zi2[i] , zo1[i]); // Printing arrays
	}

	/////////////////////////////////////////////////////////////////// Q2 ///////////////////////////////////////////////////////////////////////////

	float zo2[50]; // Defining zo2 array

	for(int i = 0; i < sizeof(zo2)/sizeof(*zo2); i++){
		zo2[i] =0.5; // in asm code, we divide this number (0.5) by (zi1 * zi2)
	}

	_asm{
		MOV EBX, 0; // SETTING COUNTER = 0
		LOOP_START:
			MOVUPS XMM0 , OWORD PTR zi1[EBX]; // XMM0 = ZI1[EBX]     =>    XMM0 = ZI1[COUNTER]   EACH TIME IT GETS 4 INDEX OF ARRAY AND PUT IT IN XMM0
			MOVUPS XMM1 , OWORD PTR zi2[EBX]; // XMM1 = ZI2[EBX]     =>    XMM1 = ZI2[COUNTER]   EACH TIME IT GETS 4 INDEX OF ARRAY AND PUT IT IN XMM1
			MULPS XMM0, XMM1; // XMM0 = XMM0 * XMM1     => XMM = ZI1[COUNTER] * ZI2[COUNTER]
			MOVUPS XMM2, OWORD PTR zo2[EBX]; // XMM2 = ZO2[EBX]      =>    XMM2 = ZO2[COUNTER]   EACH TIME IT GETS 4 INDEX OF ARRAY AND PUT IT IN XMM2
			DIVPS XMM2, XMM0; // XMM2 = XMM2 / XMM0       =>      ZO2[COUNTER] = ZO2[COUNTER] / (ZI1[COUNTER] * ZI2[COUNTER])
			MOVUPS OWORD PTR zo2[EBX] , XMM2; // ZO2[EBX] = XMM2     =>    ZO2[COUNTER] = XMM2
			ADD EBX, 16; // UPDATING THE COUNTER. EACH TIME WE READ 4 FLOAT AND EACH FLOAT IS 4 BYTE, SO WE SHOULF ADD 4*4 BYTE TO COUNTER
			CMP EBX, 208; // AS WE EXPLAINED, WE COPMARE THE COUNTER (50 / 4) * 16 TIMES. WE SHOULD DO THOSE OPERATION FOR ALL ARRAY INDEX
			// AND IN EACH LOOP ITERATION, WE DO THIS FOR 4 ARRAY INDEX. SO WE SHOULD DO THIS CEIL(50 / 4) TIMES. IN EACH ITERATION, WE ADD THE COUNTER BY 16.
			// SO WE HAVE TO SAY STOP THE LOOP ITERATION WHEN THE COUNTER REACHED CEIL(50 / 4) * 16. WITH TOO MANY TRIES AND ERRORS, WE FOUND CMP ONLY WORKS
			// WHEN THE IMMEDIATE NUMBER IS DIVIDABLE BY 16. SO WE PUT 208 IN THAT PLACE.
			JNZ LOOP_START; // CONTINUE THE LOOP IF EBX (COUNTER) IS LESS THAN THE NUMBER WE COMPARED
	}

	for(int i = 0; i < sizeof(zo2)/sizeof(*zo2); i++){
		_cprintf("zo2: %f       zo1: %f\n", zo2[i], zo1[i]); // Printing zo2 and to see if we calculated correctly, zo2 should be equal to zo1
	}
	
	/////////////////////////////////////////////////////////////////// Q3 ///////////////////////////////////////////////////////////////////////////
	
	for(int i = 0; i < sizeof(zi1)/sizeof(*zi1); i++){
		_cprintf("zi1: %f       zi2: %f       zo1: %f       zo2: %f \n",zi1[i] , zi2[i] , zo1[i], zo2[i]); // Printing arrays
	}
}
