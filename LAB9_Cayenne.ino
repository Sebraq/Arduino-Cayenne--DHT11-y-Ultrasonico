
#include <CayenneMQTTSerial.h>
#include "DHT.h"
#include <Ultrasonic.h>
#define TRIG 12
#define ECHO 11
Ultrasonic ultra(TRIG,ECHO);
DHT dht(2,DHT11);
float temp,cm;



// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "f809c3b0-f99b-11ed-8485-5b7d3ef089d0";
char password[] = "ac1bd44dbee46b9c63061eda9cda16277ef26582";
char clientID[] = "1e2d55d0-fb26-11ed-9ab8-d511caccfe8c";

void setup()
{
	//Baud rate can be specified by calling Cayenne.begin(username, password, clientID, 9600);
	Cayenne.begin(username, password, clientID);
  //Serial.begin(9600);
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
  dht.begin();
}

void loop() {
	Cayenne.loop();
}
CAYENNE_IN(0) { //ENCENDER LED ROJO
  digitalWrite(3, getValue.asInt());
}
CAYENNE_OUT(1){ //LEE Y ENVIA LA HUMEDAD A CAYENNE
 temp=dht.readHumidity();
 Cayenne.virtualWrite(1,temp);
}
CAYENNE_IN(2) { //ENCENDER LED VERDE
  digitalWrite(4, getValue.asInt());
}
CAYENNE_OUT(3){ //LEE Y ENVIA LA TEMPERATURA A CAYENNE
 temp=dht.readTemperature();
 Cayenne.virtualWrite(3,temp);
}
CAYENNE_OUT(4){ //LEE Y ENVIA SENSOR ULTRASONICO A CAYENNE
 cm=ultra.read(CM);
 Cayenne.virtualWrite(4,cm);
}

//Codigo realizado por Sebastian Fahad Letona Solorzano. Mayo 25 de 2023.



