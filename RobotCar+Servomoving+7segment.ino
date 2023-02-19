
#define TRIGGER_PIN  13 // Trigger pin is 13
#define ECHO_PIN     12 // Echo pin is 12
#define MAX_DISTANCE 400 // Maximum distance we want to measure (in centimeters).

#include <Servo.h> // Includes the library Servo motor to program the servo motor.

Servo myservo; // Creates servo object to control a servo.

#define IR 9 //Pin al que va conectado nuestro receptor de infrarrojos. En mi caso CHQ1838

long duracion[32]; //array que contiene la duracion de cada pulso en microsegundos (uS)
int x=0; //Contador para moverse por las distintas variables de los arrays
byte bits[32]; //Array de bits tras la conversion de tiempos a bits. (Ver protocolo NEC)
int pulso_comienzo; //En esta variable se almacena el valor del pulso de inicio de 4,5mS
int codigo_tecla=0; //Valor de la tecla pulsada convertido de binario a decimal
/********************************************************************************************/
/********************************************************************************************/
// CONFIGURACION DEL MICROPROCESADOR
#define INTERVAL_SERVO1 1000
#define INTERVAL_SERVO2 2000
unsigned long time_1 = 0;
unsigned long time_2 = 0;

int MotorA=7; // Motor A of the car connected to pin 7.
int MotorB=8;  // Motor B of the car connected to pin 8.
int PWMA=5; // PWMA (Pulse With Modulation A) connected to pin 5 .
int PWMB=6; // PWMB (Pulse With Modulation B) connected to pin 6.
int Speed=255; // Stores the values of the speed, inicially it is 255 (Max speed).
int Low_Speed=100; // The car will run in a low speed (100) to give time to the program to work properly.
int Medium_Speed=127; // The car will run in a medium speed (100) to give time to the program to work properly.

void setup() 
{
pinMode(MotorA, OUTPUT); // Pin Motor A set as output.
pinMode(MotorB, OUTPUT); // Pin Motor B set as output.
pinMode(PWMA, OUTPUT); // Pin PWMA set as output.
pinMode(PWMB, OUTPUT); // Pin PWMB set as output.
pinMode(3, OUTPUT); // Pin 3 set as output.
Serial.begin(9600); // Initialize the serial monitor.
myservo.attach(10); // Sets the pin of the servo motor.
}

// PROGRAMA PRINCIPAL
void loop() 
{
  if(millis() >= time_1 + INTERVAL_SERVO1){
        time_1 =millis();
        myservo.write(0);
    }
   if(millis() >= time_2 + INTERVAL_SERVO2){
        time_2 =millis();
        myservo.write(180);
    }

  if(digitalRead(IR)==0) //Esperamos que se pulse una tecla
  {  
    lecturaCodigoIr(); //Funcion que lee la tecla pulsada y la almacena en la variable (codigo_tecla)
    //Accion a realizar segun la tecla pulsada. 
    switch(codigo_tecla) 
    {
      case 25:
        Serial.println("Adelante");
        forward(Speed);
        break;
      case 9:
        Serial.println("Izquierda");
        left(Speed);
        break;
      case 1:
        Serial.println("Stop");
        Stop(); 
        break;
      case 49:
        Serial.println("Derecha");
        right(Speed);
        break;
      case 42:
        Serial.println("Atras");
        backward(Speed);
        break;
      case 12:
        Serial.println("UNO");
        Speed=127; 
        break;
      case 6:
        Serial.println("DOS");
        Speed=255;
        break;
      case 31:
        Serial.println("TRES");
        break;
      case 4:
        Serial.println("CUATRO");
        break;
      case 14:
        Serial.println("CINCO");
        break;
      case 23:
        Serial.println("SEIS");
        break;
      case 17:
        Serial.println("SIETE");
        break;
      case 19:
        Serial.println("OCHO");
        break;
      case 21:
        Serial.println("NUEVE");
        break;
    }
  }
}

