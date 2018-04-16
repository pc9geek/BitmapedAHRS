#include "AH.h"

void drawIcon(TFT_eSPI *tft, const unsigned short* icon, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	uint16_t  pix_buffer[BUFF_SIZE];   // Pixel buffer (16 bits per pixel)

									   // Set up a window the right size to stream pixels into
	tft->setAddrWindow(x, y, x + width - 1, y + height - 1);

	// Work out the number whole buffers to send
	uint16_t nb = ((uint16_t)height * width) / BUFF_SIZE;

	// Fill and send "nb" buffers to TFT
	for (int i = 0; i < nb; i++) {
		for (int j = 0; j < BUFF_SIZE; j++) {
			pix_buffer[j] = pgm_read_word(&icon[i * BUFF_SIZE + j]);
		}
		tft->pushColors(pix_buffer, BUFF_SIZE);
	}

	// Work out number of pixels not yet sent
	uint16_t np = ((uint16_t)height * width) % BUFF_SIZE;

	// Send any partial buffer left over
	if (np) {
		for (int i = 0; i < np; i++) pix_buffer[i] = pgm_read_word(&icon[nb * BUFF_SIZE + i]);
		tft->pushColors(pix_buffer, np);
	}
}
