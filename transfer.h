#pragma once
#include <Wire.h>

/*
* This file defines the structure for passing data across the I2c Wire
*/
#define BUFFERSIZE 32  // 32 byte buffer for adding more data later 31 bytes of data available

char CharacterBuffer[BUFFERSIZE];
typedef struct dataStruct {
	int16_t IAS;
	int16_t RALT;
	int16_t RPM;
	int16_t mAMPS;
};
struct dataStruct data;

// this copies a value into a position in the buffer
void fillbuff() {
	size_t structSize = sizeof(dataStruct);
	memcpy(&CharacterBuffer, &data, structSize);
}
void emptybuff() {
	size_t structSize = sizeof(dataStruct);
	memcpy(&data, &CharacterBuffer, structSize);
}
