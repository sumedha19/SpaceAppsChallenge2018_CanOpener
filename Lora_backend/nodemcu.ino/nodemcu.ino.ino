
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <WiFiClient.h>
#include <Hash.h>

const char* ssid = "*******";
const char* password = "******";


WebSocketsServer webSocket = WebSocketsServer(7777);
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   }
    
    Serial.println("");
    Serial.println("Connected to Network");
  //  Serial.println(ssid);
//    Serial.print("IP address: ");
//    Serial.println(WiFi.localIP());
        
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    webSocket.loop();
    if (Serial.available() > 0){
       char c[] = {(char)Serial.read()};
      webSocket.broadcastTXT(c, sizeof(c));
    }
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
   
   switch (type) {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {              // if a new websocket connection is established
        IPAddress ip = webSocket.remoteIP(num);
        //Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        Serial.printf("Connected to gateway!\n");
        break;              
      }
      
    case WStype_TEXT: {                    // if new text data is received
      Serial.printf("[%u] get Text: %s\n", num,(char) payload[0]);
      break;
    }
  
}
}
