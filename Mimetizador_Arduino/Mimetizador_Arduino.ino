#include <LiquidCrystal.h>
#include "DHT.h"

const long A = 1000;     //Resistencia en oscuridad en KΩ
const int B = 15;        //Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10;       //Resistencia calibracion en KΩ
const int LDRPin = A0;   //Pin del LDR

const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;   //se agregan los pines a las entradas a usar del LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int V;                      //variables a usar para los datos de los mensajes
int ilum; 
int SENSOR = 2;
int temp, humedad;
String mensaje = "";
String aux = "";
char input;
int cont = 0;

int estadoAnterior = 0;     //valores usados para detectar el cambio de boton
int estadoActual;
int contador = 0;

String mensajes[5];
int arregloConta = 0;
int boton = 8; // aquí el pin digital que se quiere leer para boton



DHT dht (SENSOR, DHT11);    //declaramos sensor de temperatura y humedad

void setup(){
  Serial.begin(9600);
  dht.begin();
    // INDICAMOS QUE TENEMOS CONECTADA UNA PANTALLA DE 16X2
  lcd.begin(16, 2);
  // MOVER EL CURSOR A LA PRIMERA POSICION DE LA PANTALLA Y BORRAR (0, 0)
  lcd.clear();
  pinMode(boton, INPUT);
  }

void loop(){

  estadoActual = digitalRead(boton);    //aqui nos detectara el cambio de boton
  if (estadoAnterior != estadoActual)  // ha habido un cambio de estado
  {
    contador++;                          // cuenta los cambios de estado
    int validarPar = contador % 2;       // solo queremos los cambios pares
    if (validarPar != 1)                 // si el cambio es par 
    {
      cont++;                           //sumamos la variable contador que nos servira para elegir el mensaje a mostrar
      lcd.clear();
      if(cont == 4){
        cont=0;
        }
    }
    estadoAnterior = estadoActual;
  }

  
  humedad = dht.readHumidity();       //leemos la humedad en sensor y la temperatura
  temp = dht.readTemperature();
  V = analogRead(LDRPin);                         //Leemos valor de LDR      
  ilum = ((long)V*A*10)/((long)B*Rc*(1024-V));    //calculos para la luminosidad


  while (Serial.available() > 0) {
  input = Serial.read();
  aux += input;                               //iniciamos lectura de caracteres y lo guadamos en la varia tipo cadena aux
  }

mensajes[arregloConta] = aux;             //Colocamos mensaje dentro del arreglo

 if(cont == 0){                           //Dependiendo del valor del contador al pulsar boton, mostramos el mensaje indicado
    lcd.clear();
    arregloConta = 0;
  lcd.print(mensajes[arregloConta]);
  delay(1000);
}

  if(cont == 1){
    lcd.clear();
    lcd.print(" Temperatura  ");
    lcd.setCursor(0, 1);
    lcd.print(temp);
    delay(1000);
  }
  
  if(cont == 2){
   lcd.clear();
   lcd.print(" Humedad  ");
   lcd.setCursor(0, 1);
   lcd.print(humedad);
   delay(1000);

}

  if(cont == 3){
   lcd.clear();
   lcd.print(" Luminosidad  ");
   lcd.setCursor(0, 1);
   lcd.print(ilum);
   delay(1000);
}
  
  }

