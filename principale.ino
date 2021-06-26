//include
#include <LiquidCrystal_I2C.h> //Include la libreria per il display
LiquidCrystal_I2C lcd(0x27, 16, 2); // Imposta l'indirizzo del lcd a 0x27 per 16 caratteri 2 linee

#include "global.h" //si include il file dove definisco le variabili
#include "funzioni.h"//si includono le funzioni sviluppate

void setup()
{
  
  //definizione I/O pin
  pinMode(ok,INPUT); 
  pinMode(avanti,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(sensorePioggia,INPUT);
  pinMode(fotoresistore,INPUT);
  lcd.begin(); //inizializzo il display
  lcd.backlight(); //accende la retroilluminazione
  lcd.setCursor(0, 0);//seleziono la posizione da dove iniziare a scrivere
  lcd.print("Avvio...");
  delay(1000);
  lcd.clear();//pulisco il display
  stato=schermata[0];//imposto la prima schermata da visualizzare
}
void loop(){
  //lettura sensori principali per effettuare il controllo avvisi
  float  temperatura=ottieniTemperatura();
  int    luce=ottieniLuce(fotoresistore);
  int    vPioggia=ottieniPioggia(sensorePioggia);
  
  //controllo per l'attivazione della retroilluminazione
  if(luce<200){
    lcd.backlight();
    }
  else{
    lcd.noBacklight();
  }
  
  //controllo degli avvisi, se impostati
  if(avvisi==1){
          if(temperatura<0){
            stato=6;
            freddo=1;
            }
          if(vPioggia<500){
            stato=6;
            pioggia=1;
            }
          }
          
  //gestione delle schermate
    switch(stato){ 
      
    case '1':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: "+String(ottieniTemperatura())+" "+(char)0xDF+"C");
      lcd.setCursor(0, 1);
      lcd.print("Umid: "+String(ottieniUmidita())+"  "+(char)0x25);
      delay(1000);
     if(digitalRead(avanti)==HIGH){
          delay(300);
          stato=schermata[1];
        } 
    break;
    
     case '2':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pressione: ");
      lcd.setCursor(0, 1);    
      lcd.print(String(ottieniPressione())+" mb");
      delay (2000);
      stato=schermata[2];     
    break;
    
    case '3':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Vento: ");
      lcd.setCursor(0, 1);    
      lcd.print(String(ottieniVento())+" mS");
      delay (1000);
     if(digitalRead(avanti)==HIGH){
          delay(300);
          stato=schermata[3];     
      }
    break;
    
     case '4':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pioggia: "+ String(ottieniPioggia(sensorePioggia))); //OK
      lcd.setCursor(0, 1);
      lcd.print("Luce: "+ String(ottieniLuce(fotoresistore))); //OK
      delay (1000);
     if(digitalRead(avanti)==HIGH){
          delay(300);
          stato=schermata[4];
        }   
    break;
    
     case '5':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Impostazioni:");
      if (avvisi==1){
      lcd.setCursor(0, 1);
      lcd.print("Avvisi: ON");
    }
     else{
      lcd.setCursor(0, 1);
      lcd.print("Avvisi: OFF");
    }
      delay(1000);
      if(digitalRead(ok)==HIGH){
          avvisi=!avvisi;
        }
      if(digitalRead(avanti)==HIGH){
          delay(300);
          stato=schermata[0];
        }
    break;
    
    default: //lancio gli allarmi/schermate relative al freddo o se piove 
      lcd.clear();  
      if(pioggia==1 && freddo==1){
          lcd.setCursor(0, 0);
          lcd.print("Allerta Neve!");
          accendiAvvisi(buzzer, led);
         if(digitalRead(ok)==HIGH){
              delay(300);
              stato=schermata[0];
              avvisi=0;
              pioggia=0;
              freddo=0;
          } 
      }
      else if(pioggia==1){
        lcd.setCursor(0, 0);
        lcd.print("Piove!");
        //attivo il buzzer e il led che lampeggia
        accendiAvvisi(buzzer,led);
        if(digitalRead(ok)==HIGH){
           delay(300); 
            stato=schermata[0];
            avvisi=0;
            pioggia=0;
          } 
      }
       if(freddo){
        lcd.setCursor(0, 0);
        lcd.print("Temperatura < 0!");
        //attivo il buzzer e il led che lampeggia
         accendiAvvisi(buzzer,led);
         if(digitalRead(ok)==HIGH){
           delay(300); 
            stato=schermata[0];
            avvisi=0;
            freddo=0;
         
          }
          
    
      }
          break;

    }
}
  
