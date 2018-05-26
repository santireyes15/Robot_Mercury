int ledPin0 =  A0; 
int ledPin1 =  A1; 
int ledPin2 =  A2; 
int ledPin4 =  A4; 
int ByteReceived;
int led=13;
const int EchoPin = 5;
const int TriggerPin = 6;


void setup() {
  // put your setup code here, to run once:
pinMode(ledPin0, OUTPUT);
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin4, OUTPUT);
pinMode(TriggerPin, OUTPUT);
pinMode(EchoPin, INPUT);
pinMode(led, OUTPUT);
Serial.begin(9600);

}
void encender()
{
  digitalWrite(led, HIGH);
}
void apagar()
{
  digitalWrite(led, LOW);
}
void aviso()
{
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
}
void Adelante()
{
  analogWrite(ledPin0,150);
  analogWrite(ledPin1,0);
  analogWrite(ledPin2,0);
  analogWrite(ledPin4,150);
}
void parar()
{
  analogWrite(ledPin0,0);
  analogWrite(ledPin1,0);
  analogWrite(ledPin2,0);
  analogWrite(ledPin4,0);
}
void atras()
{
  analogWrite(ledPin0,0);
  analogWrite(ledPin1,150);
  analogWrite(ledPin2,150);
  analogWrite(ledPin4,0);
}
void izquierda()
{
    analogWrite(ledPin0,0);
    analogWrite(ledPin1,100);
    analogWrite(ledPin2,0);
    analogWrite(ledPin4,200);
}
void derecha()
{
        analogWrite(ledPin0,200);
        analogWrite(ledPin1,0);
        analogWrite(ledPin2,100);
        analogWrite(ledPin4,0);
}
int preguntar(char n)
{
        if(n == 'c' )//Distancia
        {   
            return 9;
        }
        else if(n == 'w' )//izquierda
        { 
             Adelante();
             return 0;
        }
        else if(n == 'm')//parar
        {
            parar();
            return 1;
        }
        else if(n == 's')//derecha
        {
            atras();
            return 2;
        }
        else if(n == 'a')//adelante
        {
            izquierda();
            return 3;
        }
        else if (n == 'd')//atras
        {
            derecha();
            return 4;
        }
         else if(n == 'o')//encender
        {
            encender();
            return 5;
        }
         else if(n == 'p')//apagar
        {
            apagar();
            return 6;
        }
         else if(n == 'r')//parpadear
        {
            aviso();
            return 7;
        }

}
int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}
void loop() 
{ 
  if(Serial.available()>0)
      {    
        ByteReceived = Serial.read();  
        Serial.println(ByteReceived);
        
        preguntar(ByteReceived) ;
        for(int i = 0; i < 20; i++)
        {
            ByteReceived = Serial.read();
            int saberPosActual = preguntar(ByteReceived);
            if(saberPosActual == 9)
            {
                int cm = ping(TriggerPin, EchoPin);
                Serial.print("Distancia: ");
                Serial.println(cm);
            }
            delay(100);
        }
    
      }
}
