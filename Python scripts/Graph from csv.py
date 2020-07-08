# Nom du fichier
nom_fichier="Mesures.csv"    #<------ A compléter

#--------------------------------------------------------------
import os
print (os.getcwd())

import matplotlib.pyplot as plt
from datetime import datetime

import matplotlib.dates as mdates
import numpy as np

sep=';'
Format_date="%m/%d/%H:%M"

#Fonction pour récupérer les données d'une colonne dans le fichier
def readColCSV(n) :
    col= np.loadtxt(nom_fichier,delimiter=sep,skiprows=1,usecols=[n])
    return col

#Fonction pour récupérer la date dans le fichier
def readDate(n) :
    col= np.loadtxt(nom_fichier,delimiter=sep,skiprows=1,dtype=np.str,usecols=[n])
    col=[datetime.strptime(elmt, '%Y/%m/%d/%H:%M:%S') for elmt in col]
    return col

#Fonctions pour tracer les graphs
def courbe(X,title):
    fig, ax = plt.subplots()
    ax.plot(Date, X)
    fig.autofmt_xdate()
    ax.fmt_xdata = mdates.DateFormatter(Format_date)
    ax.set_title(title)

def courbe_part():
    fig, ax = plt.subplots()
    P1=ax.plot(Date, PM1,label="PM1")
    P2=ax.plot(Date, PM25,label="PM2,5")
    P3=ax.plot(Date, PM10,label="PM10")
    fig.autofmt_xdate(rotation=50)
    ax.fmt_xdata = mdates.DateFormatter(Format_date)
    ax.set_title("Particules dans l'air")
    plt.ylim(0,)
    plt.legend()

#-------- On démarre le programme ------------

# On récupère les  colonnes de données dans le fichier
Date=readDate (0)
T = readColCSV(1)
P = readColCSV(2)
Hum = readColCSV(3)
CO2 = readColCSV(4)
Cov = readColCSV(5)
PM1 = readColCSV(6)
PM25= readColCSV(7)
PM10= readColCSV(8)

#-------Tracé des graphs-------
courbe(T,'Température en °C')
plt.ylim(min(T)-3,max(T)+3)
courbe(P,'Pression en hPa')
plt.ylim(min(P)-5,max(P)+5)
courbe(Hum,'Humidité en %')
plt.ylim(40,100)
courbe(CO2,'Dioxyde de carbone en ppm')
courbe(Cov,'Composés organiques volatiles en ppm')
courbe_part()

plt.show()