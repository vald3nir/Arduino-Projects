#include <WiFi.h>
#include <HTTPClient.h>

// ==================================================================================================

// Wi-fi Setup
const char *SSID = "dev severino";
const char *PASSWORD = "17210000";

// Server
const char *END_POINT = "http://192.168.10.179:1880/test";

// ==================================================================================================

void setup()
{
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) // Check for the connection
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED) // Check WiFi connection status
  {
    HTTPClient http;
    http.begin(END_POINT);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST("{\"topic\": 1721}");
    if (httpResponseCode > 0)
    {
      String response = http.getString(); // Get the response to the request
      Serial.println(httpResponseCode);   // Print return code
      Serial.println(response);           // Print request answer
    }
    else
    {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else
  {
    Serial.println("Error in WiFi connection");
  }
  delay(500);
}
