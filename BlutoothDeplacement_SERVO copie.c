/*
Fichier:      ROVER ORANO INNOVATION 
Description:  Code Arduino, permettant de controler un petit rover
Creation :    20.07.2022
*/

// On associe la borne "ENA" du L298N à la pin D10 de l'Arduino (PWM possible sur cette broche)

#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(10, 11);
Servo myservo; 

// Association des entrees du L298N, aux sorties de l'Arduino Uno 

#define borneENA        5       // On associe la borne "ENA" du L298N a la pin 5 de l'Arduino (broche PWM)
#define borneIN1        2       // On associe la borne "IN1" du L298N a la pin 2 de l'Arduino
#define borneIN2        3       // On associe la borne "IN2" du L298N a la pin 3 de l'Arduino
#define borneIN3        4       // On associe la borne "IN3" du L298N a la pin 4 de l'Arduino
#define borneIN4        7       // On associe la borne "IN4" du L298N a la pin 7 de l'Arduino
#define borneENB        6       // On associe la borne "ENB" du L298N a la pin 6 de l'Arduino (broche PWM)

//Constatnes du programme

    //Mouvements Moteur

        // On defini des constante pour les directions

const char MARCHE_AVANT     =  'A';            
const char MARCHE_ARRIERE   =  'B';      
const char AVANT_GAUCHE     =  'C';
const char AVANT_DROITE     =  'D';        
const char ARRIERE_GAUCHE   =  'E';
const char ARRIERE_DROITE   =  'F';
const char CENTRE_GAUCHE    =  'G';
const char CENTRE_DROITE    =  'H';

    //Mouvement Servo

const char SERVO_0 =    ' ';
const char SERVO_45 =   ' ';
const char SERVO_90 =   ' ';
const char SERVO_135 =  ' ';
const char SERVO_180 =  ' ';

//Variables du programmes

int pos = 90;        // Position a l'allumage du Rover (90°)
char BluetoothData;  // Date recu par le communication bluetooth 

//*************************************************************//
                  // SETUP //
//*************************************************************//

void setup() {

  Serial.begin(9600);       // initialise la liaison serie a 9600 bauds;
  BT.begin(9600);           // declare la vitesse de communication

  Serial.println("Communication BLUETOOTTH -- TEST AVEC MODULE HC-06");
  Serial.println("Console DEBUG");

 // Configuration des pins de l'Arduino en "sortie"(pour L298N)

  pinMode(borneENA, OUTPUT);
  pinMode(borneIN1, OUTPUT);
  pinMode(borneIN2, OUTPUT);
  pinMode(borneIN3, OUTPUT);
  pinMode(borneIN4, OUTPUT);
  pinMode(borneENB, OUTPUT);

  myservo.attach(9);
  myservo.write(pos);
   
}

//*************************************************************//
              // Boucle principale : LOOP //
//*************************************************************//


void loop() {

   // Lecture du module BT et affichage des données sur le moniteur série de l'Ordinateur


 if (BT.available())
 {
    BluetoothData = BT.read();    //Get next character from bluetooth
    Serial.write(BluetoothData);  //ecrire le car sur le PC


    if(BluetoothData=='1'){
   configurerSensDeRotationPont(MARCHE_AVANT);
    }
   
    else if(BluetoothData=='3'){
   configurerSensDeRotationPont(MARCHE_ARRIERE);
    }

    else if(BluetoothData=='4'){
   configurerSensDeRotationPont(CENTRE_DROITE);
    }

   else if(BluetoothData=='2'){
   configurerSensDeRotationPont(CENTRE_GAUCHE);
    }

   else if(BluetoothData=='8'){
   configurerSensDeRotationPont(AVANT_DROITE);
    }

   else if(BluetoothData=='5'){
   configurerSensDeRotationPont(AVANT_GAUCHE);
    }

   else if(BluetoothData=='7'){
   configurerSensDeRotationPont(ARRIERE_DROITE);
    }
   
   else if(BluetoothData=='6'){
   configurerSensDeRotationPont(ARRIERE_GAUCHE);
    }
    
    else if(BluetoothData=='A'){
   myservo.write(180);
   }
    else if(BluetoothData=='B'){
    myservo.write(135);
 }    
    else if(BluetoothData=='C'){
   myservo.write(90);
}
   else if(BluetoothData=='D'){
   myservo.write(45);
}
   else if(BluetoothData=='E'){
    myservo.write(0);
 }
   
    else{
    digitalWrite(borneIN1, LOW);                 
    digitalWrite(borneIN2, LOW);                  
    digitalWrite(borneIN3, LOW);                 
    digitalWrite(borneIN4, LOW);
    }

 }  
 

  
}

