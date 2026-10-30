```cpp
// Task 3: IFTTT + Adafruit IO Voice-Controlled IoT Automation
// Board: ESP32
// Voice Assistant: Google Assistant
// Automation: IFTTT
// Cloud Platform: Adafruit IO
// Feed: LED
//
// Feed value 1 = Bulb ON
// Feed value 0 = Bulb OFF
//
// IMPORTANT:
// Keep your Wi-Fi password and Adafruit IO key private.
// Replace the placeholders below before uploading.

#define IO_USERNAME "YOUR_AIO_USERNAME"
#define IO_KEY      "YOUR_AIO_KEY"

#define WIFI_SSID   "YOUR_WIFI_NAME"
#define WIFI_PASS   "YOUR_WIFI_PASSWORD"

#include "AdafruitIO_WiFi.h"

// Connect ESP32 to Adafruit IO through Wi-Fi
AdafruitIO_WiFi io(
  IO_USERNAME,
  IO_KEY,
  WIFI_SSID,
  WIFI_PASS
);

// Use the same LED feed as Task 2
AdafruitIO_Feed *ledFeed = io.feed("LED");

// ESP32 GPIO pins
const int RELAY_PIN = 26;
const int LED_PIN = 2;

// This function runs whenever the LED feed receives an update
// from IFTTT or the Adafruit IO dashboard.
void handleRelay(AdafruitIO_Data *data) {

  int value = data->toInt();

  Serial.print("Adafruit IO value: ");
  Serial.println(value);

  if (value == 1) {

    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);

    Serial.println("Relay ON -> Bulb ON");

  }
  else if (value == 0) {

    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(LED_PIN, LOW);

    Serial.println("Relay OFF -> Bulb OFF");

  }
  else {

    Serial.println("Invalid feed value. Use 1 or 0.");

  }
}

void setup() {

  // Start Serial Monitor
  Serial.begin(115200);

  // Configure output pins
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Start with outputs LOW
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.println();
  Serial.println("Task 3: Voice-Controlled IoT Automation");
  Serial.println("Connecting to Adafruit IO...");

  // Start Adafruit IO connection
  io.connect();

  // Register callback for LED feed updates
  ledFeed->onMessage(handleRelay);

  // Wait until connected
  while (io.status() < AIO_CONNECTED) {

    Serial.print(".");
    delay(500);

  }

  Serial.println();
  Serial.println("Connected to Adafruit IO!");
  Serial.println("Waiting for voice or dashboard commands...");

  // Request the latest feed value
  ledFeed->get();
}

void loop() {

  // Maintain connection and process incoming feed updates
  io.run();

}
```
