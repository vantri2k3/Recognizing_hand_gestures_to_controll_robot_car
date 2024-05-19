#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

#define CMD_STOP 0
#define CMD_FORWARD 1
#define CMD_BACKWARD 2
#define CMD_LEFT 3
#define CMD_RIGHT 4

#define ENA D0
#define IN1_PIN D1  // The ESP8266 pin connected to the IN1 pin L298N
#define IN2_PIN D2  // The ESP8266 pin connected to the IN2 pin L298N
#define IN3_PIN D3  // The ESP8266 pin connected to the IN3 pin L298N
#define IN4_PIN D4  // The ESP8266 pin connected to the IN4 pin L298N
#define ENB D5

const char* ssid = "Xiaomi";
const char* password = "18112003";
unsigned int localUdpPort = 1234;
WiFiUDP udp;

void setup() {
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);

  // Connect to Wi-Fi  Serial.print("Connecting to.");
  Serial.begin(115200);
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());


  // Begin UDP
  Serial.println("Starting UDP");
  udp.begin(localUdpPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
}


void loop() {
  // Handle client requests
  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(udp.remotePort());

    // read the packet into packetBufffer
    char packetBuffer[255];
    udp.read(packetBuffer, packetSize);
    packetBuffer[packetSize] = 0; // null terminate the string
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    if (strcmp(packetBuffer, "F") == 0){
    CAR_moveForward();
    }
    if (strcmp(packetBuffer, "B") == 0){
      CAR_moveBackward();
    }
    if (strcmp(packetBuffer, "L") == 0){
      CAR_turnLeft();
    }
    if (strcmp(packetBuffer, "R") == 0){
      CAR_turnRight();
    }
    if (strcmp(packetBuffer, "S") == 0){
      CAR_stop();
    }
  }

  
  // TO DO: Your code here
}

void CAR_moveForward() {
  analogWrite(ENA, 300);
  analogWrite(ENB, 300);
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_moveBackward() {
  analogWrite(ENA, 300);
  analogWrite(ENB, 300);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void CAR_turnLeft() {
  analogWrite(ENA, 300);
  analogWrite(ENB, 300);
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_turnRight() {
  analogWrite(ENA, 300);
  analogWrite(ENB, 300);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_stop() { 
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}
