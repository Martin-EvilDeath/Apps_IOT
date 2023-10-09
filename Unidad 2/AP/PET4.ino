#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "BLACKPINK";
const char *password = "itcolima6";

String serverName = "http://192.168.0.101:7800/";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

int quantity = 0; // Variable para almacenar la cantidad

void post_data(String action, int quantity)
{
  DynamicJsonDocument json_chido(1024);
  json_chido["action"] = action;
  json_chido["quantity"] = quantity;
  String json_str;
  serializeJson(json_chido, json_str);

  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(json_str);

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(D2, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D16, OUTPUT);
  pinMode(D17, OUTPUT);


  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop()
{
  int buttonState = digitalRead(D2);

  if (buttonState == LOW)
  {
    quantity++;
    digitalWrite(D16, HIGH); // Enciende el primer LED
    delay(100); // Pequeña pausa para evitar múltiples incrementos por un solo botón presionado
    digitalWrite(D16, LOW);  // Apaga el primer LED
    post_data("inc", quantity);
  }

  buttonState = digitalRead(D4);

  if (buttonState == LOW)
  {
    quantity--;
    digitalWrite(D17, HIGH); // Enciende el segundo LED
    delay(100); // Pequeña pausa para evitar múltiples decrementos por un solo botón presionado
    digitalWrite(D17, LOW);  // Apaga el segundo LED
    post_data("dec", quantity);
  }

  if ((millis() - lastTime) > timerDelay)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      HTTPClient http;
      String serverPath = serverName;
      http.begin(serverPath.c_str());
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0)
      {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else
      {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
