//---Ecriture des mesures sur la carte SD-------------
void ecriture_sd()
{
  float result[3] = {0};
  myFile = SD.open("Mesures.csv", FILE_WRITE);
  if (myFile) 
  {
    DateTime now = RTC.now();
    digitalWrite(DEL,1);
             
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print('/');
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.print(";");
    
    myFile.print(bme280.getTemperature(),1);
    myFile.print(";");
    myFile.print((bme280.getPressure()/100));
    myFile.print(";");
    myFile.print(bme280.getHumidity());
    myFile.print(";");
    //Ecriture C02      
    if(scd30.isAvailable())
    {
      scd30.getCarbonDioxideConcentration(result);
      myFile.print(result[0],0);    
    }
    else {myFile.print(0);}
    myFile.print(";");
    
    //Ecriture Cov
     myFile.print(cov);
     myFile.print(";");
                          
    
    //Ecriture particules        
    if(sensor.read_sensor_value(buf,29))
    {
      Serial.println("HM330X read result failed!!!");
    }
    myFile.print(parse_mesures(buf,4));
    myFile.print(";"); 
    myFile.print(parse_mesures(buf,5));
    myFile.print(";");
    myFile.println(parse_mesures(buf,6));
       
    // close the file:
    //delay(1000);
    myFile.close();
    Serial.println("done.");
    lcd.clear();
    digitalWrite(DEL,0);
    }
    else 
    {
    // if the file didn't open, print an error:
    Serial.println("Error opening Mesures.txt");
    }
  }
