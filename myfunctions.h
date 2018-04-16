#pragma once

#include <TFT_eSPI.h>                       // Hardware-specific TFT library
#define PIC_WIDTH 100
#define PIC_HEIGHT 100
unsigned short buff[10000];
unsigned short pdial[10000];



void makeDial(float pitch) {
	
	//2 deg = 1 pixel 10,20,30,40 etc
	//draw horizon 2px
	float degPitch = pitch * RAD_TO_DEG;
	float lubber;
	int i, j;
	int posn;
	if (degPitch > 180) {
		lubber = 50 + (360 - degPitch);
	}
	else {
		lubber = 50 - degPitch;
	}

	// horizon was 50 will now be 50+pitch/2
	for (i = 0; i < lubber; i++) {
		for (j = 0; j < PIC_HEIGHT; j++) {
			posn = i * PIC_WIDTH + j;
			pdial[posn] = 0x79C2;
		}
	}
	for (i = lubber; i < PIC_HEIGHT; i++) {
		for (j = 0; j < PIC_HEIGHT; j++) {
			posn = i * PIC_WIDTH + j;
			pdial[posn] = 0x4CDF;
		}
	}
	for (i = lubber; i>15; i-=15) {
		for (j =43; j < 57; j++) {
			posn = i * PIC_WIDTH + j;
			pdial[posn] = 0xFFFF;
			pdial[posn + PIC_WIDTH] = 0xFFFF;
		}
	}
	for (i = lubber; i<75; i += 15) {
		for (j = 43; j < 57; j++) {
			posn = i * PIC_WIDTH + j;
			pdial[posn] = 0xFFFF;
			pdial[posn + PIC_WIDTH] = 0xFFFF;
		}
	}
	
	posn = 0;
	if (lubber > 0 && lubber < 99) {
		for (i = lubber; i < lubber + 1; i++) {
			for (j = 0; j < PIC_HEIGHT; j++) {
				posn = i * PIC_WIDTH + j;
				pdial[posn] = 0xFFFF;
			}
		}
	}

}
/*
	Rotate an image through an arbitary amount, rotation is centered 
*/
void rotateAH(TFT_eSPI *tft, const unsigned short* mask,  int16_t x, int16_t y, uint16_t width, uint16_t height, float angle,  float pitch) {
	float midX, midY;
	float deltaX, deltaY;
	int rotX, rotY;
	int i, j;
	midX = PIC_WIDTH / 2.0f;
	midY = PIC_HEIGHT / 2.0f;
	float sa = sin(angle);
	float ca = cos(angle);
	// pitch the dial
	makeDial(pitch);
	tft->setAddrWindow(x, y, x + width - 1, y + height - 1);
	for (i = 0; i < PIC_WIDTH; i++) {
		for (j = 0; j < PIC_HEIGHT; j++) {
			int posn = j * PIC_WIDTH + i;
			//buff[(i * PIC_WIDTH + j)] = pgm_read_word(&icon[(i * PIC_WIDTH + j)]);
			if (pgm_read_word(&mask[posn]) == TFT_TRANSPARENT) {
				deltaX = i - midX;
				deltaY = j - midY;
				rotX = (int)(midX + deltaX * sa - deltaY * ca);
				rotY = (int)(midY + deltaX * ca + deltaY * sa);
				if (rotX >= 0 && rotX < PIC_WIDTH && rotY >= 0 && rotY < PIC_HEIGHT) {
					//buff[posn] = pgm_read_word(&dial[(rotX * PIC_WIDTH + rotY)]);
					buff[posn] = pdial[(rotX * PIC_WIDTH + rotY)];
				}
			}else {
				buff[posn] = pgm_read_word(&mask[posn]);
			}
		}
	}
	if (y + height > 128) {
		tft->pushColors(buff, 100 * (128-y));
	}
	else {
		tft->pushColors(buff, 100 * 100);
	}
	
}


void rotateImage(TFT_eSPI *tft, const unsigned short* icon, int16_t x, int16_t y, uint16_t width, uint16_t height, float angle) {
	float midX, midY;
	float deltaX, deltaY;
	int rotX, rotY;
	int i, j;

	midX = PIC_WIDTH / 2.0f;
	midY = PIC_HEIGHT / 2.0f;
	float sa = sin(angle);
	float ca = cos(angle);

	tft->setAddrWindow(x, y, x + width - 1, y + height - 1);
	for (i = 0; i < PIC_WIDTH; i++){
		for (j = 0; j < PIC_HEIGHT; j++) {			
			//buff[(i * PIC_WIDTH + j)] = pgm_read_word(&icon[(i * PIC_WIDTH + j)]);
			
			deltaX = i - midX;
			deltaY = j - midY;
			
			rotX = (int)(midX + deltaX * sa + deltaY * ca);
			rotY = (int)(midY + deltaX * ca - deltaY * sa);
			if (rotX >= 0 && rotX < PIC_WIDTH && rotY >= 0 && rotY < PIC_HEIGHT) {
				buff[(j * PIC_WIDTH + i)] = pgm_read_word(&icon[(rotX * PIC_WIDTH + rotY)]);
				/*
				&bufPic[(j * PIC_WIDTH + i) * 3] = &pic[(rotX * PIC_WIDTH + rotY) * 3];
				&bufPic[(j * PIC_WIDTH + i) * 3 + 1] = &pic[(rotX * PIC_WIDTH + rotY) * 3 + 1];
				&bufPic[(j * PIC_WIDTH + i) * 3 + 2] = &pic[(rotX * PIC_WIDTH + rotY) * 3 + 2];
				*/
			}
		}
	}
	tft->pushColors(buff, 100*100);
}

// this is replacement roll pitch yaw calculator that returns 0 to 360 degrees
int myGetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity) {
	// yaw: (about Z axis)
	data[0] = atan2(2 * q->x*q->y - 2 * q->w*q->z, 2 * q->w*q->w + 2 * q->x*q->x - 1);

	// pitch: (nose up/down, about Y axis)
	float temp = atan(gravity->z / gravity->x);
	if (gravity->z < 0) {
		if (gravity->x >= 0)
			data[1] = HALF_PI - temp; //quadrant 2
		else
			data[1] = TWO_PI - HALF_PI - temp; //quadrant 3
	}
	else if (gravity->x >= 0)
		data[1] = HALF_PI - temp; //quadrant 1
	else
		data[1] = TWO_PI - HALF_PI - temp; //quadrant 4

	// roll: (tilt left/right, about X axis)
	temp = atan(gravity->z / gravity->y);
	if (gravity->y < 0) {
		if (gravity->z >= 0)
			data[2] = HALF_PI + temp; //quadrant 1
		else
			data[2] = HALF_PI + temp; //quadrant 2
	}
	else if (gravity->z >= 0)
		data[2] = TWO_PI - HALF_PI + temp; //quadrant 4
	else
		data[2] = TWO_PI - HALF_PI + temp; //quadrant 3
	return 0;
}