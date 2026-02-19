#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSans9pt7b.h>
#include "DHT.h"

//WS2812 LEDs
#define NEO_PIN 1
#define NUMPIXELS 10
#define DELAYVAL 100

//DHT Sensor
#define DHT_PIN 2 
#define DHTTYPE DHT11

//Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define SDA_PIN 8
#define SCL_PIN 9

//Temperatur
#define TEMP_MIN 22.0
#define TEMP_MID 24.0
#define TEMP_MAX 28.0
 
Adafruit_NeoPixel pixels(NUMPIXELS, NEO_PIN, NEO_RGB + NEO_KHZ800);
DHT dht(DHT_PIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    display.clearDisplay();
    display.display();
  }

  dht.begin();

  pixels.begin(); 
  pixels.clear();

}


void loop() {

  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(SSD1306_WHITE);



  int maxPixles = 0;
  float h = dht.readHumidity();
  Serial.print("H: ");
  Serial.println(h);
  float t = dht.readTemperature();
  Serial.print("T: ");
  Serial.println(t);

  int r = 0, g = 0, b = 0;

  int adcValue = analogRead(0);
  int brightness = map(adcValue, 0, 4095, 0, 255);

  display.setCursor(0, 15);
  
  if(t < TEMP_MIN){
    r = 0;
    g = 0;
    b = 200;
    Serial.println("Kalt");
    display.print("Kalt");
  }
  if((t >= TEMP_MIN) && (t <= TEMP_MAX)){
    r = 0;
    g = 200;
    b = 0;
    Serial.println("Ok");
    display.print("Ok ");

  }
  if(t > TEMP_MAX){
    r = 200;
    g = 0;
    b = 0;
    Serial.println("Heiß");
    display.print("Heiß");
  }

  display.setCursor(0, 32);
  display.print(brightness);
  
  display.display();

  
  pixels.setBrightness(brightness);
  pixels.clear();
  for(int i = 0; i < NUMPIXELS; i++) { // For each pixel...
  // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(i, pixels.Color(r, g, b));
     // Send the updated pixel colors to the hardware.
  
  }
  pixels.show();
  delay(50);
}
