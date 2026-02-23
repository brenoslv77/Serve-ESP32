#include <WiFi.h>
#include <WebServer.h>

//Nome e senha do ponto de acesso
const char* ssid = "IoT01-Senac-Breno";
const char* password = "12345678";

//Define o pino do LED
const int ledPin1 = 14;
const int ledPin2 = 27;                                     


//Criar um servidor web na porta 80
WebServer server(80);

//Página HTML que vai ser exibida nesse servidor
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Controlando LED</title>
</head>
<style>
        body{
            margin: 0;
            padding: 20px;
            font-family: Arial, Helvetica, sans-serif;
            background-color: #60a5fa;
            color: #000000;
            text-align: center;
        }
        h1 {
            color: hsl(0, 0%, 0%);
        }

        #LED1 {
            color: #fffb00;
        }

        #LED2 {
            color: #33ff00;
        }

        p{
            color: #000000;
            margin-bottom: 30px;
        }
        button{
            color: #000000;
            background-color: #ffffff;
            border: none;
            padding: 14px 24px;
            margin: 8px;
            border-radius: 8px;
            font-size: 16px;
            width: 100%;
            max-width: 220px;
        }
</style>
<body>
    <h1>Turma de IoT01 - Senac L13</h1>
    <p>Voce esta conectado ao Servidor de <strong>Breno</strong></p>
    <br></br>
    <h2 id="LED1">LED Amarelo</h2>
    <button onclick="location.href='/liga1'">Liga ✅</button>
    <button onclick="location.href='/desliga1'">Desliga ⛔</button>
    <h2 id="LED2"> LED Verde </h2>
    <button onclick="location.href='/liga2'">Liga ✅</button>
    <button onclick="location.href='/desliga2'">Desliga ⛔</button>

</body>
</html>

)rawliteral";

void handleRoot(){
  server.send(200, "text/html", htmlPage);
}

//função para ligar o led
void handleLedOn1(){
  digitalWrite(ledPin1, HIGH);
  server.send(200, "text/html", htmlPage);
}

void handleLedOn2(){
  digitalWrite(ledPin2, HIGH);
  server.send(200, "text/html", htmlPage);
}

//função para desligar o led
void handleLedOff1(){
  digitalWrite(ledPin1, LOW);
  server.send(200, "text/html", htmlPage);
}

void handleLedOff2(){
  digitalWrite(ledPin2, LOW);
  server.send(200, "text/html", htmlPage);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Configurando Access Point");

  //Inicia o Ponto de Acesso
  WiFi.softAP(ssid, password);

  //Exibir o IP do ESP32
  Serial.print("IP do ESP32:");
  Serial.println(WiFi.softAPIP());

  //Definir a rota em que a nossa página vai ser exibida (/)
  server.on("/", handleRoot);
  server.on("/liga1", handleLedOn1);
  server.on("/desliga1", handleLedOff1);

  
  server.on("/liga2", handleLedOn2);
  server.on("/desliga2", handleLedOff2);

  //iniciar o servidor
  server.begin();
  Serial.println("Servidor web iniciado!"); 

  //Definindo porta do led como output 
  pinMode(ledPin1, OUTPUT);
   pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin1, HIGH);
}

void loop() {
  //configuração que mantem o servidor ativo
  server.handleClient();
}