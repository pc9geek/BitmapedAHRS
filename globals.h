#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include <Wire.h>
#include <I2Cdev.h>                         // note bugfix  for ESP8266 @ https://github.com/me21/i2cdevlib/commit/b634283bd0a806f2b82db1e28ac1c0f23d2ab7fd
#include <TFT_eSPI.h>                       // Hardware-specific TFT library

#include <BMP085.h>                         // https://github.com/jrowberg/i2cdevlib
#include <helper_3dmath.h>                  // https://github.com/jrowberg/i2cdevlib
#include <HMC5883L.h>                       // https://github.com/jrowberg/i2cdevlib

//change the macro definition for the TFT reset from GPIO2 to RST
#ifdef TFT_RST
	#undef TFT_RST
#endif // TFT_RST
#define TFT_RST  -1

//Global vars
word brightness;                // color of foreground text
long duration;                  // Duration used to calculate distance
int16_t RALT;                   // Current Radio Altimeter value
int16_t ALT;                    // Current Scale ALTITUDE
int16_t IAS;                    // Current Scale IAS
uint16_t RPM;
float temperature;              // Ambient Temperature
float pressure;
int32_t altitude;
int16_t HEADING;                // current Heading
float G;
long lastcall;


TFT_eSPI tft = TFT_eSPI();                    // Invoke custom library
BMP085 barometer;                             // Barometer Object
HMC5883L mag;                                 // compass
MPU6050 mpu;                                  // MPU


											  //MPU
int16_t ax, ay, az;
// int16_t gx, gy, gz;
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer


						// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

#endif