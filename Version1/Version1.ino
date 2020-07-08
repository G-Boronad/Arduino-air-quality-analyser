/* SD card attached to SPI bus as follows:
 ** MOSI - pin 11 on Arduino Uno/ pin 51 for mega
 ** MISO - pin 12 on Arduino Uno/ pin 50 for Mega
 ** CLK - pin 13 on Arduino Uno/pin 52 for Méga
 ** CS - depends on your SD card shield or module.pin(10)
 
 Capteur HCHO sur pin 19 ( Rx1)
*/

//Pin  DEL et bouton
const int BP=3;
const int DEL=2;
int compt=1; //pour la fonction compteur de attach interrupt


// Durée pour le choix entre deux fonctions au début
unsigned long Start_time;
const int INIT= 8000;
//Durée entre 2 affichage sur le LCD
unsigned long prevtime = 0;

// Durée entre deux mesures vers Node Red
unsigned long starttime1;
const unsigned long duree1 = 2000;     //   <---------------------- 2s
// Durée entre deux mesures enregistrées
const unsigned long duree2 = 300000;     //   <---------------------- 5 min

//Bouton setup
int etat ;
int oldetat ;
int etatBP=0;
const int WAIT = 0;
const int CHOIX1 = 1; // Affichage des mesures en continu
const int CHOIX2= 2;  // Enregistrement des mesures sur la carte sd 

// init LCD
#include "rgb_lcd.h"
rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

//Horloge data logging
#include "RTClib.h"
RTC_DS1307 RTC;

//Data logger
#include <SPI.h>
#include <SD.h>
const int sd_pin = 10;
File myFile;
boolean sd_val=false;

//Init COV sensor (étalonné sur le formaldéhyde)
#include <DFRobotHCHOSensor.h>
DFRobotHCHOSensor hchoSensor(&Serial1);
int cov = 0;


//Init CO2 sensor (étalonné sur le formaldéhyde)
#include "SCD30.h"
#if defined(ARDUINO_ARCH_AVR)
  #pragma message("Defined architecture for ARDUINO_ARCH_AVR.")
  #define SERIAL Serial
#elif defined(ARDUINO_ARCH_SAM)
  #pragma message("Defined architecture for ARDUINO_ARCH_SAM.")
  #define SERIAL SerialUSB
#elif defined(ARDUINO_ARCH_SAMD)
  #pragma message("Defined architecture for ARDUINO_ARCH_SAMD.")  
  #define SERIAL SerialUSB
#elif defined(ARDUINO_ARCH_STM32F4)
  #pragma message("Defined architecture for ARDUINO_ARCH_STM32F4.")
  #define SERIAL SerialUSB
#else
  #pragma message("Not found any architecture.")
  #define SERIAL Serial
#endif


// Init atmosphere sens
#include "Seeed_BME280.h"
#include <Wire.h>
BME280 bme280;

//Init Particules sensor
#include "Seeed_HM330X.h"
HM330X sensor;
u8 buf[30];

//------------------------------------------------------------------------------

void setup() {
  // Serial, wire et RTC begin
  Serial.begin(9600);
  Serial.println("Start");
  Wire.begin();
  RTC.begin();
  // LCD Begin
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("WAIT");

  pinMode (DEL,OUTPUT);
  digitalWrite(DEL,1);
  Start_time= millis();
  
  pinMode (BP,INPUT);  
  oldetat = LOW ;
  etat = WAIT;
 
  // HCHO sensor
 Serial1.begin(9600);   

  //Initalisation atmosphere sensor
  if(!bme280.init()){
    Serial.println("#BME280 error!");
  }
  Serial.println("#BME280 start!!");

  //Initialisation du capteur de particules
  if(sensor.init())
    {
        Serial.println("HM330X init failed!!!");
        while(1);
    }
    
  //Initialisation C02 :
  scd30.initialize();
  float result[3] = {0};
  
  
  starttime1=millis();
  Start_time=millis();
}
  
//----------------------------------------------------------------------------
void loop() 
{
  
  while (millis()-Start_time<INIT)
  {
    bouton_init();
  }
  if(hchoSensor.available()>0)  
    {
      cov = hchoSensor.uartReadPPM()*1200;
    } 
  if (etat == WAIT)
  {
    lecture_LCD();
  }
  if (etat == CHOIX1)
  {
    lcd.setRGB(0, colorG, colorB);
    if (sd_val==false)
    {
      initSD();
      sd_val=true;
    }
    if ((millis()-starttime1) > duree2)
    {
      ecriture_sd();
      starttime1=millis();
    }
  }
   
  if (etat == CHOIX2)
  {
    if ((millis()-starttime1) > duree1)
    {
      ecriture_Json();
      starttime1 = millis();
    }
  }
} 
