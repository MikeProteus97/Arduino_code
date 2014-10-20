/* PROGRAMA SEMAFOROS */
// By Michael Vargas 
// mikeandroid97@gmail.com  \ @MichaelVargas97
#define veh_Rojo1      7         //pines de ubicación de LEDS
#define veh_Amarillo1  6
#define veh_Verde1     5                  
#define veh_Rojo2      10
#define veh_Amarillo2  9
#define veh_Verde2     8
#define pea_Verde1     3
#define pea_Rojo1      4
#define pea_Rojo2      11
#define pea_Verde2     12
#define boton          2
//############### ESPACIO CONSTANTES y PARA VARIABLES ###########
const int intervalo=5000;  // Tiempo de espera en verde o rojo
const int numero_parpadeos=3;// numero de parpadeos antes de que el semaforo vehicular pase a verde
const int frecuencia_parpadeo=250; // tiempo en el que parpadea el semaforo peatonal verde
const int res_parpadeo= (numero_parpadeos*2) * frecuencia_parpadeo; // no puede ser mayor al intervalo
const int parpadeo_pea= intervalo - res_parpadeo ; // es el tiempo para activar el parpadeo peatonal hay un desfase de 500 ms
const int tiempo_amarillo= 800; // tiempo de demora en el semaforo amarillo
const int frecuencia_amarillo=250; // el amarillo 1 se alcanza al Amarillo1 se alcanza al amarillo2

unsigned long tiempo = 0;  // no tocar
boolean repetir=true;  // no tocar // para hacer la secuencia inicial una sola vez
unsigned int estado_boton=0;  // no tocar // Activar el seteo de los semaforos

//############# ESPACIO PARA FUNCIONES #######
void parpadear_amarillo(){
  digitalWrite(pea_Rojo1,HIGH);
  digitalWrite(pea_Rojo2,HIGH);
  digitalWrite(veh_Amarillo1,HIGH);
  digitalWrite(veh_Amarillo2,HIGH);
  delay(200);
  digitalWrite(pea_Rojo1,LOW);
  digitalWrite(pea_Rojo2,LOW);
  digitalWrite(veh_Amarillo1,LOW);
  digitalWrite(veh_Amarillo2,LOW);
  delay(200);
  }

 void secuencia(){
   
          for (int x=1; x<=(numero_parpadeos+1);x++){
          digitalWrite(pea_Verde1,HIGH);
          delay(frecuencia_parpadeo);
          digitalWrite(pea_Verde1,LOW);
          delay(frecuencia_parpadeo);
          }
          digitalWrite(pea_Rojo1,HIGH);
          digitalWrite(veh_Verde2,LOW);
          digitalWrite(veh_Amarillo2,HIGH);
          delay(frecuencia_amarillo);
          digitalWrite(veh_Rojo1,LOW);
          digitalWrite(veh_Amarillo1,HIGH);
          delay(tiempo_amarillo);
          digitalWrite(veh_Amarillo2,LOW);
          digitalWrite(veh_Rojo2,HIGH);
          delay(frecuencia_amarillo);
          digitalWrite(veh_Amarillo1,LOW);
          digitalWrite(veh_Verde1,HIGH);
          digitalWrite(pea_Rojo2,LOW);
          digitalWrite(pea_Verde2,HIGH);
          delay(parpadeo_pea);
          for (int x=1; x<=(numero_parpadeos+1);x++){
          digitalWrite(pea_Verde2,HIGH);
          delay(frecuencia_parpadeo);
          digitalWrite(pea_Verde2,LOW);
          delay(frecuencia_parpadeo);
          }
          digitalWrite(pea_Rojo2,HIGH);
          digitalWrite(veh_Verde1,LOW);
          digitalWrite(veh_Amarillo1,HIGH);
          delay(frecuencia_amarillo);
          digitalWrite(veh_Rojo2,LOW);
          digitalWrite(veh_Amarillo2,HIGH);
          delay(tiempo_amarillo);
          digitalWrite(veh_Amarillo1,LOW);
          digitalWrite(veh_Rojo1,HIGH);
          delay(frecuencia_amarillo);
          digitalWrite(veh_Amarillo2,LOW);
          digitalWrite(veh_Verde2,HIGH);
          digitalWrite(pea_Rojo1,LOW);
          digitalWrite(pea_Verde1,HIGH);
           tiempo = millis();
 }
   
  void secuencia_inicial(){
    
 if ( repetir == true ){
      digitalWrite(veh_Rojo1,HIGH);
      digitalWrite(pea_Verde1,HIGH);
      digitalWrite(veh_Verde2,HIGH);
      digitalWrite(pea_Rojo2,HIGH);
      repetir=false;
  }
 }
void semaforo_arduino(){
 
  estado_boton= digitalRead(boton);
  if ( estado_boton == LOW && (millis() - tiempo > 0) ) {
     parpadear_amarillo();
     tiempo=millis();
  
  }
  else {
          if ( estado_boton  == HIGH){
               secuencia_inicial();
          if ((millis() - tiempo) >= parpadeo_pea ){
                secuencia();
   }    
  }
 }
} 
//############# CODIGO PRINCIPAL #######
void setup() {
// Definir puertos de entrada y salida
 pinMode(boton,INPUT);
for (int pin=3;pin <=12;pin++){
   pinMode(pin,OUTPUT);
  }
}

void loop() {
semaforo_arduino();
}
