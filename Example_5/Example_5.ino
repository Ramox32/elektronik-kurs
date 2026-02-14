void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Hallo Welt: ");
  Serial.print(sensorValue);
  Serial.println(" Hallo.");
}

