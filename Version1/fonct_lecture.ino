//--------Fonction lectures des mesures sur le LCD--------------------
void lecture_LCD()
{
  attachInterrupt(1, compteur_6, FALLING); //attache l'interruption externe n°1 (pin3)  
  float result[3] = {0};    //capteur CO2
  if (millis()- prevtime > 2000)
  {
    if (compt==1)       //température
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Temperature en C");
      lcd.setCursor(4,1);
      lcd.print(bme280.getTemperature(),1);
      prevtime = millis();
    }
     
    if (compt==2)       //pression
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pression en hPa");
      lcd.setCursor(4,1);
      lcd.print(bme280.getPressure()/100);
      prevtime = millis();
    }
      
    if (compt==3)       //Humidité
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Humidite en %");
      lcd.setCursor(6,1);
      lcd.print(bme280.getHumidity());
      prevtime = millis();
    }
      
    if (compt==4)       //CO2
    {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("CO2 en ppm");
      lcd.setCursor(6,1);
      if(scd30.isAvailable())
      {
        scd30.getCarbonDioxideConcentration(result);
        lcd.print(result[0],0);   
    }
    else {lcd.print(0);}
    prevtime = millis();
    }
        
    if (compt==5)       //Cov
    {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("COV en ug/m3");
      lcd.setCursor(6,1);
      lcd.print(cov);
      prevtime = millis();
    }
          
    if (compt==6)     //Particules
    {
      int part=0;
      if(sensor.read_sensor_value(buf,29))
      {
        Serial.println("HM330X read result failed!!!");
      }
          
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" PM10 en ug/L");
      lcd.setCursor(4,1);
      lcd.print(parse_mesures(buf,6));
      prevtime = millis();
    }  
  }
}
