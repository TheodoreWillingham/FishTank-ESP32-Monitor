#include <Arduino.h> // Base Arduino Functions
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1           // Reset pin not used
#define SCREEN_ADDRESS 0x3C     // I2C address detected
#define ONE_WIRE_BUS 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float Celsius = 0;
float Fahrenheit = 0;

void setup() {
  sensors.begin();
  Serial.begin(115200);
  Wire.begin(21, 22);         // SDA, SCL
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);                  // Stop here
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Tanks Tempature: ");
  display.display();
}

void loop() {
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);

  display.fillRect(0, 20, SCREEN_WIDTH, 20, SSD1306_BLACK);

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print(Fahrenheit);
  display.println(" F");
  display.display();

  delay(10000);
}