void lecturaCodigoIr() 
{
  //PASO 1: DETECCION DEL PULSO DE INICIO DE SECUENCIA (4,5mS)
  pulso_comienzo=pulseIn(IR, HIGH);
  if(pulso_comienzo>4000 && pulso_comienzo<5000) //...comprobamos si es el pulso de comienzo de 4,5mS (inicio de secuencia)
  {
    //PASO 2: CRONOMETRAJE DE TIEMPOS DE CADA PULSO(uS)
    for(x=1; x<=32; x++) 
    {
      duracion[x]=pulseIn(IR, HIGH); //Duracion de cada pulso (uS)
    }
    //PASO 3: SEGUN EL TIEMPO DE CADA PULSO, DETERMINAMOS SI ES UN 0 O UN 1 LOGICO (Ver protocolo NEC)
    for(x=1; x<=32; x++) 
    {
      if(duracion[x]>500 && duracion[x]<700) //Si el pulso dura entre 500 y 700uS...
      {  
        bits[x]=0; //... es un 0 logico
      }
      if(duracion[x]>1500 && duracion[x]<1750) //Si el pulso dura entre 1500 y 1750uS
      {
        bits[x]=1; //... es un 1 logico
      }
    }      
    //PASO 4: CONVERSION DEL ARRAY BINARIO A VARIABLE DECIMAL. 
    //Puesto que muchos de los bits se repiten en todas las teclas, omitimos dichos bits y 
    //nos quedamos con los bits 17 al 21 y el 23 (6 bits). Suficientes para distinguir todas las teclas.
    //Estos 6 bits los convertimos a decimal con el metodo de Potencias de 2. Y el resultado lo almacenamos
    //en la variable codigo_tecla.
    codigo_tecla=0; //Reseteamos la ultima tecla pulsada
    if(bits[17]==1)
    {
      codigo_tecla=codigo_tecla+32; //2^6
    }
    if(bits[18]==1)
    {
      codigo_tecla=codigo_tecla+16; //2^5
    }
    if(bits[19]==1)
    {
      codigo_tecla=codigo_tecla+8; //2^4
    }
    if(bits[20]==1)
    {
      codigo_tecla=codigo_tecla+4; //2^3
    }
    if(bits[21]==1)
    {
      codigo_tecla=codigo_tecla+2; //2^2
    }
    if(bits[23]==1)
    {
      codigo_tecla=codigo_tecla+1; //2^1
    }
  }
  delay(180); //retardo para que no se produzcan "rebotes" y no lea dos pulsaciones de la misma tecla
}

void forward(int x){ // Function to called "forward".
  /* The function "fordward" makes the car go forward by using this methode:
      1. The Motor A has to go forward, so we give high voltage (1) to its pin 
      2. The Motor B also has to go forward, so we give high voltage (1) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */  
  digitalWrite(3, 1);
  digitalWrite(MotorA,1);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, x);
}
void backward(int x){ // Function called "backward".
  /* The function "backward" makes the car go backwards by using this methode:
      1. The Motor A has to go backward, so we give low voltage (0) to its pin 
      2. The Motor B also has to go backward, so we give low voltage (0) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */
  digitalWrite(3, 1);
  digitalWrite(MotorA,0);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 0);
  analogWrite(PWMB, x);
}
void left(int x){ // Function called "left".
  /* The function "left" makes the car turn to the left by using this methode:
      1. The Motor A has to go forward, so we give high voltage (1) to its pin 
      2. The Motor B has to go backwards, so we give low voltage (0) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */
  digitalWrite(3, 1);
  digitalWrite(MotorA,1);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 0);
  analogWrite(PWMB, x);
}
void right(int x){ // Function called "right".
  /* The function "right" makes the car turn to the right by using this methode:
      1. The Motor A has to go backward, so we give low voltage (0) to its pin 
      2. The Motor B has to go forward, so we give high voltage (1) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */
  digitalWrite(3, 1);
  digitalWrite(MotorA,0);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, x);
}
void Stop(){ // Function called "stop".
  /* The function "stop" stops the car by using this methode:
      1. The Motor A has to go fordward, so we give high voltage (1) to its pin 
      2. The Motor B also has to go forward, so we give high voltage (1) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will have no speed as we want the car to stop.
  */
  digitalWrite(3, 1);
  digitalWrite(MotorA,1);
  analogWrite(PWMA, 0);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, 0);
}
