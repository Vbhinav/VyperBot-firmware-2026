#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

/* WIFI CONFIG */
const char* ssid = "SAC-08(2.4GHz)";
const char* password = "sac@1964";

/*  UDP CONFIG */
WiFiUDP udp;
const unsigned int joystickPort = 1234;

/* JOYSTICK VALUES  */
float xVal = 128.0;
float yVal = 128.0;

unsigned long lastPacketTime = 0;

char packetBuffer[64];

/* SETUP */

void setup() {

  Serial.begin(115200);
  delay(500);

  Serial.println("\n=== JOYSTICK UDP TEST MODE ===");

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi CONNECTED");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  udp.begin(joystickPort);

  Serial.print("Listening UDP on port ");
  Serial.println(joystickPort);
}

/* LOOP */

void loop() {

  handleJoystickUDP();

  yield();   // keep WiFi alive
}

/* UDP JOYSTICK */

void handleJoystickUDP() {

  static unsigned long lastCheck = 0;

  if (millis() - lastCheck < 20) return;   // 50Hz
  lastCheck = millis();

  int packetSize = udp.parsePacket();
  if (!packetSize) return;

  int len = udp.read(packetBuffer, sizeof(packetBuffer) - 1);
  if (len <= 0) return;

  packetBuffer[len] = '\0';

  lastPacketTime = millis();

  Serial.println("\n--- UDP PACKET RECEIVED ---");

  Serial.print("RAW: ");
  Serial.println(packetBuffer);

  /* PARSE CSV */

  char* comma = strchr(packetBuffer, ',');
  if (!comma) {
    Serial.println("Invalid packet format");
    return;
  }

  *comma = '\0';

  xVal = constrain(atof(packetBuffer), 0, 255);
  yVal = constrain(atof(comma + 1), 0, 255);

  Serial.print("X: ");
  Serial.print(xVal);

  Serial.print("   Y: ");
  Serial.println(yVal);

  driveDifferential(xVal, yVal);
}

/* DIFFERENTIAL DRIVE TEST */

void driveDifferential(float x, float y) {

  float turn  = (x - 128.0) / 128.0;
  float speed = (128.0 - y) / 128.0;

  if (abs(turn) < 0.05) turn = 0;
  if (abs(speed) < 0.05) speed = 0;

  int left  = constrain((speed - turn) * 100, -100, 100);
  int right = constrain((speed + turn) * 100, -100, 100);

  Serial.print("Left Motor: ");
  Serial.print(left);

  Serial.print(" | Right Motor: ");
  Serial.println(right);
}
