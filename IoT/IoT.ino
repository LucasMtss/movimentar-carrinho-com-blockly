/*
 	
    				CÓDIGO DA PLACA NodeMCU (IoT)
	A placa IoT estabelece uma conexão WiFi, quando a conexão é estabelecida
    um led RGB sinalizará com a coloração verde, caso contrário permanecerá vermelho.
    Recebe um vetor da API python, então separa e envia individualmente os movimentos
    para a placa Mega, cada movimento em sua respectiva porta.
    
    Consertar a pinagem do LED RGB de acordo com os pinos da placa IoT, enviar os dados 
    para placa Mega pelos respectivos pinos de movimentação.
    
    Instalação dos Drivers: 
    	https://www.robocore.net/tutoriais/instalando-driver-do-nodemcu
    
    URL de acesso a placa NodeMCU:
    	http://arduino.esp8266.com/stable/package_esp8266com_index.json
        
    Bibliotecas:
    	ESP8266
    	WifiManager
        Arduino_JSON
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <vector>
#include <string>

using namespace std;

const char* ssid = "Leone";
const char* password = "12345678";

//URL da API python
const char* serverName = "http://192.168.86.2:5000/api/carrinho";

String sensorReadings;
float sensorReadingsArr[3];

// Variáveis de Server
ESP8266WebServer server(80);

int rgbRed = 11;
int rgbGreen = 10;
int rgbBlue = 9;

String fim;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Checa o status de conexão do Wifi
  	
    //LED RGB - Verde - Conexão Wifi estabelecida
    digitalWrite(rgbGreen, HIGH);
    digitalWrite(rgbRed, LOW);
    digitalWrite(rgbBlue, LOW);
    
    WiFiClient client;
    HTTPClient http;
 
    //Requisição a API
    //http.begin(client, serverName);
    //http.GET();                    

    //Transforma a esposta em uma String
    String payload = http.getString();
	
    //fim = payload;
    fim = "000022220000";
    //Fecha a conexão
    //http.end();
    
    //Enviar os dados para a placa Mega
    std::vector<char> movimentos;
    for(char caracter : fim){
      movimentos.push_back(caracter);
    } 
    
    for(int i = 0;i < movimentos.size(); i++){
    	digitalWrite(movimentos.at(i), HIGH);	
      delay(700);
      digitalWrite(movimentos.at(i), LOW);	
    }
    
    
  } else {
    
  	//LED RGB - Vermelho - Conexão Wifi não estabelecida
    digitalWrite(rgbGreen, LOW);
    digitalWrite(rgbRed, HIGH);
    digitalWrite(rgbBlue, LOW);
  }
  delay(5000);
}
