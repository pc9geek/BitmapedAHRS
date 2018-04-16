#pragma once
/*

COMPONENTS
ARDUINO NANO           http://www.pighixxx.com/test/pinouts/boards/nano.pdf
TFT + SD               https://www.youtube.com/watch?v=boagCpb6DgY
SONAR                  https://www.robotics.org.za/HC-SR04
GY-86(10DOF)           https://www.banggood.com/GY-86-10DOF-MS5611-HMC5883L-MPU6050-Module-MWC-Flight-Control-Sensor-Module-p-1172532.html?rmmds=search&cur_warehouse=CN
GPS                    https://www.aliexpress.com/item/2pcs-lot-GY-NEO6MV2-new-GPS-module-with-Flight-Control-Flight-Control-EEPROM-MWC-APM2-5/1811853522.html?spm=a2g0s.9042311.0.0.oW5cxn
AIRSPEED(MPXV7002DP)   https://www.openimpulse.com/blog/products-page/product-category/mpxv7002dp-pressure-sensor-module/
30A CURRENT SENSOR     https://www.banggood.com/1PC-30A-New-Range-Current-Sensor-Module-for-ACS712-p-86583.html


					Wiring
									+-----+
						+------------| USB |------------+
						|            +-----+            |
			TFT 3.3V    | [ ]3.3V               VIN [ ] |
						| [ ]GND                GND [ ]~|
						| [ ]TX-GPIO1           RST [ ]~|
						| [ ]RX-GPIO3            EN [ ]~|
			TFT CS      | [ ]D8-GPIO15         3.3V [ ] |
			TFT MOSI    | [ ]D7-GPIO13          GND [ ] |
						| [ ]D6-GPIO12          CLK [ ]~|
			TFT SCK     | [ ]D5-GPIO14          SDO [ ]~|
			TFT GND     | [ ]GND                CMD [ ] |
						| [ ]3.3V               SD1 [ ]~|
			TFT RESET   | [ ]D4-GPIO2    GPIO9 -SD2 [ ] |
			TFT DC      | [ ]D3-GPIO0    GPIO10-SD3 [ ] |
			mpu SDA     | [ ]D2-GPIO4           RSV [ ] |
			MPU SCL     | [ ]D1-GPIO5           RSV [ ] |
						| [ ]D0-GPIO16           AO [ ] |
						|                               |
						|                               |
						|                               |
						+-------------------------------+

https://mmc.bolha.com/0/image/201505/203823/ESP2866-ESP01-ESP03-ESP12-Wemos-NodeMcu-wifi-mikrokontroler_580457f994290.jpg

Display SDO/MISO  to NodeMCU pin D6 (or leave disconnected if not reading TFT)

https://github.com/Bodmer/TFT_eSPI

// Display LED       to NodeMCU pin VIN (or 5V, see below)
// Display SCK       to NodeMCU pin D5
// Display SDI/MOSI  to NodeMCU pin D7
// Display DC (RS/AO)to NodeMCU pin D3
// Display RESET     to NodeMCU pin D4 (or RST, see below) * #define TFT_RST  -1
// Display CS        to NodeMCU pin D8 (or GND, see below)
// Display GND       to NodeMCU pin GND (0V)
// Display VCC       to NodeMCU 5V or 3.3V


SD CARD
SD_MISO				D6
SD_MOSI				D7	
SD_CS				D0	GPIO16
SD_SCK				

GY87
SDA					D2
SCL					D1

SONAR https://www.14core.com/wiring-esp8266-nodemcu-with-hcsr04-ultrasonic-sensor/
VCC    => 5v
TRIG   ->
ECHO   ->
GND    -> GND

`

GPS
VCC  -> 5V
TX   ->  (RX)
RX   ->  (TX)
GND  -> GND

IAS
GND -> GND
5V  ->  5v
SIG ->  A0



*/