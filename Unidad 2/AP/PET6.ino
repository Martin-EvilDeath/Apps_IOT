#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "Lucecita";
const char *password = "LuzFerBonita54321";

String serverName = "http://c83e-187-190-35-202.ngrok-free.app";

unsigned long lastTime = 0;
unsigned long timerDelay = 3000;

// Define los pines para los botones
const int buttonPinAsc = 27; // Cambia al número de pin que estás utilizando
const int buttonPinDesc = 33; // Cambia al número de pin que estás utilizando

const int ledPin = 13;

bool ascRequested = false; // Bandera para controlar la solicitud "asc"
bool descRequested = false; // Bandera para controlar la solicitud "desc"

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

  // Configura los pines de los botones como entradas
  pinMode(buttonPinAsc, INPUT_PULLUP);
  pinMode(buttonPinDesc, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  // Verifica si el botón "asc" se ha presionado
  if (digitalRead(buttonPinAsc) == HIGH && !ascRequested) {
    ascRequested = true;
  }

  // Verifica si el botón "desc" se ha presionado
  if (digitalRead(buttonPinDesc) == HIGH && !descRequested) {
    descRequested = true;
  }

  HTTPClient http;

  String serverPathLed = serverName + "/led";

  http.begin(serverPathLed.c_str());

  // Send HTTP GET request
  int httpResponseCodeGET = http.GET();
  
  if (httpResponseCodeGET>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCodeGET);
    String payload = http.getString();
    Serial.println(payload);

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    int led = doc["status"];
    Serial.println(led);

    if (led == false) {
      digitalWrite(ledPin, LOW);
    }
    if (led == true) {
      digitalWrite(ledPin, HIGH);
    }
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCodeGET);
  }

  http.end();

  if (ascRequested || descRequested) {
    if ((millis() - lastTime) > timerDelay) {
      if (WiFi.status() == WL_CONNECTED) {
        String serverPath = serverName + "/led";

        http.begin(serverPath.c_str());

        DynamicJsonDocument jsonDoc(64);

        if (ascRequested) {
          jsonDoc["action"] = "asc";
          ascRequested = false; // Restablece la bandera después de la solicitud
        } else if (descRequested) {
          jsonDoc["action"] = "desc";
          descRequested = false; // Restablece la bandera después de la solicitud
        }
        jsonDoc["quantity"] = 1; // Cambia la cantidad según tu necesidad

        String jsonString;
        serializeJson(jsonDoc, jsonString);

        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonString);

        if (httpResponseCode > 0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          Serial.println(payload);
        } else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }

        http.end();
      } else {
        Serial.println("WiFi Disconnected");
      }
      lastTime = millis();
    }
  }
}
