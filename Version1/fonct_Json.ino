//---Ecriture des mesures la liaison série en JSON-------------
void ecriture_Json()
  {
  float result[3] = {0};
     
  Serial.print("{\"Temp\":");
  Serial.print(bme280.getTemperature(),1);
  Serial.print(",\"Pression\":");
  Serial.print((bme280.getPressure()/100));
  Serial.print(",\"Hum\":");
  Serial.print(bme280.getHumidity());
    
  //Ecriture C02      
  Serial.print(",\"CO2\":");
  if(scd30.isAvailable())
  {
    scd30.getCarbonDioxideConcentration(result);
    Serial.print(result[0],0);    
  }
  else {Serial.print(0);}
    
  //Ecriture Cov
  Serial.print(",\"Cov\":");
  Serial.print(cov);
       
  //Ecriture particules        
  Serial.print(",\"PM1\":");
  if(sensor.read_sensor_value(buf,29))
  {
    Serial.println("HM330X read result failed!!!");
  }
  Serial.print(parse_mesures(buf,4));
  Serial.print(",\"PM25\":"); 
  Serial.print(parse_mesures(buf,5));
  Serial.print(",\"PM10\":");
  Serial.print(parse_mesures(buf,6));
  Serial.println("}");
       
  }
