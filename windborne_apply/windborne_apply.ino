/*
 * WindBorne Sensors Intern — Application POST Request
 * Board: ESP32 (any variant)
 * 
 * Arduino IDE Setup:
 *   1. File > Preferences > Additional Board Manager URLs:
 *      https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
 *   2. Tools > Board > Board Manager > search "esp32" > Install
 *   3. Tools > Board > ESP32 Dev Module (or your variant)
 *   4. Upload this sketch
 *   5. Open Serial Monitor at 115200 baud to see the result
 */

#include <WiFi.h>
#include <HTTPClient.h>

const char* WIFI_SSID     = "Columbia University";
const char* WIFI_PASSWORD  = "";  // Open network

const char* ENDPOINT = "https://windbornesystems.com/career_applications.json";

const char* PAYLOAD =
  "{"
    "\"career_application\":{"
      "\"name\":\"Shlok Desai\","
      "\"email\":\"sbd2150@columbia.edu\","
      "\"role\":\"Sensors Intern\","
      "\"notes\":\"Nairobi, Kenya. sub-Saharan Africa is one of the largest deserts on the planet, the baloon network i saw on the website has gaps across East Africa and the Indian ocean. A Nairobi site might fill critical data voids over the Indian Ocean and the African interior, directly improving forecasts for monsoon onset to the indian subcontinent as well where India Pakistan and Bangladesh are developing countries that rely a lot on farming and thus a better monsoon forecast there would be helpful. Also it is a place I have always wanted to visit - the Great Rift Valley, Maasai Mara, and Mount Kenya are on my bucket list. (P.S. This POST request was sent from an ESP32 on my desk at Columbia.)\","
      "\"submission_url\":\"https://desaishlok.github.io/windborne.html\","
      "\"resume_url\":\"https://desaishlok.github.io/ShlokDesai_Resume.pdf\""
    "}"
  "}";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n--- WindBorne Sensors Intern Application ---");
  Serial.println("--- Sent from ESP32 @ Columbia University ---\n");

  // Connect to WiFi
  Serial.printf("[..] Connecting to %s\n", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\n[FAIL] Could not connect to WiFi");
    return;
  }

  Serial.printf("\n[OK] Connected — IP: %s\n", WiFi.localIP().toString().c_str());

  // Send POST request
  HTTPClient http;
  http.begin(ENDPOINT);
  http.addHeader("Content-Type", "application/json");

  Serial.printf("[..] Sending POST to %s\n", ENDPOINT);
  int statusCode = http.POST(PAYLOAD);

  Serial.printf("[>>] Status: %d\n", statusCode);
  Serial.printf("[>>] Response: %s\n", http.getString().c_str());

  if (statusCode == 200) {
    Serial.println("\n=== APPLICATION ACCEPTED ===");
  } else {
    Serial.println("\n=== NOT ACCEPTED — check response above ===");
  }

  http.end();
  WiFi.disconnect(true);
}

void loop() {
  // Nothing — runs once
}