// Fonction : Direction                                        

void configurerSensDeRotationPont(char sensDeRotation) {

  if(sensDeRotation == MARCHE_AVANT) {

    digitalWrite(borneIN1, HIGH);                 
    digitalWrite(borneIN2, LOW);                  
    digitalWrite(borneIN3, HIGH);                 
    digitalWrite(borneIN4, LOW); 

    changeVitesseMoteurPontA(220); 
    changeVitesseMoteurPontB(220);  
  }
  
  if(sensDeRotation == MARCHE_ARRIERE) {

    digitalWrite(borneIN1, LOW);                
    digitalWrite(borneIN2, HIGH);                 
    digitalWrite(borneIN3, LOW);             
    digitalWrite(borneIN4, HIGH);               
    
    changeVitesseMoteurPontA(220); 
    changeVitesseMoteurPontB(220);
  }

   if(sensDeRotation ==   AVANT_GAUCHE) {

    digitalWrite(borneIN1, HIGH);                 
    digitalWrite(borneIN2, LOW);                  
    digitalWrite(borneIN3, HIGH);                 
    digitalWrite(borneIN4, LOW); 

    changeVitesseMoteurPontA(150); 
    changeVitesseMoteurPontB(220);  
  }

    if(sensDeRotation ==   AVANT_DROITE) {

    digitalWrite(borneIN1, HIGH);                 
    digitalWrite(borneIN2, LOW);                  
    digitalWrite(borneIN3, HIGH);                 
    digitalWrite(borneIN4, LOW); 

    changeVitesseMoteurPontA(220); 
    changeVitesseMoteurPontB(150);  
  }

    if(sensDeRotation ==   ARRIERE_GAUCHE) {

    digitalWrite(borneIN1, LOW);                 
    digitalWrite(borneIN2, HIGH);                  
    digitalWrite(borneIN3, LOW);                 
    digitalWrite(borneIN4, HIGH); 

    changeVitesseMoteurPontA(150); 
    changeVitesseMoteurPontB(220);  
  }

    if(sensDeRotation ==   ARRIERE_DROITE) {

    digitalWrite(borneIN1, LOW);                 
    digitalWrite(borneIN2, HIGH);                  
    digitalWrite(borneIN3, LOW);                 
    digitalWrite(borneIN4, HIGH); 

    changeVitesseMoteurPontA(220); 
    changeVitesseMoteurPontB(150);  
  }

  if(sensDeRotation == CENTRE_GAUCHE) {

    digitalWrite(borneIN1, LOW);               
    digitalWrite(borneIN2, HIGH);        
    digitalWrite(borneIN3, HIGH);                 
    digitalWrite(borneIN4, LOW);     

    changeVitesseMoteurPontA(180); 
    changeVitesseMoteurPontB(180);              
  }

    if(sensDeRotation == CENTRE_DROITE) {

    digitalWrite(borneIN1, HIGH);                
    digitalWrite(borneIN2, LOW);               
    digitalWrite(borneIN3, LOW);                 
    digitalWrite(borneIN4, HIGH);  

    changeVitesseMoteurPontA(180); 
    changeVitesseMoteurPontB(180);                             
  } 
}

// Fonction : changeVitesse                                            

void changeVitesseMoteurPontA(int nouvelleVitesseA) {
  
  analogWrite(borneENA, nouvelleVitesseA);
}
void changeVitesseMoteurPontB(int nouvelleVitesseB) {
  
  analogWrite(borneENB, nouvelleVitesseB);
}