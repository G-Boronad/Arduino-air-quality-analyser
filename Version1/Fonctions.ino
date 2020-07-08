////Fonction capteur de particules
err_t parse_mesures(u8 *data,int u)
{
  u16 value=0;
  err_t NO_ERROR;
        
  int mes[7];  //nombres de résultats envoyés
  if(NULL==data)
  return ERROR_PARAM;
     
  for(int i=1;i<8;i++)
  {
    value = (u16)data[i*2]<<8|data[i*2+1];
    mes[i-1]=value;
  }
  return mes[u]; 
}

  
//-----------------------------------------------------------------------------
///Fonction pour le Attach interrupt
void compteur_6()
{
  static long lastDebounceTime = 0;
  if (lastDebounceTime == 0 || (millis() - lastDebounceTime) > 150)
  {
    lastDebounceTime = millis();
    compt++;
    if (compt==7){compt=1;}
    Serial.print("compt=");
    Serial.println(compt);
  }   
}

//-------------------------------------------------------------------
//Fonction pour le choix entre les deux fonctions lecture LCD ou ecriture SD
//Utilisation du bouton au demarrage avec 2 choix possibles
void bouton_init()
{
  //création de l'automate avec 2 choix
  etatBP = digitalRead (BP);
  if (oldetat == HIGH && etatBP == LOW)
  {
    if ( etat == WAIT){etat = CHOIX1;}
    else if (etat == CHOIX2){etat = CHOIX1;}
    else if (etat == CHOIX1){etat = CHOIX2;}
  }
  // Au démarrage attente d'un appui
  if (etat == WAIT)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Lecture mesures");
    lcd.setCursor(0,1);
    lcd.print("or push button");
  }
      
  //Affichage pour le choix 1
  if (etat == CHOIX1)
  {
    digitalWrite(DEL,1);
    Serial.println("Choix 1 = Enregistrement sur SD");
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Enregistrement");
    lcd.setCursor(0,1);
    lcd.print("sur SD...");
    delay (100);
  }
    
          //Affichage pour le choix 2
  if ( etat == CHOIX2)
  {
    Serial.println("Choix 2 = Node Red"); 
    digitalWrite(DEL,0);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Node Red");
    delay(100);
  }
  
  oldetat = etatBP;
  delay (50);
  }

//-------------------------------------------------------------------
//Initalisation carte SD
void initSD()
{
  Serial.print("Initializing SD card...");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Initialisation");
  lcd.setCursor(0,1);
  lcd.print("carte SD ...");
      
  if (!SD.begin(sd_pin)) 
  {
    Serial.println("initialization failed!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Initit SD");
    lcd.setCursor(4,1);
    lcd.print("ERREUR !");
    while (1);
  }
  Serial.println("initialization done.");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Initialisation :");
  lcd.setCursor(6,1);
  lcd.print("OK !");
  delay(2000);
  myFile = SD.open("Mesures.csv", FILE_WRITE);
  if (myFile) 
  {
    Serial.print("Ecriture des mesures.csv...");
    myFile.println("#Date heure;Temperature en °C; Pression en hPa; Humidite de l'air en %;CO2 dans l'air en ppm;COV dans l'air en µg/m3;PM1 en µg/L;PM2.5 en µg/L;PM10 en µg/L");
     // close the file:
    myFile.close();
    Serial.println("done.");
    delay(2000);
  }
  else
  {
    // Ecriture Erreur si l'initialisation échoue
    Serial.println("Error opening Mesures.csv");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Erreur avec");
    lcd.setCursor(0,1);
    lcd.print("fichier .csv");
    delay(5000);
  }
  
  digitalWrite(DEL,0);
  lcd.clear();
}
