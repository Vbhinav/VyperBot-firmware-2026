/* LDR PIN */
#define LDR_PIN A0

/* LDR SETTINGS */
#define LDR_THRESHOLD 1000

void setup() {

  Serial.begin(115200);
  delay(500);

  Serial.println("\n=== LDR TEST MODE ===");

  pinMode(LDR_PIN, INPUT);
}

void loop() {

  int ldrValue = 0;

  // Average 5 readings
  for (int i = 0; i < 5; i++) {
    ldrValue += analogRead(LDR_PIN);
    delay(2);
  }

  ldrValue /= 5;

  Serial.print("LDR Value: ");
  Serial.print(ldrValue);

  if (ldrValue >= LDR_THRESHOLD) {
    Serial.println("  -> HIT DETECTED");
  } else {
    Serial.println("  -> no hit");
  }

  delay(100);
}
