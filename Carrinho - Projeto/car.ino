// WIFI 
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SmartCar";
const char* password = "12345678";

WebServer server(80);

// Ligação das rodas
#define IN1 23
#define IN2 22
#define IN3 21
#define IN4 19

bool powerOn = false;


// MOVIMENTOS
void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void tras() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void esquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void direita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// COMANDOS
void handleCommand() {
  if (!server.hasArg("go")) {
    server.send(400, "text/plain", "Erro");
    return;
  }

  String cmd = server.arg("go");

  if (cmd == "power_on") {
    powerOn = true;
    parar();
  }
  else if (cmd == "power_off") {
    powerOn = false;
    parar();
  }
  else if (!powerOn) {
    server.send(200, "text/plain", "OFF");
    return;
  }
  else if (cmd == "frente") frente();
  else if (cmd == "tras") tras();
  else if (cmd == "esquerda") esquerda();
  else if (cmd == "direita") direita();
  else if (cmd == "stop") parar();
  else if (cmd == "buzina_on") toneESP32(BUZZER, 1000);
  else if (cmd == "buzina_off") noToneESP32(BUZZER);

  server.send(200, "text/plain", "OK");
}

// HTML 
const char PAGE[] PROGMEM = R"=====(


)=====";

// SETUP
void setup() {
  Serial.begin(115200);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(BUZZER,OUTPUT);

  parar();

  WiFi.softAP(ssid, password);

  server.on("/", [](){ server.send_P(200,"text/html",PAGE); });
  server.on("/cmd", handleCommand);

  server.begin();
  Serial.println(WiFi.softAPIP());
}

// LOOP
void loop() {
  server.handleClient();
}
