#include <Stepper.h>
#include <WiFi.h>
#include <PubSubClient.h>



#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978



int santa_melody[] = {
  NOTE_G4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_B3,
  NOTE_C4
};

int santa_tempo[] = {
  8,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 2,
  4, 4, 4, 4,
  4, 2, 4,
  1
};

int wish_melody[] = {
  NOTE_B3, 
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};

int wish_tempo[] = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};




const char *ssid = "linksys";
const char *password = "";
const char *mqttBroker = "192.168.1.100";
const int mqttPort = 1883;
const char *mqttUser = "";
const char *mqttPassword = "";
const char *mqttClientId = "";
const char *mqttTopic = "campesino/led";



WiFiClient espClient;
PubSubClient client(espClient);















const int stepsPerRevolution = 800;  
const int motorSpeed = 11;  
const int washingTime = 5000;  
const int pauseTime = 300;  

int DISTANCIA = 0;
int pinLed = 14;
int pinLed2 = 26;
int pinLed3 = 27;
int pinLed4 = 25;
int pinLed5 = 33;
int pinLed6 = 4;
int pinLed7 = 17;
int pinLed8 = 15;
int pinEco = 12;
int buzzer =2;


int pinGatillo = 13;

#define IN1 22
#define IN2 21
#define IN3 19
#define IN4 5




Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH) * 0.01723 / 2;  
}

//MELODIA 1
void playMelody(int melody[], int tempo[]) {
  for (int i = 0; i < sizeof(santa_melody) / sizeof(santa_melody[0]); i++) {
    int noteDuration = 2000 / tempo[i];

    digitalWrite(pinLed6, HIGH);
    digitalWrite(pinLed7, HIGH);
    
    digitalWrite(pinLed8, HIGH);

    tone(buzzer, melody[i], noteDuration);
    delay(noteDuration * 1.1);

    digitalWrite(pinLed6, LOW);
    digitalWrite(pinLed7, LOW);
    digitalWrite(pinLed8, LOW);

    noTone(buzzer);

    delay(50);
  }
}

//MELODIA 2
void playMelody2() {
  for (int i = 0; i < sizeof(wish_melody) / sizeof(wish_melody[0]); i++) {
    int noteDuration = 2000 / wish_tempo[i];

    digitalWrite(pinLed6, HIGH);
    digitalWrite(pinLed7, HIGH);
    
    digitalWrite(pinLed8, HIGH);

    tone(buzzer, wish_melody[i], noteDuration);
    delay(noteDuration * 1.1);

    digitalWrite(pinLed6, LOW);
    digitalWrite(pinLed7, LOW);
    digitalWrite(pinLed8, LOW);


    noTone(buzzer);

    delay(50);
  }
}








void setup_wifi()
{
  delay(10);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}



void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Mensaje recibido en el tópico: ");
  Serial.println(topic);

  Serial.print("Contenido: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();

  if (strcmp(topic, mqttTopic) == 0)
  {
    if (payload[0] == '1')
    {
      digitalWrite(pinLed7, HIGH);
      digitalWrite(pinLed6, HIGH);
      digitalWrite(pinLed8, HIGH);
      tone(buzzer, 1000);
      
    }
    else if (payload[0] == '0')
    {
      digitalWrite(pinLed7, LOW);
      digitalWrite(pinLed6, LOW);
      digitalWrite(pinLed8, LOW);
      noTone(buzzer);
    }
    else if (payload[0] == '2') {
        playMelody(santa_melody, santa_tempo); 
        Serial.println("Clockwise");
        myStepper.step(stepsPerRevolution);
        delay(washingTime);

        delay(pauseTime);

        myStepper.step(-stepsPerRevolution);
        delay(washingTime);

        delay(pauseTime);
        myStepper.step(0);
        playMelody2();
      }
    else if (payload[0]== '3')
    {
      myStepper.step(0);
    }
    
  }
}

unsigned long tiempoUltimoIntentoConexion = 0;
const unsigned long tiempoEsperaReconexion = 60000;  

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Intentando conexión MQTT...");
    if (client.connect(mqttClientId, mqttUser, mqttPassword))
    {
      Serial.println("Conectado");
      client.subscribe(mqttTopic);
    }
    else
    {
      Serial.print("falló, rc=");
      Serial.print(client.state());
      Serial.println(" Intentando de nuevo en 5 segundos");
      delay(5000);
      
      tiempoUltimoIntentoConexion = millis();
    }
  }
}



void setup()
{
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqttBroker, mqttPort);
  client.setCallback(callback);

 
  myStepper.setSpeed(motorSpeed);

  
  pinMode(pinLed, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinLed4, OUTPUT);
  pinMode(pinLed5, OUTPUT);
  pinMode(pinLed6, OUTPUT);
  pinMode(pinLed7, OUTPUT);
  pinMode(pinLed8, OUTPUT);

  tone(buzzer, 5000);   
  tone(buzzer,1000, 500); 
  noTone(buzzer); 
}




unsigned long tiempoAnteriorSensor = 0;
unsigned long tiempoAnteriorAutomatico = 0;
const unsigned long intervaloMovimientoSensor = 2000;  
const unsigned long intervaloMovimientoAutomatico = 200000;  
const int duracionMovimiento = 1000;  

void loop() {
  DISTANCIA = readUltrasonicDistance(pinGatillo, pinEco);
  Serial.println(DISTANCIA);

  unsigned long tiempoActual = millis();
  

  if (tiempoActual - tiempoAnteriorSensor >= intervaloMovimientoSensor) {
    if (DISTANCIA < 20) {
      digitalWrite(pinLed, HIGH);
      digitalWrite(pinLed2, HIGH);
      digitalWrite(pinLed3, HIGH);
      digitalWrite(pinLed4, HIGH);
      digitalWrite(pinLed5, HIGH);

      playMelody(wish_melody,wish_tempo);

      Serial.println("Clockwise");
        myStepper.step(stepsPerRevolution);
        delay(washingTime);

        delay(pauseTime);

        myStepper.step(-stepsPerRevolution);
        delay(washingTime);

        delay(pauseTime);
        myStepper.step(0);

      tiempoAnteriorSensor = tiempoActual;
    } else {
      digitalWrite(pinLed, LOW);
      digitalWrite(pinLed2, LOW);
      digitalWrite(pinLed3, LOW);
      digitalWrite(pinLed4, LOW);
      digitalWrite(pinLed5, LOW);

      noTone(buzzer);

      myStepper.step(0);
    }
  }

  
  if (tiempoActual - tiempoAnteriorAutomatico >= intervaloMovimientoAutomatico) {
       Serial.println("Clockwise");
        myStepper.step(stepsPerRevolution);
        delay(washingTime);

        
        delay(pauseTime);

       
        myStepper.step(-stepsPerRevolution);
        delay(washingTime);

        
        delay(pauseTime);
        myStepper.step(0);

        playMelody2();

   
    tiempoAnteriorAutomatico = tiempoActual;
}




  if (!client.connected())
  {
    reconnect();
  }


  client.loop();


  delay(20);
}
