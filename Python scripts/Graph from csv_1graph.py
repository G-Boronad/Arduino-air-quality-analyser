# Nom du fichier
nom_fichier="Mesures.csv"       #<-------------------------------- A compléter


#-------------------------------------------------------------------------------
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

#-------Fonctions pour tracer des courbes------

#Température
def graph_temp(i):
    ax[i].fmt_xdata = mdates.DateFormatter(Format_date)
    ax[i].plot(Date,T)
    ax[i].set_ylim((min(T)-3),(max(T)+3))
    ax[i].set_title("Température en °C")

#Pression
def graph_pres(i):
    ax[i].fmt_xdata = mdates.DateFormatter(Format_date)
    ax[i].plot(Date, P)
    ax[i].set_ylim(min(P)-5,max(P)+5)
    ax[i].set_title("Pression en Pa")

#humidité
def graph_hum(i):
    ax[i].fmt_xdata = mdates.DateFormatter(Format_date)
    ax[i].plot(Date, Hum)
    ax[i].set_ylim(40,100)
    ax[i].set_title("Humidité en %")

#CO2
def graph_co2(i):
    ax[i].fmt_xdata = mdates.DateFormatter(Format_date)
    ax[i].plot(Date, CO2)
    ax[i].set_title("CO2 en ppm")

#Cov
def graph_cov(i):
    ax[i].fmt_xdata = mdates.DateFormatter(Format_date)
    ax[i].plot(Date, Cov)
    ax[i].set_title("COV en ppb")

#Particules
def graph_part(i):
    ax[i].fmt_xdata = mdates.DateFormatter(Format_date)
    ax[i].plot(Date,PM1,label="PM1")
    ax[i].plot(Date,PM25,label="PM2,5")
    ax[i].plot(Date,PM10,label="PM10")
    ax[i].set_title("Particules dans l'air")
    ax[i].legend()
    ax[i].set_ylim(0,)

#-------- On démarre le programme ------------

# On récupère les  colonnes de données du fichier
Date = readDate(0)
T = readColCSV(1)
P = readColCSV(2)
P=P/100
Hum = readColCSV(3)
CO2 = readColCSV(4)
Cov = readColCSV(5)
PM1 = readColCSV(6)
PM25= readColCSV(7)
PM10= readColCSV(8)

#On demande quelles courbes  afficher ?
n=0
if input("Voulez vous afficher la Température? (o/n)") == "o":
    n=n+1
    n_temp=n-1
    trace_temp=True
else:
    trace_temp=False
if input("Voulez vous afficher la Pression? (o/n)") == "o":
    n=n+1
    n_pres=n-1
    trace_pres=True
else:
    trace_pres=False
if input("Voulez vous afficher l'humidité? (o/n)") == "o":
    n=n+1
    n_hum=n-1
    trace_hum=True
else:
    trace_hum=False
if input("Voulez vous afficher le CO2? (o/n)") == "o":
    n=n+1
    n_co2=n-1
    trace_co2=True
else:
    trace_co2=False
if input("Voulez vous afficher les COV? (o/n)") == "o":
    n=n+1
    n_cov=n-1
    trace_cov=True
else:
    trace_cov=False
if input("Voulez vous afficher les particules? (o/n)") == "o":
    n=n+1
    n_part=n-1
    trace_part=True
else:
    trace_part=False

# On trace
fig,ax = plt.subplots(n,1)
fig.set_figheight(7)
fig.set_figwidth(10)
fig.subplots_adjust(left=0.05, bottom=0, right=0.98, top=0.95, wspace=None, hspace=0.2)
#https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.pyplot.subplots_adjust.html
fig.autofmt_xdate(rotation=60)
#https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.figure.Figure.html

if trace_temp==True:
    graph_temp(n_temp)
if trace_pres==True:
    graph_pres(n_pres)
if trace_hum==True:
    graph_hum(n_hum)
if trace_co2==True:
    graph_co2(n_co2)
if trace_cov==True:
    graph_cov(n_cov)
if trace_part==True:
    graph_part(n_part)

plt.show()