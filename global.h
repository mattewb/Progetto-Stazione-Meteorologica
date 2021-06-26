//definizione pin
#define ok 2// pin bottone ok
#define avanti 13// pin bottone avanti
#define sensorePioggia A0 //pin YL-83
#define fotoresistore A1 //pin fotoresistore

//definiziione variabili & costanti

 const int led=9; //pin led
 const int buzzer=8;// pin buzzer
 const int pdht=4; //pin dht11
 char schermata[] = {'1','2','3','4','5'};// array che permette di modificare lo stato assunto dall'Arduino
 char stato='\n'; //stato assunto dall'Arduino in un dato istante
 bool avvisi=0; //flag avvisi
 bool pioggia=0;
 bool freddo=0;
