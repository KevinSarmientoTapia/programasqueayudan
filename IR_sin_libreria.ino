/*********************************************************************************************
Lector de mando a distancia por infrarrojos (ver 1.0)
**********************************************************************************************
AUTOR: Angel Lozano L.
FECHA: 05/02/2015
PAGINA WEB: https://www.facebook.com/Arduinoenespanol
DESCRIPCION: Decodifica las teclas del mando a distancia sin necesidad de libreria.
Este programa esta basado en el protocolo NEC.
*********************************************************************************************/
// LIBRERIAS INCLUIDAS (ninguna)
/********************************************************************************************/
// DEFINICION DE VARIABLES Y CONSTANTES
#define IR 9 //Pin al que va conectado nuestro receptor de infrarrojos. En mi caso CHQ1838

long duracion[32]; //array que contiene la duracion de cada pulso en microsegundos (uS)
int x=0; //Contador para moverse por las distintas variables de los arrays
byte bits[32]; //Array de bits tras la conversion de tiempos a bits. (Ver protocolo NEC)
int pulso_comienzo; //En esta variable se almacena el valor del pulso de inicio de 4,5mS
int codigo_tecla=0; //Valor de la tecla pulsada convertido de binario a decimal
/********************************************************************************************/
/********************************************************************************************/
// CONFIGURACION DEL MICROPROCESADOR
void setup() 
{
  Serial.begin(9600);
}

// PROGRAMA PRINCIPAL
void loop() 
{
  
  if(digitalRead(IR)==0) //Esperamos que se pulse una tecla
  {  
    lecturaCodigoIr(); //Funcion que lee la tecla pulsada y la almacena en la variable (codigo_tecla)
    //Accion a realizar segun la tecla pulsada. 
    switch(codigo_tecla) 
    {
      case 41: //El codigo decimal que corresponde a la tecla STANDBY es 41
        Serial.println("STANDBY");
        break;
      case 25:
        Serial.println("MODE");
        break;
      case 57:
        Serial.println("MUTE");
        break;
      case 9:
        Serial.println("PLAY/PAUSA");
        break;
      case 1:
        Serial.println("ATRAS");
        break;
      case 49:
        Serial.println("ADELANTE");
        break;
      case 56:
        Serial.println("ECUALIZADOR");
        break;
      case 42:
        Serial.println("MENOS -");
        break;
      case 36:
        Serial.println("MAS +");
        break;
      case 26:
        Serial.println("CERO");
        break;
      case 38:
        Serial.println("ALEATORIO");
        break;
      case 44:
        Serial.println("U/SD");
        break;
      case 12:
        Serial.println("UNO");
        break;
      case 6:
        Serial.println("DOS");
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
//FIN PROGRAMA PRINCIPAL**************************************************************************/
/*************************************************************************************************/
// SUBRUTINAS
//Subrutina que lee que tecla del mando a distancia se ha pulsado y 
//la almacena en la variable codigo_tecla
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
//FIN SUBRUTINAS ************************************************************************************/

