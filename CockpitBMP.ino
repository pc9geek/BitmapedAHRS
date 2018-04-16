#include <MPU6050_9Axis_MotionApps41.h>
//#include <MPU6050_6Axis_MotionApps20.h>
#include <HMC5883L.h>

#include <MPU6050.h>
#include <helper_3dmath.h>
#include <BMP085.h>
#include <I2Cdev.h>
#include <Wire.h>
#include <TFT_eSPI.h>


#include "globals.h"
//#include "AH.h"
#include "ahmask.h"
#include "myfunctions.h"



void setup() {
	Wire.begin(4, 5);

	tft.init();                // initialize a ST7735S chip, black tab
	tft.setRotation(1);
	tft.fillScreen(TFT_BLACK);

	InitMPU();                                 // Start the MPU
	barometer.initialize();                    // Start the Altimter
	IAS = 123;
	tft.fillScreen(0x2104);
	//drawIcon(&tft, ah, 30, 14, 100, 100);

	//create the overlay sprite

	delay(2000);
}

void loop() {
	static long refreshtime;
	static float lasty;

	// test wire master reader
	Wire.requestFrom(9, 32);    // request 6 bytes from slave device #8

	while (Wire.available()) { // slave may send less than requested
		char c = Wire.read(); // receive a byte as character
		Serial.print(c);         // print the character
	}


	//if (millis() > lastcall + 70) {
		ReadMPU();

		
		//lets see if we can rotATE THE ah IN MEMORY!
		//rotateImage(ypr[2] / DEG2RAD);
//		rotateImage(&tft,insert,30,14,100,100, ypr[2] );
		//skip if value differs by more that 10%
		
		rotateAH(&tft, ahmask, 30, 50, 100, 100, ypr[2],ypr[1]);

		// UpdateSensors();                          // update the sensor values
		//DisplayData();                            // display the screen
		// UpdateAH(&tft, ypr[2] / DEG2RAD, 0 - (ypr[1] / DEG2RAD));
		// tft.setTextSize(1);
		//tft.setFont(&FreeSans18pt7b);
		//tft.setFont();
		tft.setCursor(0, 10);
		tft.fillRect(0, 10, 128, 30, ST7735_BLACK);
		tft.print("Time:"); tft.print(" "); tft.print(millis() - lastcall); tft.println(" ");
		//tft.print("Pitch:"); tft.print(" "); tft.print(ypr[1]); tft.println(" ");
		tft.print("Pitch:"); tft.print(" "); tft.print(ypr[1]* RAD_TO_DEG); tft.println(" ");
		tft.print("Roll:"); tft.print(" "); tft.print(ypr[2] * RAD_TO_DEG); tft.println(" ");
		lastcall = millis();
		//tft.setFont(&FreeSans12pt7b);
	//}
}


void InitMPU() {

	Serial.println(F("Initializing DMP..."));
	mpu.initialize();
	Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
	devStatus = mpu.dmpInitialize();
	/*
	mpu.setXAccelOffset(1451);
	mpu.setYAccelOffset(-1003);
	mpu.setZAccelOffset(3891);
	mpu.setXGyroOffset(89);
	mpu.setYGyroOffset(-10);
	mpu.setZGyroOffset(-16);
	*/
	mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		Serial.println(F("Enabling DMP..."));
		mpu.setDMPEnabled(true);
	}
	else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		Serial.print(F("DMP Initialization failed (code "));
		Serial.print(devStatus);
		Serial.println(F(")"));
	}
	packetSize = mpu.dmpGetFIFOPacketSize();

	///////////////////
}
void ReadMPU() {
	mpu.resetFIFO();
	fifoCount = 0;
	while (fifoCount < packetSize) {
		fifoCount = mpu.getFIFOCount();
	}
	if (fifoCount == 1024) mpu.resetFIFO();
	else {
		fifoCount = mpu.getFIFOCount();
		mpu.getFIFOBytes(fifoBuffer, packetSize);                               // read a packet from FIFO
		mpu.resetFIFO();
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		//mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);	
		myGetYawPitchRoll(ypr, &q, &gravity);									// 
	}
}




float getG() {
	float x = mpu.getAccelerationX() / 4096.0;
	float y = mpu.getAccelerationY() / 4096.0;
	float z = mpu.getAccelerationZ() / 4096.0;
	return (sqrt(x * x + y * y + z * z));
}