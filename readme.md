# Arduino  air analyser

This is a air analyser programmed with Arduino. It can be used to study air quality.

It measures temperature (°C), pressure (hPa), Humidity (%), CO2 (ppm), volatile organic compounds = VOC and specialy HCHO (µg/m3), and particles PM1 PM2.5 and PM10 (µg/m3).

Data can be,  displayed on LCD screen, displayed on computer screen with a Node-Red dashboard, stored on sd card then displayed on graph with python script.

It uses Seed studio Grove shield to simplify component connection.

![](carte-english.png)

## Connection explanation:
* SD Shield is attached to SPI bus as follows:
    * MOSI - pin 11 on sd shield connected with wire to  pin 51 on  Mega
    * MISO - pin 12 on sd shield connected with wire to  pin 50 on Mega
    * CLK - pin 13 on sd shield connected with wire to  pin 52 on Méga
    * CS  - depends on your SD card shield : pin 10 for mine.
    
* SD shield is attached to I2C bus as follows:
    * sda pin on sd shield connected with jumper to  A4 pin on sd shield
    * scl pin on sd shield connected with jumper to  A5 pin on sd shield
      
* HCHO  sensor on pin 19 (Rx1) on Mega 

* CO2 sensor, lcd display, BME280 sensor and particles sensor are attached to I2C plugs en Grove Shield

* Button is connected to D2 plug on Grove shiled

* LED is connected to D3 plug on Grove shield

## Functions
When the program is starting, you have to make a choice between the three functions of the analyser:
* display sensor values on the LCD screen;
* data logging on sd card;
* send data to Node-Red thrue serial link.

I use an automat like below to make this choice
![](automat.png)
## Node-Red

## Python scripts
 

