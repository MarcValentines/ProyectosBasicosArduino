#include <FastLED.h>
#define LED_PIN 6
#define NUM_LEDS 19
#define BRIGHTNESS 100
#define LED_TYPE SK6812
#define COLOR_ORDER GRB

#define SENSOR_PIN A0
#define BRIGHTNESS_MIN 10
#define BRIGHTNESS_MAX 255

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //leer el valor analógico del sensor (0-1023)
  unsigned int valorSensor = analogRead(SENSOR_PIN);

  //mapear el valor al rango de brillo
  unsigned int brillo = map(valorSensor, 0, 1023, BRIGHTNESS_MIN, BRIGHTNESS_MAX);

  //aplicar el nuevo brillo
  FastLED.setBrightness(brillo);

  //transformar todos los leds a un color sólido
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();

  //Detener arduino 50ms
  delay(50);
}
