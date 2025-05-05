#include <FastLED.h>
#define LED_PIN 6
#define NUM_LEDS 19
#define LED_TYPE SK6812
#define COLOR_ORDER GRB

#define SENSOR_PIN A0

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  Serial.begin(9600);
  FastLED.setBrightness(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int valorSensor = analogRead(SENSOR_PIN);

  //mapear el número de leds a encender
  unsigned int encender = map(valorSensor, 0, 1023, 0, NUM_LEDS);

  //bucle para encender solo los necesarios
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < encender) {
      //modificar el tono según el led en el que se encuentra
      byte tono = map(i, 0, NUM_LEDS -1, 0, 96);
      leds[i] = CHSV(tono, 255, 255);
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
  delay(50);
}
