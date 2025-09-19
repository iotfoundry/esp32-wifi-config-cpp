#include "WiFi.h"
#include "Preferences.h"
#include "wifi_config.h" // WiFi credentials (gitignored)

#define LED_PIN 7 // ESP32C3 built-in LED

// Signal strength thresholds
#define STRONG_SIGNAL -50 // -30 to -50 dBm
#define MEDIUM_SIGNAL -70 // -50 to -70 dBm
// Below -70 dBm is weak signal

// WiFi credentials are loaded from wifi_config.h
// This file is gitignored for security

void setup()
{
  Serial.begin(115200);
  delay(1000);

  // Setup LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("ESP32C3 WiFi Connection");

  // Connect to WiFi
  connectToWiFi();
}

void connectToWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to WiFi...");
  Serial.println("SSID: " + String(WIFI_SSID));

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20)
  {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("\nWiFi Connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  }
  else
  {
    Serial.println("\nWiFi connection failed!");
    digitalWrite(LED_PIN, HIGH);
  }
}

void loop()
{
  // Check WiFi status and show signal strength
  if (WiFi.status() == WL_CONNECTED)
  {
    int rssi = WiFi.RSSI();
    Serial.print("WiFi Connected - IP: ");
    Serial.print(WiFi.localIP());
    Serial.print(" | RSSI: ");
    Serial.print(rssi);
    Serial.println(" dBm");

    // LED signal strength indicator
    showSignalStrength(rssi);
  }
  else
  {
    Serial.println("WiFi Disconnected - Attempting to reconnect...");
    digitalWrite(LED_PIN, LOW); // LED off when disconnected

    // Attempt to reconnect
    connectToWiFi();
  }

  delay(2000); // Check every 2 seconds
}

void showSignalStrength(int rssi)
{
  if (rssi >= STRONG_SIGNAL)
  {
    // Strong signal: Fast blink (100ms)
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
  else if (rssi >= MEDIUM_SIGNAL)
  {
    // Medium signal: Medium blink (500ms)
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  }
  else
  {
    // Weak signal: Slow blink (1000ms)
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
  }
}

String getWiFiStatus()
{
  switch (WiFi.status())
  {
  case WL_CONNECTED:
    return "Connected";
  case WL_NO_SSID_AVAIL:
    return "No SSID Available";
  case WL_CONNECT_FAILED:
    return "Connection Failed";
  case WL_CONNECTION_LOST:
    return "Connection Lost";
  case WL_DISCONNECTED:
    return "Disconnected";
  default:
    return "Unknown";
  }
}
