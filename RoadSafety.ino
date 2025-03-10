#define BLYNK_TEMPLATE_ID "TMPL30VD23i8k"
#define BLYNK_TEMPLATE_NAME "FOB IOT"
#define BLYNK_AUTH_TOKEN "VvGyh_GmS1FrsGd6zCUOL67D3qJ1prtm"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>  // Include DHT library

// Pin Definitions
const int ldrPin = A0;          // LDR connected to A0
const int motionPin = D6;       // PIR motion sensor connected to D5
const int trigPin = D4;         // Ultrasonic sensor trigger pin
const int echoPin = D5;         // Ultrasonic sensor echo pin
const int ledPin = D7;          // LED connected to D4
const int dhtPin = D2;          // DHT sensor connected to D3

// DHT Sensor Setup
#define DHT_TYPE DHT11  // Use DHT11 or DHT22
DHT dht(dhtPin, DHT_TYPE);

// Variables
int lightLevel = 0;             // Stores light level from LDR
bool motionDetected = false;    // Stores motion detection status
float crowdDensity = 0;         // Stores crowd density (distance from ultrasonic sensor)
float temperature = 0;          // Stores temperature from DHT sensor
float humidity = 0;             // Stores humidity from DHT sensor
float duration , distance ;
// Blynk Authentication
char auth[] = "VvGyh_GmS1FrsGd6zCUOL67D3qJ1prtm"; // Replace with your Blynk Auth Token
char ssid[] = "Aadi_5GHz";   // Replace with your WiFi SSID
char pass[] = "erashu07"; // Replace with your WiFi Password

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize Pins
  pinMode(ldrPin, INPUT);
  pinMode(motionPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize DHT Sensor
  dht.begin();

  // Connect to Wi-Fi and Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();  // Run Blynk

  // Read sensor data
  lightLevel = analogRead(ldrPin);  // Read light level
  motionDetected = digitalRead(motionPin);  // Read motion status
  crowdDensity = measureDistance();  // Measure crowd density
  temperature = dht.readTemperature();  // Read temperature
  humidity = dht.readHumidity();  // Read humidity

  // Send data to Blynk
  Blynk.virtualWrite(V0, lightLevel);  // Send light level to Blynk (Virtual Pin V0)
  Blynk.virtualWrite(V1, motionDetected);  // Send motion status to Blynk (Virtual Pin V1)
  Blynk.virtualWrite(V2, crowdDensity);  // Send crowd density to Blynk (Virtual Pin V2)
  Blynk.virtualWrite(V3, temperature);  // Send temperature to Blynk (Virtual Pin V3)
  Blynk.virtualWrite(V4, humidity);  // Send humidity to Blynk (Virtual Pin V4)

  // Control LED based on motion and light level
  if (motionDetected && lightLevel < 800) {  // Adjust threshold as needed
    digitalWrite(ledPin, HIGH);  // Turn on LED
  } else {
    digitalWrite(ledPin, LOW);  // Turn off LED
  }

  delay(1000);  // Delay for stability
}

// Function to measure distance using ultrasonic sensor
float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  return distance;
  delay(100);
}