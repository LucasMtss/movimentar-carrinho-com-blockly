//ARDUINO OBSTACLE AVOIDING CAR//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//NewPing Library https://github.com/livetronic/Arduino-NewPing// 
//Servo Library https://github.com/arduino-libraries/Servo.git //

#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 255 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;   

//######################################

//Denominando as portas de cada componente

//Mensagem enviada pela IoT
int frente = 24;
int direita = 26;
int re = 28;
int esquerda = 30;

//Farois Dianteiros
int farolDE = 39;
int farolDD = 41;

//Luz de Ré
int farolTE = 37;
int farolTD = 43;

//Controladores do Sonar Ultrasônico
int SonarTrigger = 49;
int SonarEcho = 47;

int IoT = 53;

//##################################
  
//Variáveis utilizadas  
int distancia = 0;
int tempo = 0;

int speedSet = 0;

int piso = 600;

void setup() {  
  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);

  //Portas digitais lendo a entrada dos sinais da IoT
  pinMode(frente, INPUT);
  pinMode(esquerda, INPUT);
  pinMode(re, INPUT);
  pinMode(direita, INPUT);
  
  //Sensor Ultrasônico
  pinMode(SonarTrigger, OUTPUT);
  pinMode(SonarEcho, INPUT);
  Serial.begin(9600);
  
  //Farois
  pinMode(farolDE, OUTPUT);
  pinMode(farolDD, OUTPUT);
  pinMode(farolTE, OUTPUT);
  pinMode(farolTD, OUTPUT);
  
  pinMode(IoT, OUTPUT);
}

void loop() {
  digitalWrite(IoT, HIGH);  
  //moveForward();
  //moveBackward(); 
  //delay(5000);
  //turnRight(); 
  //turnLeft();
  
  //Farois Dianteiros acessos
  digitalWrite(farolDE, HIGH);
  digitalWrite(farolDD, HIGH);

   //Verifica qual sinal foi enviado pela IoT
  if(digitalRead(frente) == HIGH) {
    //Movimento para frente só é feito caso não tenha obstáculo a uma certa distância
    if(sensorUltra() >= 150)
      moveForward();
  }
  if(digitalRead(re) == HIGH)
  	moveBackward();
  if(digitalRead(esquerda) == HIGH)
  	turnLeft();
  if(digitalRead(direita) == HIGH)
   	turnRight();
  
}

void moveStop() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
} 
  
void moveForward() {
    motor1.run(BACKWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet  += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
   }   
   delay(piso);
   moveStop();
}

void moveBackward() {
    digitalWrite(farolTE, HIGH);
    digitalWrite(farolTD, HIGH);
    motor1.run(FORWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet  += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
  }
  delay(piso);
  moveStop();
  digitalWrite(farolTE, LOW);
  digitalWrite(farolTD, LOW);
  
}  

void turnRight() {
  motor1.run(BACKWARD);
  motor4.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);   
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet  += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
  }
  delay(piso);
  moveStop();
} 
 
void turnLeft() {
  motor1.run(FORWARD);
  motor4.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);   
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet  += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
  }
  delay(piso);
  moveStop();
}  

int sensorUltra() {
  //Estabiliza o sensor
  digitalWrite(SonarTrigger, LOW);
  delayMicroseconds(2);
  
  //Envia um pulso para ativar o sensor
  digitalWrite(SonarTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(SonarTrigger, LOW);
  
  //Recebe o pulso de retorno do sensor vindo do ECHO e retorna o a duração do pulso em microsegundos
  tempo = pulseIn(SonarEcho, HIGH);
  //Distância = tempo * velocidade do som / 2 (Velocidade do som é 340 m/s)
  distancia = tempo/58.2;
  
  return distancia;
}
