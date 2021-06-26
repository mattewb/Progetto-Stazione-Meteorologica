#ifndef FUNZIONI_H  
#define FUNZIONI_H 

//    ***   funzioni prima schermata     ***


float ottieniTemperatura();//funzione che restituisce la temperatura


float ottieniUmidita();//funzione che restituisce l'umidità



//    ***   funzioni seconda schermata   ***

float ottieniPressione();//funzione che restituisce la pressione in mb


//    ***   funzioni terza schermata   ***

void countup();//funzione contatore

float ottieniVento();//funzione che restituisce la velocità del vento



//    ***   funzioni terza schermata   ***

int  ottieniPioggia(int pin);//funzione che restituisce il valore di luce

int ottieniLuce(int pin);//funzione che restituisce il valore di luce
 

//    ***   funzioni quarta schermata     ***
  

void accendiAvvisi(int buzzer, int led); //funzione che attiva il buzzer e il led

#endif
