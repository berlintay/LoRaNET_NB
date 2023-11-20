#include <Arduino.h>
#include <WiFi.h>
#include <ESP_Mesh.h>
#include <RH_RF95.h>

#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASS "YourWiFiPassword"

#define NODE_ID 1

// LoRa Configuration
#define RFM95_CS_PIN 5
#define RFM95_RST_PIN 14
#define RFM95_INT_PIN 2
RH_RF95 rf95(RFM95_CS_PIN, RFM95_INT_PIN);

Mesh mesh;

void setup() {
  Serial.begin(115200);

  // Setup LoRa
  if (!rf95.init()) {
    Serial.println("LoRa initialization failed.");
    while (1);
  }

  // Setup Wi-Fi
  connectToWiFi();

  // Setup Mesh
  mesh.init();
  mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION);
}

void loop() {
  // Handle LoRa communications
  receiveLoRaData();
  sendLoRaData();

  // Handle Wi-Fi communications
  receiveWiFiData();
  sendWiFiData();

  // Handle Mesh communications
  mesh.update();
}

void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void receiveLoRaData() {
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)) {
      Serial.print("Received LoRa data: ");
      Serial.write(buf, len);
      Serial.println();
      // Process the received LoRa data
    }
  }
}

void sendLoRaData() {
  // Send LoRa data
  String data = "Hello from LoRa Node " + String(NODE_ID);
  rf95.send((uint8_t *)data.c_str(), data.length());
  rf95.waitPacketSent();
  Serial.println("Sent LoRa data: " + data);
}

void receiveWiFiData() {
  // Implement Wi-Fi data reception logic
  // Example: String data = WiFi.readString();
  // Process the received Wi-Fi data
}

void sendWiFiData() {
  // Send Wi-Fi data
  // Example: String data = "Hello from Wi-Fi Node " + String(NODE_ID);
  //         WiFi.print(data);
  Serial.println("Sent Wi-Fi data");
}
