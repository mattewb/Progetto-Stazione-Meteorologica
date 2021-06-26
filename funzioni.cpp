//      ---     include      ---
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <Wire.h>//libreria necessaria per bmp 180
#include <Adafruit_BMP085.h> //libreria bmp 180
#include"funzioni.h"// includo file header
DHT_Unified dht(4, DHT11);//creo un oggetto di tipo DHT specificando il pin dov'è collegato il DHT11 e la tipologia di sensore (la libreria permette di interfacciarsi a vari sensori)
uint32_t delayMS;//creo una variabile per definire i delay in millisecondi per la lettura della temperatura

//variabili "locali" x DHT11
float tPrecedente=0.0;//variabile temperatura precedente
float uPrecedente=0.0;//variabile umidità precedente

// variabili per l'anemometro
const int tempoMisurazione = 3; //definizione del tempo di misurazione in secondi
const int SensorPin = 3;  //Definizione del pin di interrupt(2 o 3 @ Arduino Uno)
volatile int InterruptCounter;//contatore per contare il numero di interrupt
float velocitaVento;

//funzioni:

//funzioni prima schermata
float ottieniTemperatura(){
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  delay(delayMS);
  //si osserva l'evento che genera il DHT 11 
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    return tPrecedente;
  }
  else{
      tPrecedente=event.temperature;
      return event.temperature;
      }
}

float ottieniUmidita(){
  dht.begin();
  sensor_t sensor;
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  delay(delayMS);
  //si osserva l'evento che genera il DHT 11 
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    return uPrecedente;
  }
   else{
      uPrecedente=event.relative_humidity;
      return event.relative_humidity;
      }
}


//funzioni seconda schermata

void countup() {//funzione contatore
  InterruptCounter++;
}

float ottieniVento() {
  InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(SensorPin), countup, RISING); 
  delay(1000 * tempoMisurazione);
  detachInterrupt(digitalPinToInterrupt(SensorPin));
  velocitaVento = (float)InterruptCounter / (float)tempoMisurazione * 1.2;
  return velocitaVento/3.6;
}

float ottieniPressione(){
  Adafruit_BMP085 bmp; //creazione oggetto di tipo Adafruit_BMP085 per utilizzare le funzioni per il bmp 180
  bmp.begin(); 
  
  return (bmp.readPressure())*0.01;//Pa* 0.01 = mb
  };


//funzioni terza schermata

int ottieniPioggia(int pin){ 
     int sensorValue=analogRead(pin); //Legge il valore dal pin e lo assegna alla variabile
    //il sensore restituisce 1024 se non è bagnato, 0 se completamente bagnato
    return sensorValue;
  }

int ottieniLuce(int pin){
    int sensorValue = analogRead(pin);
    return sensorValue;//restituisco il valore di luce rilevata 
  }


//funzioni quarta schermata

  
void accendiAvvisi(int buzzer, int led){
    digitalWrite(led,HIGH);
    tone(buzzer,1000,200);     //suona nota sul pin 12 alla frequenza di 1000Hz
    delay(2000);                        //aspetta 2 secondi
    digitalWrite(led,LOW);
    noTone(buzzer);                //interruzione suono nota
    delay(1000);
     }
  
  
 
