#define ADC_Pin 0
#define LED_PIN 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int ADCvalue = analogRead(ADC_Pin);
  Serial.println("ADC: ");
  Serial.print(ADCvalue);
  int mapValue = map(ADCvalue, 0, 4095, 0, 255);
  analogWrite(LED_PIN, mapValue);


}


analogWrite
