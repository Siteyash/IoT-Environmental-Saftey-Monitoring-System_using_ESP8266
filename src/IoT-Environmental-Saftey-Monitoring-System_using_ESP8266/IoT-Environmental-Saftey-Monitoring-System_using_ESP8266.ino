
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>

// ---------- WiFi Credentials ----------
const char* ssid = "Yours//";
const char* password = "Yours//";

// ---------- ThingSpeak ----------
const char* apiKey = "Yours//";
const char* server = "http://api.thingspeak.com/update";

// ---------- Sensor Pins ----------
#define DHTPIN D2
#define DHTTYPE DHT11

#define MQ2_PIN A0
#define FLAME_PIN D5
#define LED_PIN D7

DHT dht(DHTPIN, DHTTYPE);

// ---------- Settings ----------
unsigned long previousMillis = 0;
const unsigned long uploadInterval = 20000;

// Adjust after observing normal MQ-2 readings
const int GAS_THRESHOLD = 500;

// Most flame modules output LOW when flame is detected.
// Verify this with your actual module.
const bool FLAME_ACTIVE_LOW = true;

void setup() {
  Serial.begin(115200);

  pinMode(FLAME_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  dht.begin();

  Serial.println();
  Serial.println("Environmental Safety Monitoring");
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  // Read DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read MQ-2
  int gasValue = analogRead(MQ2_PIN);

  // Read Flame Sensor
  int flameRaw = digitalRead(FLAME_PIN);

  int flameStatus;

  if (FLAME_ACTIVE_LOW) {
    flameStatus = (flameRaw == LOW) ? 1 : 0;
  } else {
    flameStatus = (flameRaw == HIGH) ? 1 : 0;
  }

  // Check abnormal conditions
  bool gasAlert = gasValue > GAS_THRESHOLD;
  bool fireAlert = flameStatus == 1;

  // LED warning
  digitalWrite(LED_PIN,
               (gasAlert || fireAlert) ? HIGH : LOW);

  // Display sensor values
  Serial.println("\n------ SENSOR DATA ------");

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 reading failed!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  Serial.print("Flame Status: ");
  Serial.println(flameStatus);

  if (gasAlert || fireAlert) {
    Serial.println("WARNING: Abnormal condition detected!");
  } else {
    Serial.println("System Status: NORMAL");
  }

  // Upload every 20 seconds
  if (millis() - previousMillis >= uploadInterval) {
    previousMillis = millis();

    if (WiFi.status() == WL_CONNECTED &&
        !isnan(temperature) &&
        !isnan(humidity)) {

      WiFiClient client;
      HTTPClient http;

      String url = String(server) +
        "?api_key=" + apiKey +
        "&field1=" + String(temperature, 1) +
        "&field2=" + String(humidity, 1) +
        "&field3=" + String(gasValue) +
        "&field4=" + String(flameStatus);

      http.begin(client, url);

      int httpCode = http.GET();

      Serial.print("ThingSpeak Response: ");
      Serial.println(httpCode);

      if (httpCode > 0) {
        Serial.print("Entry ID: ");
        Serial.println(http.getString());
      }

      http.end();

    } else {
      Serial.println("WiFi disconnected or invalid DHT data.");
    }
  }

  delay(2000);
}
