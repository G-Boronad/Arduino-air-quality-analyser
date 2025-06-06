# Arduino Air Quality Analyser

![](carte_english.png)

## The Project

This is an air analyser programmed with Arduino. It can be used to study air quality.
It uses an Arduino Mega board and a Seeed Studio Grove shield to simplify component connections.

### Measurements

* Temperature (°C)
* Pressure (hPa)
* Humidity (%)
* CO₂ (ppm)
* Volatile Organic Compounds (VOC), especially Formaldehyde (HCHO) (µg/m³)
* Particulate Matter: PM1, PM2.5, and PM10 (µg/m³)

### Data Can Be

* Displayed on LCD screen
* Displayed on computer screen via a Node-RED dashboard
* Stored on SD card and visualized as graphs using a Python script

## Sensor Connections

* Grove shield is plugged into the Mega board. Then, the SD shield is plugged into the Grove shield.

* SD shield is connected to the SPI bus as follows:

  * **MOSI** — pin 11 on  SD shield connected to pin 51 on the Mega
  * **MISO** — pin 12 on  SD shield connected to pin 50 on the Mega
  * **CLK** — pin 13 on SD shield connected to pin 52 on the Mega
  * **CS** — depends on your SD shield (pin 10 for mine)

* **SD shield** is also connected to the I2C bus for the RTC module:

  * SDA pin on SD shield is connected via jumper to A4 on the SD shield
  * SCL pin on SD shield is connected via jumper to A5 on the SD shield

* **HCHO sensor** is connected to pin 19 (Rx1) on the Mega

* **CO₂ sensor**, **LCD display**, **BME280 sensor**, and **particle sensor** are connected to I2C ports on the Grove shield

* **button** is connected to port D2 on the Grove shield

* **LED** is connected to port D3 on the Grove shield

## Installation

* Install all required libraries in the Arduino IDE
* You may need to set the time and date on the RTC module using the [RTC\_set\_time.ino](RTC_set_time.ino) sketch
* Upload the `version1.ino` sketch to the Mega board

## Functions

When the program starts, you must choose one of three functions:

* Display sensor values on the LCD screen
* Log data to the SD card
* Send data to Node-RED via the serial connection

I use an automaton with a button, as shown below, to make this selection:

![](automat.png)

## Node-RED

* See the official documentation to install Node-RED on Windows:
  [https://nodered.org/docs/getting-started/windows](https://nodered.org/docs/getting-started/windows)
  [https://nodered.org/docs/getting-started/local](https://nodered.org/docs/getting-started/local)

* Mega board sends data in JSON format via the serial connection to Node-RED

* Import the flow using [flows.json-1.txt](flows.json-1.txt)

* Don't forget to change COM port's name in  Serial node

* Flow exemple:

![](flows.jpg)

* Real-time dashboard. I use this dashboard in classroom with my students:

![](Dashboard.jpg)

## Python Scripts

I use Python scripts to graph datas stored on SD card.

* The first script, [Graph from csv.py](Python%20scripts/Graph%20from%20csv.py), displays one graph per data type in separate windows.
* The second script, [Graph from csv\_1graph.py](Python%20scripts/Graph%20from%20csv_1graph.py), displays multiple graphs in one window.
